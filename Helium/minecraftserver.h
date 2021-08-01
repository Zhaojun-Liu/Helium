#pragma once

#include<string>

using namespace std;

#ifndef _H_MINECRAFTSERVER
#define _H_MINECRAFTSERVER

class MinecraftServerInstance {
protected:
	string servername;
	string jvmdirectory;
	string serverjarname;
	string jvmoption;
	string serverdirectory;

	int    serverstartuptype;
	int	   servertype;
	int	   serverstatus;
public:
	MinecraftServerInstance();
	MinecraftServerInstance(const MinecraftServerInstance const* ins);

	~MinecraftServerInstance();

	string SetServerName(string servername);
	string GetServerName();

	string SetJVMDirectory(string dir);
	string GetJVMDirectory();

	string SetServerJarName(string name);
	string GetServerJarName();

	string SetJVMOption(string option);
	string GetJVMOption();

	string SetServerDirectory(string dir);
	string GetServerDirectory();

	int    SetStartupType(int type);
	int    GetStartupType();

	int    SetServerType(int type);
	int    GetServerType();

	int    SetServerStatus(int stat);
	int    GetServerStatus();

	int    StartServer();
	int    StopServer();
	int    RestartServer();
};

#endif // !_H_MINECRAFTSERVER
