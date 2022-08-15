/*
* Helium API is dll for remapping Helium API functions.
* You can get the lastest source code and releases of Helium API at :
* https://github.com/Helium-DevTeam/Helium
* ----------------------------------------------------------------------------------------
* Helium Copyright (C) 2021-2022 HeliumDevTeam
*
* This file is a part of Helium API
*
* Helium API is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Helium API is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Helium API.  If not, see <https://www.gnu.org/licenses/>.
* ----------------------------------------------------------------------------------------
*/

#include"pch.h"
#include"Command.h"

using namespace std;

namespace HeliumAPI {
	typedef int(*t1)(string);
	typedef void(*t2)(void*, uuid);
	typedef uuid(*t3)(list<any>, uuid, int, void*);
	typedef uuid(*t4)(uuid);
	typedef uuid(*t5)(string);
	typedef uuid(*t6)(uuid);

	int ExecuteCommand(string rawcmd) {
		auto ptr = t1(HeliumAPIMap.at("ExecuteCommand"));
		return ptr(rawcmd);
	}
	void RegisterCommandCallback(HeliumCommandCallback funcptr, uuid cmduuid) {
		auto ptr = t2(HeliumAPIMap.at("RegisterCommandCallback"));
		return ptr(funcptr, cmduuid);
	}
	uuid AddCommand(list<any> cmdargu, uuid parentuuid, int type, HeliumCommandCallback funcptr) {
		auto ptr = t3(HeliumAPIMap.at("AddCommand"));
		return ptr(cmdargu, parentuuid, type, funcptr);
	}
	uuid DeleteCommand(uuid cmduuid) {
		auto ptr = t4(HeliumAPIMap.at("DeleteCommand"));
		return ptr(cmduuid);
	}
	uuid QueryCommand(string cmd) {
		auto ptr = t5(HeliumAPIMap.at("QueryCommand"));
		return ptr(cmd);
	}
	uuid GetCommandTreeNodeMetadata(uuid cmduuid) {
		auto ptr = t6(HeliumAPIMap.at("GetCommandTreeNodeMetadata"));
		return ptr(cmduuid);
	}
}