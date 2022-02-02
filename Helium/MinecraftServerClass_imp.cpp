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
#include<boost/uuid/uuid_io.hpp>
#include<boost/uuid/uuid_generators.hpp>

module Helium.MinecraftServer:Class;

import <string>;
import <vector>;
import Helium.Logger;
import Helium.Parser;

using namespace std;
using namespace boost::uuids;

namespace Helium {
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
	HANDLE HeliumMinecraftServer::GetServerThreadHandle() {
		return this->thread;
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

	bool HeliumMinecraftServer::IsRCONEnabled() {
		return this->rcon.isenabled;
	}
	bool HeliumMinecraftServer::EnableRCON() {
		auto r = this->rcon.isenabled;
		this->rcon.isenabled = true;
		return r;
	}
	bool HeliumMinecraftServer::DisableRCON() {
		auto r = this->rcon.isenabled;
		this->rcon.isenabled = false;
		return r;
	}

	int HeliumMinecraftServer::GetRCONPort() {
		return this->rcon.port;
	}
	int HeliumMinecraftServer::SetRCONPort(int port) {
		auto r = this->rcon.port;
		this->rcon.port = port;
		return r;
	}

	string HeliumMinecraftServer::GetRCONPassword() {
		return this->rcon.pwd;
	}
	string HeliumMinecraftServer::SetRCONPassword(string pwd) {
		auto r = this->rcon.pwd;
		this->rcon.pwd = pwd;
		return r;
	}

	uuid HeliumMinecraftServer::GenServerUUID() {
		uuid serveruuid = random_generator()();
		string uuidstr = to_string(serveruuid);
		HeliumEndline hendl;
		lg << "Successfully generated UUID of server : " << this->name << hendl;
		lg << "UUID : " << uuidstr << hendl;
		this->serveruuid = serveruuid;
		return this->serveruuid;
	}

	bool HeliumMinecraftServer::IsValid() {
		bool ret = true;
		return ret;
	}

	int HeliumMinecraftServer::StartServer() {
		HeliumEndline hendl;
		
		lg << "Starting server " << this->name << "(" << to_string(this->serveruuid) << ")" << hendl;
		lg << "Start command : " << this->startcommand << hendl;

		if (this->stat != HeliumServerStat::TERMINATED) {
			lg << "Someone are trying to start a non-terminated server : " << this->name << "(" << to_string(this->serveruuid) << ")" << hendl;
			return -1;
		}

		if (!this->IsValid()) {
			lg << "Someone are trying to start a invalid server : " << this->name << "(" << to_string(this->serveruuid) << ")" << hendl;
			return -1;
		}

		SECURITY_ATTRIBUTES sa;
		PROCESS_INFORMATION pi;
		STARTUPINFOA si;

		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.bInheritHandle = true;
		sa.lpSecurityDescriptor = NULL;

		ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);

		if (!CreatePipe(&this->redir.hStdOutRead, &this->redir.hStdOutWrite, &sa, 0)) {
			lg << "Failed to create STDOut pipe for server " << this->name << " with error code : " << (long)GetLastError() << hendl;
			return GetLastError();
		}

		if (!CreatePipe(&this->redir.hStdInRead, &this->redir.hStdInWrite, &sa, 0)) {
			lg << "Failed to create STDIn pipe for server " << this->name << " with error code : " << (long)GetLastError() << hendl;
			return GetLastError();
		}

		if (!SetHandleInformation(this->redir.hStdOutRead, HANDLE_FLAG_INHERIT, 0)) {
			lg << "Failed to SetHandleInformation() for STDOut for server " << this->name << " with error code : " << (long)GetLastError() << hendl;
			return GetLastError();
		}

		if (!SetHandleInformation(this->redir.hStdInWrite, HANDLE_FLAG_INHERIT, 0)) {
			lg << "Failed to SetHandleInformation() for STDIn for server " << this->name << " with error code : " << (long)GetLastError() << hendl;
			return GetLastError();
		}

		si.hStdError = this->redir.hStdOutWrite;
		si.hStdOutput = this->redir.hStdOutWrite;
		si.hStdInput = this->redir.hStdInRead;
		si.dwFlags |= STARTF_USESTDHANDLES;

		if (auto suc = CreateProcessA(NULL,
			const_cast<char*>(this->startcommand.c_str()),
			NULL,
			NULL,
			true,
			CREATE_SUSPENDED|CREATE_NO_WINDOW,
			NULL,
			NULL,
			&si,
			&pi); !suc) {
			lg << "Failed to create process for server " << this->name << " with error code : " << (long)GetLastError() << hendl;
			return GetLastError();
		}
		else {
			CloseHandle(this->redir.hStdOutWrite);
			CloseHandle(this->redir.hStdInRead);

			this->proc = pi.hProcess;
			this->thread = pi.hThread;

			this->stat = HeliumServerStat::PAUSED;

			lg << "Successfully started server " << this->name << "(" << to_string(this->serveruuid) << ")" << hendl;
			lg << "Server running on PID " << (long)pi.dwProcessId << hendl;
		}

		return 0;
	}
	int HeliumMinecraftServer::StopServer() {
		int ret = 0;
		return ret;
	}
	int HeliumMinecraftServer::PauseServer() {
		int ret = 0;
		return ret;
	}
	int HeliumMinecraftServer::ResumeServer() {
		int ret = 0;
		HeliumEndline hendl;

		if (!this->IsValid()) {
			lg << "Someone are trying to start a invalid server : " << this->name << "(" << to_string(this->serveruuid) << ")" << hendl;
			return -1;
		}

		if (this->stat != HeliumServerStat::PAUSED) {
			lg << "Someone are trying to start a non-paused server : " << this->name << "(" << to_string(this->serveruuid) << ")" << hendl;
			return -1;
		}

		if (ret = ResumeThread(this->thread); ret == -1) {
			lg << "Failed to resume process for server " << this->name << " with error code : " << (long)GetLastError() << hendl;
			return GetLastError();
		}

		return ret;
	}

	void HeliumMinecraftServer::operator = (HeliumMinecraftServer server) {

	}

	HeliumMinecraftServer::HeliumMinecraftServer() {

	}
	HeliumMinecraftServer::~HeliumMinecraftServer() {

	}

	int ProcessServerOutput(HeliumMinecraftServer* ptr, string servername, HANDLE stdread, HANDLE hproc) {
		return 0;
	}
}