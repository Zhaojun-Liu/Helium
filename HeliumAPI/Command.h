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

#pragma once

#include"pch.h"
#include<boost/uuid/uuid.hpp>
#include<boost/uuid/uuid_generators.hpp>

using namespace std;
using namespace boost::uuids;

namespace HeliumAPI {
	typedef int (*HeliumCommandCallback)(string rawcmd, string sender, int permission, list<any> arguments);

	int ExecuteCommand(string rawcmd);
	void RegisterCommandCallback(HeliumCommandCallback funcptr, boost::uuids::uuid cmduuid);
	boost::uuids::uuid AddCommand(list<any> cmdargu, boost::uuids::uuid parentuuid = nil_generator()(), int type = 1, HeliumCommandCallback funcptr = nullptr);
	boost::uuids::uuid DeleteCommand(boost::uuids::uuid cmduuid);
	boost::uuids::uuid QueryCommand(string cmd);
	boost::uuids::uuid GetCommandTreeNodeMetadata(boost::uuids::uuid cmduuid);
}