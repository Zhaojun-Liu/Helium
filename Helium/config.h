/*
* Helium Pre-Alpha 0.6.1
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

#ifndef _H_CONFIG
#define _H_CONFIG

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include<string>
#include<vector>
#include<variant>
#include<spdlog/spdlog.h>

#include"tinyxml2/tinyxml2.h"
#include"xmlutils.h"
#include"minecraftserver.h"
#include"logger.h"

namespace Helium {

#define CFG_FILENAME "HeliumConfig.xml"
#define gnsbn(name) GetNodeStringByName(pRootEle,name)

	using namespace std;

	static const char* boolstr[] = { "True", "False" };
#define VALUE_TYPE_INTEGER 0
#define VALUE_TYPE_DOUBLE 1
#define VALUE_TYPE_STRING 2
#define VALUE_TYPE_BOOLEAN 3

	struct ConfigNode
	{
		string nodename;
		int valuetype = VALUE_TYPE_INTEGER;
		variant<int, double, string, bool> var;

		int Print();
	};

	struct HeliumAttribute {
		string nodename;
		int valuetype = VALUE_TYPE_INTEGER;
		variant<int, double, string, bool> var;
	};

	extern vector<HeliumAttribute> attrlist;

	int _stdcall SaveConfigFile();
	int _stdcall CreateConfigFile();
	int _stdcall ReadConfigFile();
	int _stdcall Config();

#define START_CONFIG_NODES_REGISTER vector<ConfigNode> _confignodes_
#define ADD_CONFIG_NODE(nodenamestr, _nodename, _valuetype, defaultvalue) ConfigNode _newnode_##_nodename##_;\
_newnode_##_nodename##_.nodename = nodenamestr;\
_newnode_##_nodename##_.valuetype = _valuetype;\
_newnode_##_nodename##_.var.emplace<_valuetype>(defaultvalue);\
_confignodes_.push_back(_newnode_##_nodename##_);
}
#endif // !_H_CONFIG
