#pragma once

#ifndef _H_MINECRAFTSERVER
#define _H_MINECRAFTSERVER

#include<string>
#include<thread>
#include<iostream>

#include<Windows.h>

using namespace std;

struct RedirectInformation
{

	HANDLE hStdInRead = NULL;   //�ӽ����õ�stdin�Ķ����  
	HANDLE hStdInWrite = NULL;  //�������õ�stdin�Ķ���� 

	HANDLE hStdOutRead = NULL;  //�������õ�stdout�Ķ����  
	HANDLE hStdOutWrite = NULL; //�ӽ����õ�stdout��д���  

	HANDLE hStdErrWrite = NULL; //�ӽ����õ�stderr��д���  

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
	string serverjarname;
	string jvmoption;
	string serverdirectory;
	string minmem;
	string maxmem;

	int    serverstartuptype;
	int	   servertype;
	int	   serverstatus;

	thread stdoutthread;

	RedirectInformation redir;
public:
	MinecraftServerInstance();
	MinecraftServerInstance(const MinecraftServerInstance const* ins);

	~MinecraftServerInstance();

	int    ProcessServerOutput();

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

	string    SetMaxmem(string mem);
	string    SetMinmem(string mem);
	string    GetMaxmem();
	string    GetMinmem();

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
