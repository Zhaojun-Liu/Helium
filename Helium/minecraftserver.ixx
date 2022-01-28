module;

#include<string>
#include<thread>
#include<iostream>

#include<Windows.h>
#include<guiddef.h>
#include<spdlog/spdlog.h>
#include<boost/uuid/uuid.hpp>

#include"utils.h"
#include"commands.h"
#include"tinyxml2/tinyxml2.h"
#include"logger.h"

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

			HANDLE hProc;
			DWORD  dwPid;
			DWORD  dwReturnValue;

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
			HANDLE SetServerHandle();

			DWORD GetServerRetValue();

			RedirectInformation GetServerRedir();
			RedirectInformation SetServerRedir(RedirectInformation* redir);

			uuid GenServerUUID();
		};

		int ProcessServerOutput(HeliumMinecraftServer* ptr, string servername, HANDLE stdread, HANDLE hproc);
	}
}