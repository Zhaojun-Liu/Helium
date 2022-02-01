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

export module Helium.Config;

#define _HAS_CXX20
#define CFG_FILENAME "HeliumConfig.xml"

import <string>;
import <vector>;
import <strstream>;

import "tinyxml2/tinyxml2.h";
import "boost/uuid/uuid.hpp";

using namespace std;
using namespace tinyxml2;
using namespace boost::uuids;

import Helium.MinecraftServer;

export{
	namespace Helium {
		enum HeliumLanguage {
			en_US,
			zh_CN
		};

		enum HeliumPermissionLevel {
			GUEST,
			USER,
			ADMIN,
			SERVEROWNER,
			HELIUMOWNER
		};

		struct HeliumSetting {
			int Language;
			string Encoding;
			string ExtDir;
			string ScrDir;
			bool AutoUpdate;
		};

		struct PermissionNamespace {
			string servername;
			uuid serveruuid;
			int defaultpermission;
			vector<pair<string, int>> permissions;
		};

		int ReadHeliumConfig();
		int CreateHeliumConfig();

		int GetLanguage();
		string GetEncoding();
		string GetExtensionDirectory();
		string GetScriptDirectory();
		bool IsAutoUpdate();
		int QueryPermission(string server, string name);
		int QueryPermission(uuid server, string name);
		int QueryDefaultPermission(string server);
		int QueryDefaultPermission(uuid server);
	}
}

module : private;

namespace Helium {
	HeliumSetting Settings;
	vector<PermissionNamespace> Permissions;
	const char* permdescstr[] = { "Guest", "User", "Admin", "ServerOwner", "HeliumOwner" };
}