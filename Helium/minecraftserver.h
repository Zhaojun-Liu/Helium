#pragma once

#ifndef _H_MINECRAFTSERVER
#define _H_MINECRAFTSERVER

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include<string>
#include<thread>
#include<iostream>

#include<Windows.h>

#include"utils.h"

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

struct ServerLineOutput {
	string servername;
	string output;
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

class MinecraftServerInstance {
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
	HANDLE serverproc;

	RedirectInformation redir;
public:
	MinecraftServerInstance();
	MinecraftServerInstance(MinecraftServerInstance* ins);
	MinecraftServerInstance(MinecraftServerInstance& ins);

	~MinecraftServerInstance();

	int    ProcessServerOutput(string servername, bool visi);

	string SetServerName(string servername);
	string GetServerName();

	string SetJVMDirectory(string dir);
	string GetJVMDirectory();

	string SetServerFileName(string name);
	string GetServerFileName();

	string SetJVMOption(string option);
	string GetJVMOption();

	string SetServerDirectory(string dir);
	string GetServerDirectory();

	string SetMaxmem(string mem);
	string SetMinmem(string mem);
	string GetMaxmem();
	string GetMinmem();

	int    SetStartupType(int type);
	int    GetStartupType();

	int    SetServerType(int type);
	int    GetServerType();

	int    SetServerStatus(int stat);
	int    GetServerStatus();

	bool   SetVisibility(bool vis);
	bool   GetVisibility();

	bool   SetAutoStart(bool start);
	bool   GetAutoStart();

	int    StartServer();
	int    StopServer();
	int    RestartServer();

	void   Print();
};

#endif // !_H_MINECRAFTSERVER
