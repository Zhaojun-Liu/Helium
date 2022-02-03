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

#define WIN32_LEAN_AND_MEAN

#include<thread>

#include<Windows.h>
#include<spdlog/spdlog.h>
#include<boost/uuid/uuid.hpp>

export module Helium.MinecraftServer:Class;

import Helium.Logger;
import <string>;

using namespace std;
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
					exception e;
					throw e;
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

		protected:
			string name;
			string dir;
			string startcommand;

			int type;
			int stat;

			bool visi;
			bool autostart;

			HANDLE proc;
			HANDLE thread;
			DWORD  pid;
			DWORD  retv;

			RedirectInformation redir;

			uuid serveruuid;

			RCONInfo rcon;
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

			int GetServerType();
			int SetServerType(int type);

			int GetServerStat();

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

			uuid GenServerUUID();

			int StartServer();
			int StopServer();
			int PauseServer();
			int ResumeServer();

			void operator=(HeliumMinecraftServer server);			
		};
		HeliumLogger lg("HeliumServer");
		int ProcessServerOutput(HeliumMinecraftServer* ptr, string servername, HANDLE stdread, HANDLE hproc);
	}
}

namespace Helium {
	vector<thread> outputthread;
}