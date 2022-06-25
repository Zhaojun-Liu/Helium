/*
* Helium is a customizable extension system for Minecraft server.
* You can get the lastest source code and releases of Helium at :
* https://github.com/Minecraft1248/Helium
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

#include<vector>
#include<map>
#include<spdlog/spdlog.h>
#include<boost/dll.hpp>
#include<boost/uuid/uuid.hpp>
#include<boost/uuid/uuid_io.hpp>
#include<boost/uuid/uuid_generators.hpp>

#include"tinyxml2/tinyxml2.h"

export module Helium.Extension;

import <string>;
import Helium.Logger;

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

			}
			HeliumExtension(string cfgname);
			~HeliumExtension();

			int LoadExt();
			int LockExt();
			int UnlockExt();
			int UnloadExt();
			int ScanEventFunc();
			string GetExtName();

			class HeliumExtensionFuncs {
				friend class HeliumExtension;
			};

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
				fs::path extname;
			};

		private:
			HeliumExtensionConfig config;
			HeliumExtensionFuncs funcs;
			int extstat;
			uuid extuuid;
			string name;
			shared_library extins;
			fs::path extpath;
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
			log << HLL::LL_WARN << "Failed to load extension config file : " << this->configpath.filename().string() << hendl;
			return -1;
		}

		tinyxml2::XMLElement* root = doc.RootElement();
		if (root == NULL) {
			log << HLL::LL_WARN << "Failed to get root element of extension config file : " << this->configpath.filename().string() << hendl;
			return -1;
		}
		return 0;
	}

	HeliumExtension::HeliumExtension(string cfgname) {
		this->extstat = EXT_STATUS_EMPTY;
		this->config.configpath = fs::path(cfgname);
		log << HLL::LL_INFO << "Reading extension config file : " << this->config.configpath.filename().string() << hendl;
		if (auto ret = this->config.ReadConfig(); ret != 0)
			return;
		log << HLL::LL_INFO << "Done." << hendl;
		this->extstat = EXT_STATUS_UNLOADED;
		uuid extuuid = random_generator()();
		this->extuuid = extuuid;
		return;
	}
	HeliumExtension::~HeliumExtension() {
		this->extstat = EXT_STATUS_EMPTY;
		return;
	}
	int HeliumExtension::LoadExt() {
		log << HLL::LL_INFO << "Enter LoadExt()" << hendl;
		this->extpath = "./TestExtension.dll";
		this->extins.load(this->extpath);
		if (this->extins.has("ExtensionLoad")) {
			log << HLL::LL_INFO << "Try to get ExtensionLoad()'s pointer" << hendl;
			auto& symbol = this->extins.get<int()>("ExtensionLoad");
			symbol();
		}
		else {
			log << HLL::LL_WARN << "Cannot find ExtensionLoad() in TestExtension" << hendl;
		}
		return 0;
	}
	int HeliumExtension::LockExt() {
		return 0;
	}
	int HeliumExtension::UnloadExt() {
		return 0;
	}
	int HeliumExtension::UnlockExt() {
		return 0;
	}
	int HeliumExtension::ScanEventFunc() {
		return 0;
	}
	string HeliumExtension::GetExtName(){
		return this->name;
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
		return ret;
	}
	int LoadAllExtension() {
		auto ret = 0;
		for (auto& ext : extensions) {
			if (!ext.LoadExt()) {
				ret++;
				log << LINFO << "Successfully loaded extension : " << ext.GetExtName() << hendl;
			}
			else {
				log << LWARN << "Failed to load extension : " << ext.GetExtName() << hendl;
			}
		}
		return ret;
	}
	int UnloadAllExtension() {
		return 0;
	}
	int LockAllExtension() {
		return 0;
	}
	int UnlockAllExtension() {
		return 0;
	}
}