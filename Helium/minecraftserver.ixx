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

#include<string>
#include<thread>
#include<iostream>

#include<Windows.h>
#include<guiddef.h>
#include<spdlog/spdlog.h>
#include<boost/uuid/uuid.hpp>

#include"tinyxml2/tinyxml2.h"

export module Helium.MinecraftServer;

#define SERVER_STATUS_RUNNING		0
#define SERVER_STATUS_TERMINATED	1
#define SERVER_STATUS_PAUSED		2
#define SERVER_STATUS_UNDEF			3

#define SERVER_TYPE_VANILLA		0
#define SERVER_TYPE_FORGE		1
#define SERVER_TYPE_BUKKIT		2
#define SERVER_TYPE_BUKKIT14	3
#define SERVER_TYPE_BUNGEECORD	4
#define SERVER_TYPE_WATERFALL	5
#define SERVER_TYPE_CAT			6
#define SERVER_TYPE_BETA18		7

#define BUFSIZE 8192

using namespace std;
using namespace boost::uuids;
using namespace std;

export{
	namespace Helium {
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
			DWORD  pid;
			DWORD  retv;

			RedirectInformation redir;

			uuid serveruuid;
		public:
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
			void SetServerHandle(HANDLE han);

			DWORD GetServerRetValue();

			RedirectInformation GetServerRedir();
			RedirectInformation SetServerRedir(RedirectInformation* redir);

			uuid GenServerUUID();
		};

		int ProcessServerOutput(HeliumMinecraftServer* ptr, string servername, HANDLE stdread, HANDLE hproc);

		extern vector<HeliumMinecraftServer> heliumservers{};
	}
}