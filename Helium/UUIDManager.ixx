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

#include<boost/uuid/uuid.hpp>
#include<boost/uuid/uuid_generators.hpp>
#include<boost/uuid/uuid_io.hpp>

export module Helium.UUIDManager;

import <map>;
import <memory>;

import Helium.Logger;

using namespace boost::uuids;
using namespace std;

export{
	namespace Helium {
		enum UUIDInfoType {
			SERVER,
			EXTENSION,
			SCRIPT,
			EVENT,
			UNDEF
		};

		struct UUIDInfo
		{
			UUIDInfoType type;
			void* infoptr;
		};

		map<uuid, UUIDInfo> uuidpool;

		uuid RequestUUID(int type, void* infoptr);

		bool IsUUIDExists(uuid uuid);
		int UUIDType(uuid uuid);
		int ChangeUUIDInfo(uuid uuid, int type, void* infoptr);
	}
}

namespace Helium {
	uuid RequestUUID(int type, void* infoptr) {
		random_generator rgen;
		uuid ruuid = rgen();

		UUIDInfo tempinfo;
		tempinfo.type = (UUIDInfoType)type;
		tempinfo.infoptr = infoptr;

		uuidpool[ruuid] = tempinfo;

		log << LINFO << "Generated UUID : " << to_string(ruuid) << " UUID Type : " << type << hendl;

		return ruuid;
	}

	bool IsUUIDExists(uuid uuid) {
		if (uuidpool.count(uuid) > 0) return true;
		return false;
	}
	int UUIDType(uuid uuid) {
		return (int)uuidpool[uuid].type;
	}
	int ChangeUUIDInfo(uuid uuid, int type, void* infoptr) {
		UUIDInfo tempinfo;
		tempinfo.type = (UUIDInfoType)type;
		tempinfo.infoptr = infoptr;
		uuidpool[uuid] = tempinfo;
		return 0;
	}
}