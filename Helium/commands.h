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

#define MAX_EXECUTORS 2048
#define MAX_CMD_QUEUE 2048

#define EMPTY_CMD "EMPTY_CMD"

#define CMD_TYPE_BUILTINCMD 0
#define CMD_TYPE_MCCMD 1
#define CMD_TYPE_PROCESSCTRL 2
#define CMD_TYPE_DONOTHING 3

#define QUEUE_STATUS_RUNNING 0
#define QUEUE_STATUS_SLEEPING 1
#define QUEUE_STATUS_LOADING 2
#define QUEUE_STATUS_TERMINATED 3
#define QUEUE_STATUS_SUSPENDED 4

#define QUEUE_TYPE_NORMAL 0
#define QUEUE_TYPE_SHELL 1

class CommandInstance {
public:
	CommandInstance();
	CommandInstance(string command, int type);

	string GetCmd();
	string SetCmd(string command);

	int GetCmdType();
	int SetCmdType(int type);

	int IncExecuteCounter();
	int GetExecuteCounter();
	int ClearExecuteCounter();
private:
	string command;

	int cmdtype;
	int executecounter;
};

class CommandQueue {
	friend int ExecutorThread(int qid);
public:
	CommandQueue();
	~CommandQueue();

	int Queue_Suspend();
	int Queue_Resume();
	int Queue_Sleep(int slptime);

	int Reinitialize();

	int LoadCommandQueueFromFile(string filename);
	int DumpCommandQueueToFile();

	int InsertCommand(CommandInstance command);
	int InsertCommand(CommandInstance command, int index);

	int DeleteCommand(string command);
	int DeleteCommand(int index);

	int SetStatus(int stat);
	int GetStatus();

	int SetType(int type);
	int GetType();

	int SetTS(int ts);
	int GetTS();

	int SetCurrIndex(int index);
	int GetCurrIndex();

	int SetExecutor(int execindex);
	int GetExecutor();

	int SetQID(int qid);
	int GetQID();

	bool IsUnstoppable();
	bool IsImmutable();
	bool IsCanBeRestarted();
	bool IsControlledByExecutor();

	bool SetUnstoppable(bool unstoppable);
	bool SetImmutable(bool immutable);
	bool SetCanBeRestarted(bool restart);
	bool SetControlledByExecutor(bool cbe);

	bool operator== (CommandQueue queue);
private:
	vector<CommandInstance> _cmdqueue;
	thread* _executor;

	string queuename;

	int queuestatus;
	int queuetype;
	int timeslice;
	int currentindex;
	int executorindex;
	int qid;

	bool unstoppable;
	bool immutable;
	bool restart;
	bool controlbyexecutor;
};

/*
草
我又不是在写系统
何必呢
一比一模型yyds
*/

int ExecutorThread(int qid);
int DeleteQueue(CommandQueue queue);
int NewCommandFromConsole(LPCSTR cmd);
int CreateQueueForShell();
int NewQID();
vector<CommandQueue>::iterator SearchQueueByQID(int qid);

bool isCommand(LPCSTR cmd);

#endif // !_H_COMMANDS