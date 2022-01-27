/*
* Helium
* Copyright (C) 2021-2022 HeliumDevTeam
*
* Helium is a customizable extension system for Minecraft server which is written in C++.
* This project is inspired by the [Fallen-Breath/MCDReforged](https://github.com/Fallen-Breath/MCDReforged).
* We target to provide a liter, faster, and more customizable choice.
* As a trade-off, we sacrifice its portability and the simplicity of writing extensions.
* (we r sry that we haven't finish the first alpha version yet, if u r interested in our project, we recommend u to use mcdr as a temporary alternative)
* This project is licensed by the GPL-3.0-or-later license.
*
* Very very special thank to contributors of the following projects:
* [Fallen-Breath/MCDReforged](https://github.com/Fallen-Breath/MCDReforged)
* [kpeeters/tree.hh](https://github.com/kpeeters/tree.hh)
* [leethomason/tinyxml2](https://github.com/leethomason/tinyxml2/)
* [jcwangxp/Crossline](https://github.com/jcwangxp/Crossline/)
*
* You can get the lastest source code and releases of Helium at :
* https://github.com/Minecraft1248/Helium
*
* -------------------------------------------------------------------------------------------------------------------------------------------------------
*    This file is part of Helium.
*
*    Helium is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    Helium is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with Helium.  If not, see <https://www.gnu.org/licenses/>.
* -------------------------------------------------------------------------------------------------------------------------------------------------------
*/

#pragma once

#ifndef _H_HELIUMCONFIG
#define _H_HELIUMCONFIG

#define CFG_FILENAME "HeliumConfig.xml"

#include<string>
#include<vector>
#include<strstream>

#include"tinyxml2/tinyxml2.h"
#include"boost/uuid/uuid.hpp"

#include"logger.h"
#include"xmlutils.h"
#include"minecraftserver.h"
#include"utils.h"

namespace Helium {
	using namespace tinyxml2;
	using namespace boost::uuids;
	using namespace std;

#define en_US 0
#define zh_CN 1

#define PERMISSION_LEVEL_GUEST			0
#define PERMISSION_LEVEL_USER			1
#define PERMISSION_LEVEL_ADMIN			2
#define PERMISSION_LEVEL_SERVEROWNER	3
#define PERMISSION_LEVEL_HELIUMOWNER	4

	struct HeliumSetting {
		int Language;
		string Encoding;
		string ExtDir;
		string ScrDir;
		bool rconEnable;
		int rconPort;
		string rconPassword;
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
}

#endif // !_H_HELIUMCONFIG
