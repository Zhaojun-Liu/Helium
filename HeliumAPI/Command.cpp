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
	int ExecuteCommand(string rawcmd) {

	}
	void RegisterCommandCallback(HeliumCommandCallback funcptr, uuid cmduuid) {

	}
	uuid AddCommand(list<any> cmdargu, uuid parentuuid, int type = 1, HeliumCommandCallback = nullptr) {

	}
	uuid DeleteCommand(uuid cmduuid) {

	}
	uuid QueryCommand(string cmd) {

	}
	uuid ReplaceCommand(list<any> cmdargu, uuid cmduuid, int type = 1, HeliumCommandCallback = nullptr) {

	}
	uuid GetCommandTreeNodeMetadata(uuid cmduuid) {

	}
}