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

#include<string>
#include<vector>
#include<iostream>
#include<map>
#include<spdlog/spdlog.h>
#include<boost/dll.hpp>

#include"tinyxml2/tinyxml2.h"

export module Helium.Extension;

import Helium.Events;

using namespace std;

export{
	namespace Helium {
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

		class HeliumExtensionFuncs {

		};

		class HeliumExtension {
			friend class HeliumExtensionConfig;
			friend class HeliumExtensionFuncs;

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
		private:
			HeliumExtensionConfig config;
			HeliumExtensionFuncs funcs;
			int extstat;
			vector<HeliumEventInstance*> EventQueue;
		};
	}
}