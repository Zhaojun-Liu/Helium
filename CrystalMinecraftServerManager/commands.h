#pragma once

#ifndef _H_COMMANDS
#define _H_COMMANDS

#include<vector>
#include<string>
#include<thread>	
#include<Windows.h>

using namespace std;

#define MAX_EXECUTORS 64

#define EMPTY_CMD "EMPTY_CMD"

#define CMD_TYPE_BUILTINCMD 0
#define CMD_TYPE_MCCMD 1
#define CMD_TYPE_PROCESSCTRL 2
#define CMD_TYPE_DONOTHING 3

#define QUEUE_STATUS_RUNNING 0
#define QUEUE_STATUS_SLEEPING 1
#define QUEUE_STATUS_READY 2
#define QUEUE_STATUS_LOADING 3
#define QUEUE_STATUS_TERMINATED 4
#define QUEUE_STATUS_SUSPENDED 5

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
public:
	CommandQueue();

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
�����㷨����:
	�ع���ת�㷨(Regressive Round-Robin)�ı���:
		ִ�п�ʼ,����һ����ʼָ����a,ÿ��ִ�еĶ�����ִ����a��ָ����ó�ִ�����߳�,ͬʱͨ������ȫ������ÿ��ִ��a��ָ���ʱ��,
		����ִ��ʱ���ָ��ƽ��.
		����t1Ϊ��n��ִ������ʱ��,t2Ϊ��һ��ִ��ʱ���Ԥ��ֵ,��Ϊ��ȥִ��ʱ���ָ��ƽ��,����a(0<=a<=1),��:
			t2 = a * t1 + ( 1 - a ) * ��
		a��Ϊ��ǰִ��ʱ���Ȩ��,��(1-a)��Ϊ��ʷִ��ʱ���Ȩ��,һ��ѡ��Ϊ1/2,�������ļ��и���ѡ��.
		ͬʱִ�����̱߳Ƚϵ�ǰ��������ִ��ʱ��,������t1,���ʵ�������a,����t1,���ʵ�������a.
*/

int ExecutorThread();
int StartQueueExecuting(int exec);
int DeleteQueue(CommandQueue queue);
int DeleteRunnableQueue(CommandQueue queue);
int NewCommandFromConsole(LPCSTR cmd);
int CreateQueueForShell();
int NewQID();

bool isCommand(LPCSTR cmd);

#endif // !_H_COMMANDS