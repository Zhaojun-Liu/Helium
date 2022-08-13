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
#include"Server.h"

namespace HeliumAPI {
	typedef vector<string>(*t1)(int);
	typedef int(*t2)(string, string);
	typedef int(*t3)(string);
	typedef bool(*t4)(string);
	typedef size_t(*t5)(string);
	typedef list<any>(*t6)(string);

	vector<string> GetServerList(const int& mask) {
		t1 ptr = t1(HeliumAPIMap.at("GetServerList"));
		return ptr(mask);
	}
	int SendCommandToServer(const string& servername, const string& rawcmd) {
		t2 ptr = t2(HeliumAPIMap.at("SendCommandToServer"));
		return ptr(servername, rawcmd);
	}
	int GetServerStatus(const string& servername) {
		t3 ptr = t3(HeliumAPIMap.at("GetServerStatus"));
		return ptr(servername);
	}
	int StartServer(const string& servername) {
		t3 ptr = t3(HeliumAPIMap.at("StartServer"));
		return ptr(servername);
	}
	int StopServer(const string& servername) {
		t3 ptr = t3(HeliumAPIMap.at("StopServer"));
		return ptr(servername);
	}
	int PauseServer(const string& servername) {
		t3 ptr = t3(HeliumAPIMap.at("PauseServer"));
		return ptr(servername);
	}
	int RestartServer(const string& servername) {
		t3 ptr = t3(HeliumAPIMap.at("RestartServer"));
		return ptr(servername);
	}
	int ActivateServer(const string& servername) {
		t3 ptr = t3(HeliumAPIMap.at("ActivateServer"));
		return ptr(servername);
	}
	int DeactivateServer(const string& servername) {
		t3 ptr = t3(HeliumAPIMap.at("DeactivateServer"));
		return ptr(servername);
	}
	int StartAllServer() {
		t1 ptr = t1(HeliumAPIMap.at("GetServerList"));
		t3 sptr = t3(HeliumAPIMap.at("StartServer"));
		auto list = ptr(-1);
		auto ret = 0;
		for (auto& str : list) {
			if (sptr(str) == 0) 
				ret++;
		}
		return ret;
	}
	int StopAllServer() {
		t1 ptr = t1(HeliumAPIMap.at("GetServerList"));
		t3 sptr = t3(HeliumAPIMap.at("StopServer"));
		auto list = ptr(-1);
		auto ret = 0;
		for (auto& str : list) {
			if (sptr(str) == 0)
				ret++;
		}
		return ret;
	}
	int PauseAllServer() {
		t1 ptr = t1(HeliumAPIMap.at("GetServerList"));
		t3 sptr = t3(HeliumAPIMap.at("PauseServer"));
		auto list = ptr(-1);
		auto ret = 0;
		for (auto& str : list) {
			if (sptr(str) == 0)
				ret++;
		}
		return ret;
	}
	int RestartAllServer() {
		t1 ptr = t1(HeliumAPIMap.at("GetServerList"));
		t3 sptr = t3(HeliumAPIMap.at("RestartServer"));
		auto list = ptr(-1);
		auto ret = 0;
		for (auto& str : list) {
			if (sptr(str) == 0)
				ret++;
		}
		return ret;
	}
	int ActivateAllServer() {
		t1 ptr = t1(HeliumAPIMap.at("GetServerList"));
		t3 sptr = t3(HeliumAPIMap.at("ActivateServer"));
		auto list = ptr(-1);
		auto ret = 0;
		for (auto& str : list) {
			if (sptr(str) == 0)
				ret++;
		}
		return ret;
	}
	int DeactivateAllServer() {
		t1 ptr = t1(HeliumAPIMap.at("GetServerList"));
		t3 sptr = t3(HeliumAPIMap.at("DeactivateServer"));
		auto list = ptr(-1);
		auto ret = 0;
		for (auto& str : list) {
			if (sptr(str) == 0)
				ret++;
		}
		return ret;
	}
	bool IsServerActivated(const string& servername) {
		t4 ptr = t4(HeliumAPIMap.at("IsServerActivated"));
		return ptr(servername);
	}
	size_t GetServerPID(const string& servername) {
		t5 ptr = t5(HeliumAPIMap.at("GetServerPID"));
		return ptr(servername);
	}
	list<any> GetServerMetadata(const string& servername) {
		t6 ptr = t6(HeliumAPIMap.at("GetServerMetadata"));
		return ptr(servername);
	}
	int Execute(const string& servername, const string& cmd) {
		t2 ptr = t2(HeliumAPIMap.at("Execute"));
		return ptr(servername, cmd);
	}
	int Tell(const string& servername, const string& cmd) {
		t2 ptr = t2(HeliumAPIMap.at("Tell"));
		return ptr(servername, cmd);
	}
	int Say(const string& servername, const string& cmd) {
		t2 ptr = t2(HeliumAPIMap.at("Say"));
		return ptr(servername, cmd);
	}
	int Boardcast(const string& servername, const string& cmd) {
		t2 ptr = t2(HeliumAPIMap.at("Boardcast"));
		return ptr(servername, cmd);
	}
	int Reply(const string& servername, const string& cmd) {
		t2 ptr = t2(HeliumAPIMap.at("Reply"));
		return ptr(servername, cmd);
	}
	int Save(const string& servername) {
		t3 ptr = t3(HeliumAPIMap.at("GetServerList"));
		return ptr(servername);
	}
	bool CanDoCommandAction(const string& servername) {
		t4 ptr = t4(HeliumAPIMap.at("CanDoCommandAction"));
		return ptr(servername);
	}
}