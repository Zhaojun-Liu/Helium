/*
* Helium is a customizable extension system for Minecraft server.
* You can get the lastest source code and releases of Helium at :
* https://github.com/Helium-DevTeam/Helium
* ----------------------------------------------------------------------------------------
* Helium Copyright (C) 2021-2022 HeliumDevTeam
*
* This file is a part of Helium
*
* Helium is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Helium is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Helium.  If not, see <https://www.gnu.org/licenses/>.
* ----------------------------------------------------------------------------------------
*/

module;

#include<boost/dll.hpp>
#include<boost/uuid/uuid.hpp>
#include<boost/uuid/uuid_io.hpp>
#include<boost/uuid/uuid_generators.hpp>

#include"tinyxml2/tinyxml2.h"

export module Helium.Extension;

import <string>;
import <vector>;
import <list>;
import <any>;
import <map>;

import Helium.UUIDManager;
import Helium.Logger;
import Helium.Events;

using namespace tinyxml2;
using namespace std;
using namespace boost::uuids;
using namespace boost::dll;
using namespace boost::filesystem;

export{
	namespace Helium {
		enum ExtStat {
			EXT_STATUS_EMPTY,
			EXT_STATUS_LOADING,
			EXT_STATUS_LOADED,
			EXT_STATUS_UNLOADING,
			EXT_STATUS_UNLOADED,
			EXT_STATUS_LOCKED
		};

		void HeliumExtensionDebugPrint(string extprint);

		class HeliumExtension {
		public:
			HeliumExtension() {
				this->extension_eventmgr = make_shared<HeliumEventManager>();
			}
			HeliumExtension(string cfgname);
			~HeliumExtension();

			int LoadExt();
			int LockExt();
			int UnlockExt();
			int UnloadExt();
			int ScanEventFunc();
			void* GetFuncPtr(string funcname);
			void* SetFuncPtr(string funcname, void* newptr);
			bool HasFunc(string funcname);
			string GetExtName();

			class HeliumExtensionConfig {
				friend class HeliumExtension;
			public:
				string _stdcall GetExtConfigPath() {
					return configpath.string();
				}
				void _stdcall PutExtConfigPath(string path) {
					this->configpath = path;
				}

				string _stdcall GetExtName() {
					return configpath.string();
				}
				void _stdcall PutExtName(string path) {
					this->configpath = path;
				}

				int ReadConfig();
			private:
				fs::path configpath;
				fs::path extpath;
				string extname;
			};

		private:
			HeliumExtensionConfig config;
			map<string, void*> funcs;
			int extstat;
			uuid extuuid;
			shared_library extins;
			shared_ptr<HeliumEventManager> extension_eventmgr;
		};

		vector<HeliumExtension> extensions;

		int InitAllExtension();
		int LoadAllExtension();
		int UnloadAllExtension();
		int LockAllExtension();
		int UnlockAllExtension();
	}
}

namespace Helium {
	void HeliumExtensionDebugPrint(string extprint) {
		log << HLL::LL_INFO << "Debug print from extension : " << extprint << hendl;
	}

	int HeliumExtension::HeliumExtensionConfig::ReadConfig() {
		tinyxml2::XMLDocument doc;
		if (auto ret = doc.LoadFile(this->configpath.string().c_str()); ret != tinyxml2::XMLError::XML_SUCCESS) {
			log << LCRIT << "Failed to load extension config file : " << this->configpath.filename().string() << hendl;
			log << LCRIT << "The extension will not be loaded" << hendl;
			return -1;
		}

		tinyxml2::XMLElement* root = doc.FirstChildElement("HeliumExtension");
		if (root == NULL) {
			log << LCRIT << "Failed to get root element of extension config file : " << this->configpath.filename().string() << hendl;
			log << LCRIT << "The extension will not be loaded." << hendl;
			return -1;
		}

		auto* extname = root->FirstChildElement("ExtensionName");
		auto* extfilename = root->FirstChildElement("ExtensionFileName");
		if (extname == NULL) {
			log << LCRIT << "Failed to get \"ExtensionName\" element of extension config file : " << this->configpath.filename().string() << hendl;
			log << LCRIT << "The extension will not be loaded" << hendl;
			return -1;
		}
		if (extfilename == NULL) {
			log << LCRIT << "Failed to get \"ExtensionName\" element of extension config file : " << this->configpath.filename().string() << hendl;
			log << LCRIT << "The extension will not be loaded" << hendl;
			return -1;
		}
		if (extname->GetText() != NULL) {
			this->extname = extname->GetText();
		}
		if (extfilename->GetText() != NULL) {
			string tempstr;
			tempstr.append("./extensions/").append(extfilename->GetText());
			this->extpath = fs::path(tempstr);
		}
		return 0;
	}

