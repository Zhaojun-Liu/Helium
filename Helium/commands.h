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

using namespace std;

#define CMD_TYPE_EMPTY
#define CMD_TYPE_HELIUM
#define CMD_TYPE_MINECRAFT

#define QUEUE_STAT_EMPTY
#define QUEUE_STAT_LOADING
#define QUEUE_STAT_READY
#define QUEUE_STAT_EXECUTING
#define QUEUE_STAT_PAUSED
#define QUEUE_STAT_TERMINATED
#define QUEUE_STAT_DUMPING

class HeliumCommand {
protected:
	string command;

	int executecounter;
	int commandtype;

public:
	_stdcall HeliumCommand();
	_stdcall HeliumCommand(const HeliumCommand* cmd);
	_stdcall HeliumCommand(string cmd);

	int _stdcall Execute();
	int _stdcall AutoSetType();
	
	string _stdcall GetCommand();
	string _stdcall SetCommand(string cmd);

	int _stdcall GetExecCounter();
protected:
	int _stdcall IncExecCounter();
public:

	int _stdcall GetCommandType();
};

class HeliumCommandQueue {
protected:
	vector<HeliumCommand> commands;
	thread execthread;

	int queuestatus;
	int queueid;
	
	bool restart;
	bool unstoppable;
	bool immutable;

	int _stdcall ExecThreadFunc();
public:
	_stdcall HeliumCommandQueue();
	_stdcall HeliumCommandQueue(const HeliumCommandQueue* queue);
	_stdcall HeliumCommandQueue(const vector<HeliumCommand>* cmds);

	int _stdcall NewQID();
	int _stdcall GetQID();

	int _stdcall GetQueueStatus();

	bool GetRestart();
	bool SetRestart(bool r);

	bool GetUnstoppable();
	bool SetUnstoppable(bool u);

	bool GetImmutable();
	bool SetImmutable(bool i);
};

#endif // !_H_COMMANDS