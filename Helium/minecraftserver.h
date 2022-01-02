#pragma once

#ifndef _H_MINECRAFTSERVER
#define _H_MINECRAFTSERVER

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include<string>
#include<thread>
#include<iostream>

#include<Windows.h>
#include<guiddef.h>

#include"utils.h"
#include"commands.h"
#include<spdlog/spdlog.h>
#include"tinyxml2.h"
#include"logger.h"
namespace Helium {

	using namespace std;

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

#define STARTUP_TYPE_JAR 0
#define STARTUP_TYPE_BAT 1

#define BUFSIZE 8192

#define SERVER_FILENAME "server.xml"

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

	class MinecraftServerInstance {

		friend int _stdcall ProcessServerOutput(MinecraftServerInstance* ptr, string servername, HANDLE stdread, HANDLE hproc);
	protected:
		string servername;
		string jvmdirectory;
		string serverfilename;
		string jvmoption;
		string serverdirectory;
		string minmem;
		string maxmem;

		int    serverstartuptype;
		int	   servertype;
		int	   serverstatus;

		bool   outputvisibility;
		bool   autostart;

		thread stdoutthread;
		HANDLE hProc;
		DWORD  dwPid;
		DWORD  dwReturnValue;

		GUID   serverguid;

		RedirectInformation redir;
	public:
		_stdcall MinecraftServerInstance();
		_stdcall MinecraftServerInstance(const MinecraftServerInstance* ins);
		_stdcall MinecraftServerInstance(const MinecraftServerInstance& ins);

		void _stdcall operator=(const MinecraftServerInstance&& ins);

		_stdcall ~MinecraftServerInstance();

		string _stdcall SetServerName(string servername);
		string _stdcall GetServerName();

		string _stdcall SetJVMDirectory(string dir);
		string _stdcall GetJVMDirectory();

		string _stdcall SetServerFileName(string name);
		string _stdcall GetServerFileName();

		string _stdcall SetJVMOption(string option);
		string _stdcall GetJVMOption();

		string _stdcall SetServerDirectory(string dir);
		string _stdcall GetServerDirectory();

		string _stdcall SetMaxmem(string mem);
		string _stdcall SetMinmem(string mem);
		string _stdcall GetMaxmem();
		string _stdcall GetMinmem();

		int    _stdcall SetStartupType(int type);
		int    _stdcall GetStartupType();

		int    _stdcall SetServerType(int type);
		int    _stdcall GetServerType();

		int    _stdcall SetServerStatus(int stat);
		int    _stdcall GetServerStatus();

		bool   _stdcall SetVisibility(bool vis);
		bool   _stdcall GetVisibility();

		bool   _stdcall SetAutoStart(bool start);
		bool   _stdcall GetAutoStart();

		int    _stdcall SetServerReturnValue(DWORD wdnmd);
		int    _stdcall GetServerReturnValue(LPDWORD wdnmd);

		int    _stdcall SetServerGUID(LPCGUID guid);
		int    _stdcall GetServerGUID(LPGUID guid);
		DWORD  _stdcall GerServerPid();
		bool   _stdcall GetOutputVis();
		HANDLE _stdcall GetThreadHandle();
		PHANDLE WINAPI GetThreadPHandle() { return &(this->hProc); }
		int    _stdcall StartServer();
		int    _stdcall StopServer();
		int    _stdcall RestartServer();
		void   _stdcall Print();
		RedirectInformation _stdcall GetRDInfo() { return this->redir; }
	};

	int _stdcall ProcessServerOutput(MinecraftServerInstance* ptr, string servername, HANDLE stdread, HANDLE hproc);

	int _stdcall ReadServerFile();
	int _stdcall SaveServerFile();
	int _stdcall CreateServerFile();

	extern vector<MinecraftServerInstance> serverlist;
}
#endif // !_H_MINECRAFTSERVER
