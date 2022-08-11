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

#include<thread>
#include<boost/uuid/uuid.hpp>
#include<boost/uuid/uuid_io.hpp>
#include<boost/uuid/uuid_generators.hpp>
#include<boost/algorithm/string/classification.hpp>
#include<boost/algorithm/string/split.hpp>
#include<Windows.h>
#include<spdlog/spdlog.h>
#include<iostream>

export module Helium.MinecraftServer:Class;

import Helium.Events;
import Helium.Logger;
import Helium.UUIDManager;
import Helium.Parser;

import <string>;
import <list>;
import <any>;
import <vector>;

using namespace std;
using namespace boost;
using namespace boost::uuids;

export {
	namespace Helium {
		enum HeliumServerStat {
			RUNNING,
			TERMINATED,
			PAUSED,
			UNDEF
		};

		enum HeliumServerType {
			VANILLA,
			FORGE,
			BUKKIT,
			BUKKIT14,
			BUNGEECORD,
			WATERFALL,
			CAT,
			BETA18
		};

		struct RedirectInformation
		{
			HANDLE hStdInRead = NULL;   //子进程用的stdin的读入端
			HANDLE hStdInWrite = NULL;  //主程序用的stdin的读入端

			HANDLE hStdOutRead = NULL;  //主程序用的stdout的读入端
			HANDLE hStdOutWrite = NULL; //子进程用的stdout的写入端

			HANDLE hStdErrWrite = NULL; //子进程用的stderr的写入端

			RedirectInformation& operator=(RedirectInformation& a) {
				if (this != &a)
				{
					this->hStdErrWrite = a.hStdErrWrite;
					this->hStdInRead = a.hStdInRead;
					this->hStdInWrite = a.hStdInWrite;
					this->hStdOutRead = a.hStdOutRead;
					this->hStdOutWrite = a.hStdOutWrite;
					return *this;
				}
				else
				{
					throw "Error";
				}
			}
		};

		struct RCONInfo {
			bool isenabled;
			int port;
			string pwd;
		};

		class HeliumMinecraftServer {
			friend int ProcessServerOutput(HeliumMinecraftServer* ptr, string servername, HANDLE stdread, HANDLE hproc);
		public:
			HeliumMinecraftServer();
			virtual ~HeliumMinecraftServer();

			string GetServerName();
			string SetServerName(string name);

			string GetServerDirectory();
			string SetServerDirectory(string dir);

			string GetServerStartCommand();
			string SetServerStartCommand(string cmd);

			bool IsAutoStart();
			bool EnableAutoStart();
			bool DisableAutoStart();

			bool IsOutputVisible();
			bool EnableOutputVisibility();
			bool DisableOutputVisibility();

			HeliumServerType GetServerType();
			HeliumServerType SetServerType(HeliumServerType type);

			HeliumServerStat GetServerStat();

			uuid GetServerUUID();

			DWORD GetServerPID();

			HANDLE GetServerHandle();

			HANDLE GetServerThreadHandle();

			DWORD GetServerRetValue();

			RedirectInformation GetServerRedir();
			RedirectInformation SetServerRedir(RedirectInformation* redir);

			bool IsRCONEnabled();
			bool EnableRCON();
			bool DisableRCON();

			int GetRCONPort();
			int SetRCONPort(int port);

			string GetRCONPassword();
			string SetRCONPassword(string pwd);

			bool IsValid();

			int StartServer();
			int StopServer();
			int PauseServer();
			int ResumeServer();

			int GenerateParser();

			int SendToServer(const string& text);
			int Say(const string& text);
			int Boardcast(const string& text);
			int Tellraw(const string& text);
			int Execute(const string& text);
			int Save();

			void operator=(HeliumMinecraftServer server);
		private:
			string name;
			string dir;
			string startcommand;

			HeliumServerType type;
			HeliumServerStat stat;

			bool visi;
			bool autostart;

			HANDLE proc;
			HANDLE thread;
			DWORD  pid;
			DWORD  retv;

			RedirectInformation redir;

			uuid serveruuid;

			RCONInfo rcon;

			std::shared_ptr<VanillaParser> parser_ptr;
		};

		CRITICAL_SECTION cs;
		vector<thread> outputthreads;
		bool isinit = false;

		int ProcessServerOutput(HeliumMinecraftServer* ptr, string servername, HANDLE stdread, HANDLE hproc);
		int InitServerEnv();

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
				CREATE_SUSPENDED | CREATE_NO_WINDOW,
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

				list<any> param;
				any temp_any = this->name;
				param.push_back(temp_any);
				helium_event_manager.DispatchEvent(HeliumEventList::SERVER_START, param);
			}

			return 0;
		}
		int HeliumMinecraftServer::StopServer() {
			int ret = 0;

			TerminateProcess(this->proc, 0);
			list<any> param;
			any temp_any = this->name;
			param.push_back(temp_any);
			helium_event_manager.DispatchEvent(HeliumEventList::SERVER_STOP, param);

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
			this->serveruuid = RequestUUID(UUIDInfoType::SERVER, (void*)this);
		}
		HeliumMinecraftServer::~HeliumMinecraftServer() {
			if (this->stat != HeliumServerStat::TERMINATED) this->StopServer();
		}

		int HeliumMinecraftServer::GenerateParser() {
			try {
				this->parser_ptr = make_shared<VanillaParser>(this->name);
			}
			catch (std::exception& e) {
				log << HLL::LL_ERR << "Failed to generate parser for server "
					<< this->name << hendl;
				log << HLL::LL_ERR << e.what() << hendl;
			}
			return 0;
		}

		int HeliumMinecraftServer::SendToServer(const string& text) {
			return 0;
		}
		int HeliumMinecraftServer::Say(const string& text) {
			return 0;
		}
		int HeliumMinecraftServer::Boardcast(const string& text) {
			return 0;
		}
		int HeliumMinecraftServer::Tellraw(const string& text) {
			return 0;
		}
		int HeliumMinecraftServer::Execute(const string& text) {
			return 0;
		}
		int HeliumMinecraftServer::Save() {
			return 0;
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
					list<any> param;
					any temp_any;
					temp_any = ptr->name;
					param.push_back(temp_any);
					temp_any = s;
					param.push_back(temp_any);
					helium_event_manager.DispatchEvent(HeliumEventList::SERVER_OUTPUT, param);
					EnterCriticalSection(&cs);
					cout << servername << " > " << s << endl;
					LeaveCriticalSection(&cs);
					ptr->parser_ptr->Parse(s);
				}
			}

			return 0;
		}
	}
}