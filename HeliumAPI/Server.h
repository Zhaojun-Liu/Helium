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

using namespace std;

namespace HeliumAPI {
	vector<string> GetServerList(const int& mask = -1);
	int SendCommandToServer(const string& servername, const string& rawcmd);
	int GetServerStatus(const string& servername);
	int StartServer(const string& servername);
	int StopServer(const string& servername);
	int PauseServer(const string& servername);
	int RestartServer(const string& servername);
	int ActivateServer(const string& servername);
	int DeactivateServer(const string& servername);
	int StartAllServer();
	int StopAllServer();
	int PauseAllServer();
	int RestartAllServer();
	int ActivateAllServer();
	int DeactivateAllServer();
	bool IsServerActivated(const string& servername);
	size_t GetServerPID(const string& servername);
	list<any> GetServerMetadata(const string& servername);
	int Execute(const string& servername, const string& cmd);
	int Tell(const string& servername, const string& cmd);
	int Say(const string& servername, const string& cmd);
	int Boardcast(const string& servername, const string& cmd);
	int Reply(const string& servername, const string& cmd);
	int Save(const string& servername);
	bool CanDoCommandAction(const string& servername);
}