	HeliumExtension::HeliumExtension(string cfgname) {
		this->extstat = EXT_STATUS_EMPTY;
		this->config.configpath = fs::path(cfgname);
		log << HLL::LL_INFO << "Reading extension config file : " << this->config.configpath.filename().string() << hendl;
		if (auto ret = this->config.ReadConfig(); ret != 0)
			return;
		this->extuuid = RequestUUID(UUIDInfoType::EXTENSION, (void*)this);
		log << HLL::LL_INFO << "Done." << hendl;
		this->extstat = EXT_STATUS_UNLOADED;
		this->extension_eventmgr = make_shared<HeliumEventManager>();
		return;
	}
	HeliumExtension::~HeliumExtension() {
		this->extstat = EXT_STATUS_EMPTY;
		return;
	}
	int HeliumExtension::LoadExt() {
		this->extstat = EXT_STATUS_LOADING;
		typedef int (*funcptr)();
		log << HLL::LL_INFO << "Try loading extension : " << this->config.extpath.string()
			<< "(" << this->config.extname << ")" << hendl;
		try {
			this->extins.load(this->config.extpath);
		}
		catch (exception& e) {
			log << HLL::LL_ERR << "Extension " << this->config.extname
				<< " loading failed with a exception." << hendl;
			log << HLL::LL_ERR << e.what() << hendl;
			log << "The extension will not be loaded." << hendl;
			this->extstat = EXT_STATUS_EMPTY;
			return -1;
		}
		try {
			this->ScanEventFunc();
			
			list<any> temp_param;
			this->extension_eventmgr->DispatchEvent(HeliumEventList::EXTENSION_LOAD, temp_param);
		}
		catch (exception& e) {
			log << HLL::LL_ERR << "Event listener function scanner for extension " << this->config.extname
				<< " has failed" << hendl;
			log << HLL::LL_ERR << e.what() << hendl;
			log << HLL::LL_ERR << "The extension's behaviour might be incorrect." << hendl;
		}
		this->extstat = EXT_STATUS_LOADED;
		return 0;
	}
	int HeliumExtension::LockExt() {
		return 0;
	}
	int HeliumExtension::UnloadExt() {
		this->extstat = EXT_STATUS_UNLOADING;
		list<any> temp_param;
		this->extension_eventmgr->DispatchEvent(HeliumEventList::EXTENSION_UNLOAD, temp_param);
		this->extstat = EXT_STATUS_UNLOADED;
		return 0;
	}
	int HeliumExtension::UnlockExt() {
		return 0;
	}
	int HeliumExtension::ScanEventFunc() {
		auto ret = 0;
		for (int i = HeliumEventList::EMPTY_EVENT + 1;
			i < HeliumEventList::USER_DEFINED_MIN;
			i++) {
			if (this->extins.has(EventIDToListenerFunc(i))) {
				log << HLL::LL_INFO << "Find a event listener "
					<< EventIDToListenerFunc(i) << " in the extension "
					<< this->config.extname << hendl;
				helium_event_manager.RegisterEventListener(i
					, this->extins.get<int(list<any>)>(EventIDToListenerFunc(i)));
				this->extension_eventmgr->RegisterEventListener(i
					, this->extins.get<int(list<any>)>(EventIDToListenerFunc(i)));
				ret++;
			}
		}
		return ret;
	}
	string HeliumExtension::GetExtName(){
		return this->config.extname;
	}
	void* HeliumExtension::GetFuncPtr(string funcname) {
		if (this->funcs.count(funcname) != 0) {
			return this->funcs.at(funcname);
		}
		return nullptr;
	}
	void* HeliumExtension::SetFuncPtr(string funcname, void* newptr) {
		auto tempptr = this->funcs.at(funcname);
		this->funcs[funcname] = newptr;
		return tempptr;
	}
	bool HeliumExtension::HasFunc(string funcname) {
		if (this->funcs.count(funcname) > 0) return true;
		return false;
	}

	int InitAllExtension() {
		auto ret = 0;
		vector<string> files;
		fs::path extcfgpath("./extensions/extconfigs");
		string tempstr;
		for (auto& fileiter : directory_iterator(extcfgpath)) {
			if (is_directory(fileiter)) continue;
			tempstr = fileiter.path().string();
			if (!tempstr.find(".xml")) continue;
			log << HLL::LL_INFO << "Founded a extension config : " << fileiter.path().filename().string() << hendl;
			files.push_back(tempstr);
			ret++;
		}
		for (auto s : files) {
			HeliumExtension tempext(s);
			log << LDBG << s << hendl;
			extensions.push_back(tempext);
		}
		log << HLL::LL_INFO << "Finished extensions configuration stage." << hendl;
		return ret;
	}
	int LoadAllExtension() {
		auto ret = 0;
		for (auto& ext : extensions) {
			if (!ext.LoadExt()) {
				ret++;
				log << LINFO << "Successfully loaded extension " << ext.GetExtName() << hendl;
			}
			else {
				log << LWARN << "Failed to load extension " << ext.GetExtName() << hendl;
			}
		}
		return ret;
	}
	int UnloadAllExtension() {
		auto ret = 0;
		for (auto& ext : extensions) {
			if (!ext.UnloadExt()) {
				ret++;
				log << LINFO << "Successfully unloaded extension " << ext.GetExtName() << hendl;
			}
			else {
				log << LWARN << "Failed to unload extension " << ext.GetExtName() << hendl;
			}
		}
		return 0;
	}
	int LockAllExtension() {
		return 0;
	}
	int UnlockAllExtension() {
		return 0;
	}
}