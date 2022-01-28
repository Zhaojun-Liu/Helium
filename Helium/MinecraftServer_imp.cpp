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

#include<windows.h>
#include<boost/uuid/uuid.hpp>
#include<vector>

module Helium.MinecraftServer;

import <string>;
import Helium.Logger;

using namespace std;
using namespace boost::uuids;

namespace Helium {
	//vector<HeliumMinecraftServer> heliumservers();
	CRITICAL_SECTION cs;
	static bool isinit = false;
	HeliumLogger msl("HeliumServerManager");

	string HeliumMinecraftServer::GetServerName() {
		return this->name;
	}
	string HeliumMinecraftServer::SetServerName(string name) {
		string temps = this->name;
		this->name = name;
		return temps;
	}

	string HeliumMinecraftServer::GetServerDirectory() {
		return this->dir;
	}
	string HeliumMinecraftServer::SetServerDirectory(string dir) {
		string temps = this->dir;
		this->dir = dir;
		return temps;
	}

	string HeliumMinecraftServer::GetServerStartCommand() {
		return this->startcommand;
	}
	string HeliumMinecraftServer::SetServerStartCommand(string cmd) {
		string temps = this->startcommand;
		this->startcommand = cmd;
		return temps;
	}

	bool HeliumMinecraftServer::IsAutoStart() {
		return this->autostart;
	}
	bool HeliumMinecraftServer::EnableAutoStart() {
		bool t = this->autostart;
		this->autostart = true;
		return t;
	}
	bool HeliumMinecraftServer::DisableAutoStart() {
		bool t = this->autostart;
		this->autostart = false;
		return t;
	}

	bool HeliumMinecraftServer::IsOutputVisible() {
		return this->visi;
	}
	bool HeliumMinecraftServer::EnableOutputVisibility() {
		bool t = this->visi;
		this->visi = true;
		return t;
	}
	bool HeliumMinecraftServer::DisableOutputVisibility() {
		bool t = this->visi;
		this->visi = false;
		return t;
	}

	int HeliumMinecraftServer::GetServerType() {
		return this->type;
	}
	int HeliumMinecraftServer::SetServerType(int type) {
		int t = this->type;
		this->type = type;
		return t;
	}

	int HeliumMinecraftServer::GetServerStat() {
		return this->stat;
	}

	uuid HeliumMinecraftServer::GetServerUUID() {
		return this->serveruuid;
	}

	DWORD HeliumMinecraftServer::GetServerPID() {
		return this->pid;
	}

	HANDLE HeliumMinecraftServer::GetServerHandle() {
		return this->proc;
	}
	void HeliumMinecraftServer::SetServerHandle(HANDLE han) {
		this->proc = han;
	}

	DWORD HeliumMinecraftServer::GetServerRetValue() {
		return this->retv;
	}

	RedirectInformation HeliumMinecraftServer::GetServerRedir() {
		return this->redir;
	}
	RedirectInformation HeliumMinecraftServer::SetServerRedir(RedirectInformation* redir) {
		RedirectInformation r = this->redir;
		this->redir = *redir;
		return r;
	}

	uuid HeliumMinecraftServer::GenServerUUID() {
		return this->serveruuid;
	}

	int ProcessServerOutput(HeliumMinecraftServer* ptr, string servername, HANDLE stdread, HANDLE hproc) {
		return 0;
	}
}