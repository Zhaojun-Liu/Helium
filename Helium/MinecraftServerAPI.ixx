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
import <memory>;
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

		vector<shared_ptr<HeliumMinecraftServer>>::iterator QueryServer(string servername);
		vector<shared_ptr<HeliumMinecraftServer>>::iterator QueryServer(uuid server);
		vector<shared_ptr<HeliumMinecraftServer>>::iterator ServerListBegin();
		vector<shared_ptr<HeliumMinecraftServer>>::iterator ServerListEnd();

		weak_ptr<HeliumMinecraftServer> GetServerPointerByName(const string& servername);
		vector<string> GetServerList(const int& mask = -1);
		int SendCommandToServer(const string& servername, const string& rawcmd);
		int GetServerStatus(const string& servername);
		int _StartServer(const string& servername);
		int _StopServer(const string& servername);
		int _PauseServer(const string& servername);
		int RestartServer(const string& servername);
		int ActivateServer(const string& servername);
		int DeactivateServer(const string& servername);
		bool IsServerActivated(const string& servername);
		size_t GetServerPID(const string& servername);
		list<any> GetServerMetadata(const string& servername);
		int Execute(const string& servername, const string& cmd);
		int Tell(const string& servername, const string& cmd);
		int Say(const string& servername, const string& cmd);
		int Boardcast(const string& servername, const string& cmd);
		int Reply(const string& servername, const string& cmd);

		vector<shared_ptr<HeliumMinecraftServer>> heliumservers;

		void AddServer(HeliumMinecraftServer server) {
			if (server.IsValid())
				heliumservers.push_back(make_shared<HeliumMinecraftServer>(server));
		}
		int StartServer(string name) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if ((*it)->GetServerStat() == HeliumServerStat::TERMINATED 
					&& (*it)->GetServerName() == name)
					return (*it)->StartServer();
			}
			return -1;
		}
		int StartServer(uuid server) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if ((*it)->GetServerStat() == HeliumServerStat::TERMINATED 
					&& (*it)->GetServerUUID() == server)
					return (*it)->StartServer();
			}
			return -1;
		}
		int StartServer() {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if ((*it)->GetServerStat() == HeliumServerStat::TERMINATED) 
					return (*it)->StartServer();
			}
			return -1;
		}
		int StartAllServer() {
			int r = 0;
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if ((*it)->GetServerStat() == HeliumServerStat::TERMINATED)
					if (auto ret = (*it)->StartServer(); ret != 0) r = ret;
			}
			return r;
		}

		int AutoStartServer(string name) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if ((*it)->GetServerStat() == HeliumServerStat::TERMINATED 
					&& (*it)->GetServerName() == name 
					&& (*it)->IsAutoStart()) 
					return (*it)->StartServer();
			}
			return -1;
		}
		int AutoStartServer(uuid server) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if ((*it)->GetServerStat() == HeliumServerStat::TERMINATED 
					&& (*it)->GetServerUUID() == server 
					&& (*it)->IsAutoStart()) 
					return (*it)->StartServer();
			}
			return -1;
		}
		int AutoStartServer() {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if ((*it)->GetServerStat() == HeliumServerStat::TERMINATED 
					&& (*it)->IsAutoStart()) 
					return (*it)->StartServer();
			}
			return -1;
		}
		int AutoStartAllServer() {
			int r = 0;
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if ((*it)->GetServerStat() == HeliumServerStat::TERMINATED 
					&& (*it)->IsAutoStart())
					if (auto ret = (*it)->StartServer(); ret != 0) r = ret;
			}
			return r;
		}

		int StopServer(string name) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if ((*it)->GetServerStat() == HeliumServerStat::RUNNING 
					&& (*it)->GetServerName() == name)
					return (*it)->StopServer();
			}
			return -1;
		}
		int StopServer(uuid server) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if ((*it)->GetServerStat() == HeliumServerStat::RUNNING 
					&& (*it)->GetServerUUID() == server) 
					return (*it)->StopServer();
			}
			return -1;
		}
		int StopServer() {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if ((*it)->GetServerStat() == HeliumServerStat::RUNNING) 
					return (*it)->StopServer();
			}
			return -1;
		}
		int StopAllServer() {
			int r = 0;
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if ((*it)->GetServerStat() != HeliumServerStat::TERMINATED)
					if (auto ret = (*it)->StopServer(); ret != 0) r = ret;
			}
			return r;
		}

		int PauseServer(string name) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if ((*it)->GetServerStat() == HeliumServerStat::RUNNING 
					&& (*it)->GetServerName() == name) 
					return (*it)->PauseServer();
			}
			return -1;
		}
		int PauseServer(uuid server) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if ((*it)->GetServerStat() == HeliumServerStat::RUNNING 
					&& (*it)->GetServerUUID() == server) 
					return (*it)->PauseServer();
			}
			return -1;
		}
		int PauseServer() {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if ((*it)->GetServerStat() == HeliumServerStat::RUNNING) 
					return (*it)->PauseServer();
			}
			return -1;
		}
		int PauseAllServer() {
			int r = 0;
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if ((*it)->GetServerStat() == HeliumServerStat::RUNNING)
					if (auto ret = (*it)->PauseServer(); ret != 0) r = ret;
			}
			return r;
		}

		int ResumeServer(string name) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if ((*it)->GetServerStat() == HeliumServerStat::PAUSED 
					&& (*it)->GetServerName() == name) 
					return (*it)->ResumeServer();
			}
			return -1;
		}
		int ResumeServer(uuid server) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if ((*it)->GetServerStat() == HeliumServerStat::PAUSED 
					&& (*it)->GetServerUUID() == server) 
					return (*it)->ResumeServer();
			}
			return -1;
		}
		int ResumeServer() {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if ((*it)->GetServerStat() == HeliumServerStat::PAUSED)
					return (*it)->ResumeServer();
			}
			return -1;
		}
		int ResumeAllServer() {
			int r = 0;
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if ((*it)->GetServerStat() == HeliumServerStat::PAUSED)
					if (auto ret = (*it)->ResumeServer(); ret != 0) 
						r = ret;
			}
			return r;
		}

		int DeleteServer(string name) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if ((*it)->GetServerName() == name) {
					auto ret = (*it)->StopServer();
					heliumservers.erase(it);
					return ret;
				}
			}
			return -1;
		}
		int DeleteServer(uuid server) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if ((*it)->GetServerUUID() == server) {
					auto ret = (*it)->StopServer();
					heliumservers.erase(it);
					return ret;
				}
			}
			return -1;
		}
		int DeleteServer(int stat) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if ((*it)->GetServerStat() == stat) {
					auto ret = (*it)->StopServer();
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

		vector<shared_ptr<HeliumMinecraftServer>>::iterator QueryServer(string servername) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if ((*it)->GetServerName() == servername) {
					return it;
				}
			}
			return heliumservers.end();
		}
		vector<shared_ptr<HeliumMinecraftServer>>::iterator QueryServer(uuid server) {
			for (auto it = heliumservers.begin(); it < heliumservers.end(); it++) {
				if ((*it)->GetServerUUID() == server) {
					return it;
				}
			}
			return heliumservers.end();
		}
		vector<shared_ptr<HeliumMinecraftServer>>::iterator ServerListBegin() {
			return heliumservers.begin();
		}
		vector<shared_ptr<HeliumMinecraftServer>>::iterator ServerListEnd() {
			return heliumservers.end();
		}

		weak_ptr<HeliumMinecraftServer> GetServerPointerByName(const string& servername) {
			for (auto ptr : heliumservers) {
				if (ptr->GetServerName() == servername)
					return weak_ptr<HeliumMinecraftServer>(ptr);
			}
			return weak_ptr<HeliumMinecraftServer>();
		}
		vector<string> GetServerList(const int& mask) {
			vector<string> ret;
			if (mask != -1) {
				for (auto ptr : heliumservers) {
					if (ptr->GetServerStat() == mask)
						ret.push_back(ptr->GetServerName);
				}
			}
			else {
				for (auto ptr : heliumservers) {
					ret.push_back(ptr->GetServerName());
				}
			}
			return ret;
		}
		int SendCommandToServer(const string& servername, const string& rawcmd) {
			auto wptr = GetServerPointerByName(servername);
			auto ptr = wptr.lock();
			if (ptr) {
				return ptr->SendToServer(rawcmd);
			}
			return -1;
		}
		int GetServerStatus(const string& servername) {
			auto wptr = GetServerPointerByName(servername);
			auto ptr = wptr.lock();
			if (ptr) {
				return ptr->GetServerStat();
			}
			return -1;
		}
		int _StartServer(const string& servername) {
			auto wptr = GetServerPointerByName(servername);
			auto ptr = wptr.lock();
			if (ptr) {
				return ptr->StartServer();
			}
			return -1;
		}
		int _StopServer(const string& servername) {
			auto wptr = GetServerPointerByName(servername);
			auto ptr = wptr.lock();
			if (ptr) {
				return ptr->StopServer();
			}
			return -1;
		}
		int _PauseServer(const string& servername) {
			auto wptr = GetServerPointerByName(servername);
			auto ptr = wptr.lock();
			if (ptr) {
				return ptr->PauseServer();
			}
			return -1;
		}
		int RestartServer(const string& servername) {
			auto wptr = GetServerPointerByName(servername);
			auto ptr = wptr.lock();
			if (ptr) {
				ptr->Save();
				ptr->StopServer();
				return ptr->StartServer();
			}
			return -1;
		}
		int ActivateServer(const string& servername) {
			auto wptr = GetServerPointerByName(servername);
			auto ptr = wptr.lock();
			if (ptr) {
				return ptr->EnableOutputVisibility();
			}
			return -1;
		}
		int DeactivateServer(const string& servername) {
			auto wptr = GetServerPointerByName(servername);
			auto ptr = wptr.lock();
			if (ptr) {
				return ptr->DisableOutputVisibility();
			}
			return -1;
		}
		bool IsServerActivated(const string& servername) {
			auto wptr = GetServerPointerByName(servername);
			auto ptr = wptr.lock();
			if (ptr) {
				return ptr->IsOutputVisible();
			}
			return -1;
		}
		size_t GetServerPID(const string& servername) {
			auto wptr = GetServerPointerByName(servername);
			auto ptr = wptr.lock();
			if (ptr) {
				return ptr->GetServerPID();
			}
			return -1;
		}
		list<any> GetServerMetadata(const string& servername) {
			list<any> ret;
			return ret;
		}
		int Execute(const string& servername, const string& cmd) {
			auto wptr = GetServerPointerByName(servername);
			auto ptr = wptr.lock();
			if (ptr) {
				return ptr->Execute(cmd);
			}
			return -1;
		}
		int Tell(const string& servername, const string& cmd) {
			auto wptr = GetServerPointerByName(servername);
			auto ptr = wptr.lock();
			if (ptr) {
				return ptr->Tell(cmd);
			}
			return -1;
		}
		int Say(const string& servername, const string& cmd) {
			auto wptr = GetServerPointerByName(servername);
			auto ptr = wptr.lock();
			if (ptr) {
				return ptr->Say(cmd);
			}
			return -1;
		}
		int Boardcast(const string& servername, const string& cmd) {
			auto wptr = GetServerPointerByName(servername);
			auto ptr = wptr.lock();
			if (ptr) {
				return ptr->Boardcast(cmd);
			}
			return -1;
		}
		int Reply(const string& servername, const string& cmd) {
			auto wptr = GetServerPointerByName(servername);
			auto ptr = wptr.lock();
			if (ptr) {
				return ptr->Reply(cmd);
			}
			return -1;
		}
	}
}