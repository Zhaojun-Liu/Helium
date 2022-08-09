/*
* Helium is a customizable extension system for Minecraft server.
* You can get the lastest source code and releases of Helium at :
* https://github.com/Helium-DevTeam/Helium
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

#define WIN32_LEAN_AND_MEAN

#include<boost/uuid/uuid.hpp>
#include<windows.h>

export module Helium.MinecraftServer:API;

import :Class;
import <string>;
import <vector>;

using namespace std;
using namespace boost::uuids;

export {
	namespace Helium {
		void AddServer(HeliumMinecraftServer server);
		int StartServer(string name);
		int StartServer(uuid server);
		int StartServer();
		int StartAllServer();

		int AutoStartServer(string name);
		int AutoStartServer(uuid server);
		int AutoStartServer();
		int AutoStartAllServer();

		int StopServer(string name);
		int StopServer(uuid server);
		int StopServer();
		int StopAllServer();

		int PauseServer(string name);
		int PauseServer(uuid server);
		int PauseServer();
		int PauseAllServer();

		int ResumeServer(string name);
		int ResumeServer(uuid server);
		int ResumeServer();
		int ResumeAllServer();

		int DeleteServer(string name);
		int DeleteServer(uuid server);
		int DeleteServer(int stat);
		void ClearServerList();

		vector<HeliumMinecraftServer>::iterator QueryServer(string servername);
		vector<HeliumMinecraftServer>::iterator QueryServer(uuid server);
		vector<HeliumMinecraftServer>::iterator ServerListBegin();
		vector<HeliumMinecraftServer>::iterator ServerListEnd();

		vector<HeliumMinecraftServer> heliumservers;

		void AddServer(HeliumMinecraftServer server) {
			if (server.IsValid())
				heliumservers.push_back(server);
		}
		int StartServer(string name) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if (it->GetServerStat() == HeliumServerStat::TERMINATED && it->GetServerName() == name) return it->StartServer();
			}
			return -1;
		}
		int StartServer(uuid server) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if (it->GetServerStat() == HeliumServerStat::TERMINATED && it->GetServerUUID() == server) return it->StartServer();
			}
			return -1;
		}
		int StartServer() {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if (it->GetServerStat() == HeliumServerStat::TERMINATED) return it->StartServer();
			}
			return -1;
		}
		int StartAllServer() {
			int r = 0;
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if (it->GetServerStat() == HeliumServerStat::TERMINATED)
					if (auto ret = it->StartServer(); ret != 0) r = ret;
			}
			return r;
		}

		int AutoStartServer(string name) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if (it->GetServerStat() == HeliumServerStat::TERMINATED && it->GetServerName() == name && it->IsAutoStart()) return it->StartServer();
			}
			return -1;
		}
		int AutoStartServer(uuid server) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if (it->GetServerStat() == HeliumServerStat::TERMINATED && it->GetServerUUID() == server && it->IsAutoStart()) return it->StartServer();
			}
			return -1;
		}
		int AutoStartServer() {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if (it->GetServerStat() == HeliumServerStat::TERMINATED && it->IsAutoStart()) return it->StartServer();
			}
			return -1;
		}
		int AutoStartAllServer() {
			int r = 0;
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if (it->GetServerStat() == HeliumServerStat::TERMINATED && it->IsAutoStart())
					if (auto ret = it->StartServer(); ret != 0) r = ret;
			}
			return r;
		}

		int StopServer(string name) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if (it->GetServerStat() == HeliumServerStat::RUNNING && it->GetServerName() == name) return it->StopServer();
			}
			return -1;
		}
		int StopServer(uuid server) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if (it->GetServerStat() == HeliumServerStat::RUNNING && it->GetServerUUID() == server) return it->StopServer();
			}
			return -1;
		}
		int StopServer() {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if (it->GetServerStat() == HeliumServerStat::RUNNING) return it->StopServer();
			}
			return -1;
		}
		int StopAllServer() {
			int r = 0;
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if (it->GetServerStat() != HeliumServerStat::TERMINATED)
					if (auto ret = it->StopServer(); ret != 0) r = ret;
			}
			return r;
		}

		int PauseServer(string name) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if (it->GetServerStat() == HeliumServerStat::RUNNING && it->GetServerName() == name) return it->PauseServer();
			}
			return -1;
		}
		int PauseServer(uuid server) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if (it->GetServerStat() == HeliumServerStat::RUNNING && it->GetServerUUID() == server) return it->PauseServer();
			}
			return -1;
		}
		int PauseServer() {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if (it->GetServerStat() == HeliumServerStat::RUNNING) return it->PauseServer();
			}
			return -1;
		}
		int PauseAllServer() {
			int r = 0;
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if (it->GetServerStat() == HeliumServerStat::RUNNING)
					if (auto ret = it->PauseServer(); ret != 0) r = ret;
			}
			return r;
		}

		int ResumeServer(string name) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if (it->GetServerStat() == HeliumServerStat::PAUSED && it->GetServerName() == name) return it->ResumeServer();
			}
			return -1;
		}
		int ResumeServer(uuid server) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if (it->GetServerStat() == HeliumServerStat::PAUSED && it->GetServerUUID() == server) return it->ResumeServer();
			}
			return -1;
		}
		int ResumeServer() {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if (it->GetServerStat() == HeliumServerStat::PAUSED) return it->ResumeServer();
			}
			return -1;
		}
		int ResumeAllServer() {
			int r = 0;
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if (it->GetServerStat() == HeliumServerStat::PAUSED)
					if (auto ret = it->ResumeServer(); ret != 0) r = ret;
			}
			return r;
		}

		int DeleteServer(string name) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if (it->GetServerName() == name) {
					auto ret = it->StopServer();
					heliumservers.erase(it);
					return ret;
				}
			}
			return -1;
		}
		int DeleteServer(uuid server) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if (it->GetServerUUID() == server) {
					auto ret = it->StopServer();
					heliumservers.erase(it);
					return ret;
				}
			}
			return -1;
		}
		int DeleteServer(int stat) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if (it->GetServerStat() == stat) {
					auto ret = it->StopServer();
					heliumservers.erase(it);
					return ret;
				}
			}
			return -1;
		}
		void ClearServerList() {
			StopAllServer();
			heliumservers.clear();
		}

		vector<HeliumMinecraftServer>::iterator QueryServer(string servername) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if (it->GetServerName() == servername) {
					return it;
				}
			}
			return heliumservers.end();
		}
		vector<HeliumMinecraftServer>::iterator QueryServer(uuid server) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if (it->GetServerUUID() == server) {
					return it;
				}
			}
			return heliumservers.end();
		}
		vector<HeliumMinecraftServer>::iterator ServerListBegin() {
			return heliumservers.begin();
		}
		vector<HeliumMinecraftServer>::iterator ServerListEnd() {
			return heliumservers.end();
		}
	}
}