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

#include<thread>
#include<windows.h>
#include<boost/uuid/uuid.hpp>
#include<boost/uuid/uuid_io.hpp>
#include<boost/uuid/uuid_generators.hpp>
#include<boost/algorithm/string/classification.hpp>
#include<boost/algorithm/string/split.hpp>
#include<iostream>

module Helium.MinecraftServer:Class;

import <string>;
import <vector>;
import Helium.Logger;
import Helium.Parser;

using namespace std;
using namespace boost;
using namespace boost::uuids;

namespace Helium {
	CRITICAL_SECTION cs;
	vector<thread> outputthreads;
	static bool isinit = false;

	int InitServerEnv() {
		InitializeCriticalSection(&cs);
		return 0;
	}
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

	HeliumServerType HeliumMinecraftServer::GetServerType() {
		return this->type;
	}
	HeliumServerType HeliumMinecraftServer::SetServerType(HeliumServerType type) {
		auto t = this->type;
		this->type = type;

		if (this->parserinited) delete[] this->parser;
		this->parser = GetParserByType(this->type);
		return t;
	}

	HeliumServerStat HeliumMinecraftServer::GetServerStat() {
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
		log << HLL::LL_INFO;
		log << "Successfully generated UUID of server : " << this->name << hendl;
		log << "Server UUID : " << uuidstr << hendl;
		this->serveruuid = serveruuid;
		return this->serveruuid;
	}

	bool HeliumMinecraftServer::IsValid() {
		bool ret = true;
		return ret;
	}

	int HeliumMinecraftServer::StartServer() {
		HeliumEndline hendl;
		
		log << HLL::LL_INFO;
		log << "Starting server " << this->name << "(" << to_string(this->serveruuid) << ")" << hendl;
		log << "Start command : " << this->startcommand << hendl;

		if (this->stat != HeliumServerStat::TERMINATED) {
			log << "Someone are trying to start a non-terminated server : " << this->name << "(" << to_string(this->serveruuid) << ")" << hendl;
			return -1;
		}

		if (!this->IsValid()) {
			log << "Someone are trying to start a invalid server : " << this->name << "(" << to_string(this->serveruuid) << ")" << hendl;
			return -1;
		}

		SECURITY_ATTRIBUTES sa;
		PROCESS_INFORMATION pi;
		STARTUPINFOA si;
		string workingdir;

		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.bInheritHandle = true;
		sa.lpSecurityDescriptor = NULL;

		ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);

		workingdir = this->dir;

		if (!CreatePipe(&this->redir.hStdOutRead, &this->redir.hStdOutWrite, &sa, 0)) {
			log << HLL::LL_ERR << "Failed to create STDOut pipe for server " << this->name << " with error code : " << (long)GetLastError() << hendl;
			return GetLastError();
		}

		if (!CreatePipe(&this->redir.hStdInRead, &this->redir.hStdInWrite, &sa, 0)) {
			log << HLL::LL_ERR << "Failed to create STDIn pipe for server " << this->name << " with error code : " << (long)GetLastError() << hendl;
			return GetLastError();
		}

		if (!SetHandleInformation(this->redir.hStdOutRead, HANDLE_FLAG_INHERIT, 0)) {
			log << HLL::LL_ERR << "Failed to SetHandleInformation() for STDOut for server " << this->name << " with error code : " << (long)GetLastError() << hendl;
			return GetLastError();
		}

		if (!SetHandleInformation(this->redir.hStdInWrite, HANDLE_FLAG_INHERIT, 0)) {
			log << HLL::LL_ERR << "Failed to SetHandleInformation() for STDIn for server " << this->name << " with error code : " << (long)GetLastError() << hendl;
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
			workingdir.c_str(),
			&si,
			&pi); !suc) {
			log << HLL::LL_ERR << "Failed to create process for server " << this->name << " with error code : " << (long)GetLastError() << hendl;
			return GetLastError();
		}
		else {
			CloseHandle(this->redir.hStdOutWrite);
			CloseHandle(this->redir.hStdInRead);

			this->proc = pi.hProcess;
			this->thread = pi.hThread;

			this->stat = HeliumServerStat::PAUSED;

			log << "Successfully started server " << this->name << "(" << to_string(this->serveruuid) << ")" << hendl;
			log << "Server running on PID " << (long)pi.dwProcessId << hendl;

			std::thread outthread(ProcessServerOutput, this, this->name, this->redir.hStdOutRead, this->proc);
			outputthreads.push_back(std::move(outthread));
			outputthreads.back().detach();
		}

		return 0;
	}
	int HeliumMinecraftServer::StopServer() {
		int ret = 0;

		this->stat = HeliumServerStat::TERMINATED;
		return ret;
	}
	int HeliumMinecraftServer::PauseServer() {
		int ret = 0;

		this->stat = HeliumServerStat::PAUSED;
		return ret;
	}
	int HeliumMinecraftServer::ResumeServer() {
		int ret = 0;
		HeliumEndline hendl;

		if (!this->IsValid()) {
			log << HLL::LL_ERR << "Someone are trying to start a invalid server : " << this->name << "(" << to_string(this->serveruuid) << ")" << hendl;
			return -1;
		}

		if (this->stat != HeliumServerStat::PAUSED) {
			log << HLL::LL_ERR << "Someone are trying to start a non-paused server : " << this->name << "(" << to_string(this->serveruuid) << ")" << hendl;
			return -1;
		}

		if (ret = ResumeThread(this->thread); ret == -1) {
			log << HLL::LL_ERR << "Failed to resume process for server " << this->name << " with error code : " << (long)GetLastError() << hendl;
			return GetLastError();
		}

		this->stat = HeliumServerStat::RUNNING;

		return ret;
	}

	void HeliumMinecraftServer::operator = (HeliumMinecraftServer server) {

	}

	HeliumMinecraftServer::HeliumMinecraftServer() {
		this->stat = HeliumServerStat::TERMINATED;
	}
	HeliumMinecraftServer::~HeliumMinecraftServer() {
		if (this->stat != HeliumServerStat::TERMINATED) this->StopServer();
		if (this->parserinited) delete[] this->parser;
	}

	int ProcessServerOutput(HeliumMinecraftServer* ptr, string servername, HANDLE stdread, HANDLE hproc) {
		DWORD dwRead, dwWritten;
		CHAR chBuf[4097];
		BOOL bSuccess = false;

		for (;;)
		{
			bSuccess = ReadFile(stdread, chBuf, 4096, &dwRead, NULL);
			if (!bSuccess) continue;

			chBuf[dwRead - 1] = '\0';
			string output(chBuf);
			vector<string> lines;
			split(lines, output, is_any_of("\n"), token_compress_on);

			for (auto s : lines) { 
				EnterCriticalSection(&cs);
				cout << servername << " > " << s << endl;
				LeaveCriticalSection(&cs);
			}
		}

		return 0;
	}
}