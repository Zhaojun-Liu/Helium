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

export{
	namespace Helium {
		void HeliumExtensionDebugPrint(string extprint);

		class HeliumExtension {
		public:
			HeliumExtension(string cfgname);
			~HeliumExtension();

			int LoadExt();
			int LockExt();
			int UnlockExt();
			int UnloadExt();
			int ScanEventFunc();
			int SendExportFuncMap();

			enum ExtStat {
				EXT_STATUS_EMPTY,
				EXT_STATUS_LOADING,
				EXT_STATUS_LOADED,
				EXT_STATUS_UNLOADING,
				EXT_STATUS_UNLOADED,
				EXT_STATUS_LOCKED
			};

			class HeliumExtensionFuncs {

			};

			class HeliumExtensionConfig {
			public:
				_declspec(property(get = GetExtConfigPath, put = PutExtConfigPath)) string Extconfigpath;
				_declspec(property(get = GetExtName, put = PutExtName)) string Extname;

				string _stdcall GetExtConfigPath() {
					return configpath;
				}
				void _stdcall PutExtConfigPath(string path) {
					this->configpath = path;
				}

				string _stdcall GetExtName() {
					return configpath;
				}
				void _stdcall PutExtName(string path) {
					this->configpath = path;
				}

				int ReadConfig();
			private:
				string configpath;
				string extname;
			};
		private:
			HeliumExtensionConfig config;
			HeliumExtensionFuncs funcs;
			int extstat;
			uuid extuuid;
			string name;
		};

		void HeliumExtensionDebugPrint(string extprint) {
			HeliumEndline hendl;
			log << "Debug print from extension : " << extprint << hendl;
		}

		int HeliumExtension::HeliumExtensionConfig::ReadConfig() {
			HeliumEndline hendl;
			tinyxml2::XMLDocument doc;
			if (auto ret = doc.LoadFile(this->configpath.c_str()); ret != tinyxml2::XMLError::XML_SUCCESS) {
				log << HLL::LL_WARN << "Failed to load extension config file : " << this->configpath << hendl;
				return -1;
			}

			tinyxml2::XMLElement* root = doc.RootElement();
			if (root == NULL) {
				log << HLL::LL_WARN << "Failed to get root element of extension config file : " << this->configpath << hendl;
				return -1;
			}
			return 0;
		}

		HeliumExtension::HeliumExtension(string cfgname) {
			HeliumEndline hendl;
			this->extstat = EXT_STATUS_EMPTY;
			this->config.Extconfigpath.append("./extensions/extconfigs").append(cfgname).append(".xml");
			log << HLL::LL_INFO << "Reading extension config file : " << cfgname << ".xml" << hendl;
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
		int HeliumExtension::SendExportFuncMap() {
			return 0;
		}
	}
}