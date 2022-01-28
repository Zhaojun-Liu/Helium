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

#include"minecraftserver.h"
namespace Helium {
	vector<HeliumMinecraftServer> heliumservers;
	CRITICAL_SECTION cs;
	static bool isinit = false;
	HeliumLogger msl("HeliumServerManager");

	string HeliumMinecraftServer::GetServerName() {

	}
	string HeliumMinecraftServer::SetServerName(string name) {

	}

	string HeliumMinecraftServer::GetServerDirectory() {

	}
	string HeliumMinecraftServer::SetServerDirectory(string dir) {

	}

	string HeliumMinecraftServer::GetServerStartCommand() {

	}
	string HeliumMinecraftServer::SetServerStartCommand(string cmd) {

	}

	bool HeliumMinecraftServer::IsAutoStart() {

	}
	bool HeliumMinecraftServer::EnableAutoStart() {

	}
	bool HeliumMinecraftServer::DisableAutoStart() {

	}

	bool HeliumMinecraftServer::IsOutputVisible() {

	}
	bool HeliumMinecraftServer::EnableOutputVisibility() {

	}
	bool HeliumMinecraftServer::DisableOutputVisibility() {

	}

	int HeliumMinecraftServer::GetServerType() {

	}
	int HeliumMinecraftServer::SetServerType(int type) {

	}

	int HeliumMinecraftServer::GetServerStat() {

	}

	uuid HeliumMinecraftServer::GetServerUUID() {

	}

	DWORD HeliumMinecraftServer::GetServerPID() {

	}

	HANDLE HeliumMinecraftServer::GetServerHandle() {

	}
	HANDLE HeliumMinecraftServer::SetServerHandle() {

	}

	DWORD HeliumMinecraftServer::GetServerRetValue() {
	}

	RedirectInformation HeliumMinecraftServer::GetServerRedir() {

	}
	RedirectInformation HeliumMinecraftServer::SetServerRedir(RedirectInformation* redir) {

	}

	uuid HeliumMinecraftServer::GenServerUUID() {

	}

	int ProcessServerOutput(HeliumMinecraftServer* ptr, string servername, HANDLE stdread, HANDLE hproc) {

	}
}