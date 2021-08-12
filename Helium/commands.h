#pragma once

#ifndef _H_COMMANDS
#define _H_COMMANDS

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include<vector>
#include<string>
#include<thread>	
#include<Windows.h>
#include<atomic>
#include<guiddef.h>

using namespace std;

#define CMD_TYPE_EMPTY		0
#define CMD_TYPE_HELIUM		1
#define CMD_TYPE_MINECRAFT	2

#define QUEUE_STAT_EMPTY		0
#define QUEUE_STAT_LOADING		1
#define QUEUE_STAT_READY		2
#define QUEUE_STAT_EXECUTING	3
#define QUEUE_STAT_PAUSED		4
#define QUEUE_STAT_TERMINATED	5
#define QUEUE_STAT_DUMPING		6

class HeliumCommand {
	friend class HeliumCommandQueue;
protected:
	string command;
	GUID commandguid;

	int executecounter;
	int commandtype;
public:
	_stdcall HeliumCommand();
	_stdcall HeliumCommand(const HeliumCommand* cmd);
	_stdcall HeliumCommand(string cmd);

	int _stdcall AutoSetType();
	
	string _stdcall GetCommand();
	string _stdcall SetCommand(string cmd);

	int _stdcall GetCommandGUID(LPGUID guid);

	int _stdcall GetExecCounter();
protected:
	int _stdcall IncExecCounter();
public:

	int _stdcall GetCommandType();
};

class HeliumCommandQueue {
	friend int _stdcall InitShellQueue();
protected:
	vector<HeliumCommand> commands;
	thread execthread;
	string queuename;

	int queuestatus;
	int ip;
	GUID queueguid;
	GUID server;
	
	bool restart;
	bool unstoppable;
	bool immutable;
	bool isshell;

	int _stdcall ExecThreadFunc();
public:
	_stdcall HeliumCommandQueue();
	_stdcall HeliumCommandQueue(const HeliumCommandQueue& queue);
	_stdcall HeliumCommandQueue(const vector<HeliumCommand>* cmds);
	_stdcall HeliumCommandQueue(string name);

	int _stdcall StartExecute();

	string _stdcall GetQueueName();
	int _stdcall SetQueueName(string name);

	int _stdcall GetGUID(LPGUID guid);

	int _stdcall GetQueueStatus();

	bool GetRestart();
	bool SetRestart(bool r);

	bool GetUnstoppable();
	bool SetUnstoppable(bool u);

	bool GetImmutable();
	bool SetImmutable(bool i);

	int _stdcall QueryCommand(string cmd);
	int _stdcall QueryCommand(LPCGUID guid);

	int _stdcall DeleteCommand(string cmd);
	int _stdcall DeleteCommand(LPCGUID guid);
	int _stdcall DeleteCommand(int index);

	int _stdcall InsertCommand(const HeliumCommand* cmd);
	int _stdcall InsertCommand(const HeliumCommand* cmd, int index);
	int _stdcall InsertCommand(const HeliumCommand* cmd, LPCGUID guid);
};

int _stdcall InitShellQueue();
int _stdcall NewShellCommand(string cmd);

extern vector<HeliumCommandQueue> cmdqueuelist;

#endif // !_H_COMMANDS