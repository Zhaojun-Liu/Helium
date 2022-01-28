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

#include<list>
#include<map>
#include<io.h>
#include<direct.h>

module Helium.InitDirectory;

import <string>;
import Helium.Logger;
import Helium.ErrorExit;

using namespace std;

namespace Helium {
	list<HeliumDirectory> heliumdir;
	map<HeliumDirectoryInitPolicy, HeliumDirectoryInitPolicy> policystat;
	HeliumLogger dirlog("HeliumDirectoryInit");

	int InitHeliumDirectory() {
		HeliumEndline hendl;
		HeliumDirectoryInitPolicy pol;
		int ret = 0;

		for (auto dir : heliumdir) {
			pol = dir.policy;
			if (auto it = policystat.find(dir.policy); it != policystat.end())
				pol = it->second;
			dirlog << HLL::LL_DBG << dir.dirpath << hendl;
			if (_access(dir.dirpath.c_str(), 0) != 0) {
				switch (pol)
				{
				case Helium::HDIP_BLOCKED:
					break;
				case Helium::HDIP_CREATE_WARING:
					dirlog << HLL::LL_WARN << dir.extrahint << hendl;
					ret = _mkdir(dir.dirpath.c_str());
					break;
				case Helium::HDIP_CREATE_SLIENT:
					ret = _mkdir(dir.dirpath.c_str());
					break;
				case Helium::HDIP_CREATE_QUIT:
					ret = _mkdir(dir.dirpath.c_str());
					HeliumErrorExit(true, true, dir.extrahint);
					break;
				case Helium::HDIP_IGNORE_WARING:
					dirlog << HLL::LL_WARN << dir.extrahint << hendl;
					break;
				case Helium::HDIP_IGNORE_SLIENT:
					break;
				case Helium::HDIP_IGNORE_QUIT:
					HeliumErrorExit(true, true, dir.extrahint);
					break;
				default:
					break;
				}
			}
		}
		return ret;
	}
	int AddHeliumDirectory(string path, string hint, HeliumDirectoryInitPolicy policy) {
		HeliumEndline hendl;
		dirlog << HLL::LL_DBG << path << hendl;
		HeliumDirectory dir{ .dirpath = path, .extrahint = hint, .policy = policy };
		heliumdir.push_back(dir);
		return 0;
	}
	int AddHeliumDirectory(HeliumDirectory* dir) {
		heliumdir.push_back(*dir);
		return 0;
	}
	int DeleteHeliumDirectory(string path) {
		for (auto it = heliumdir.begin(); it != heliumdir.end(); it ++) {
			if (it->dirpath == path) heliumdir.erase(it);
		}
		return 0;
	}
	int BlockPolicy(HeliumDirectoryInitPolicy policy) {
		policystat[policy] = HDIP::HDIP_BLOCKED;
		return 0;
	}
	int ReplacePolicy(HeliumDirectoryInitPolicy policy, HeliumDirectoryInitPolicy replace) {
		policystat[policy] = replace;
		return 0;
	}
}