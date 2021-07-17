#pragma once

#include<vector>
#include<string>
#include<thread>	
#include<Windows.h>

using namespace std;

#define CMD_TYPE_BUILTINCMD 0
#define CMD_TYPE_MCCMD 1
#define CMD_TYPE_PROCESSCTRL 2

#define QUEUE_STATUS_RUNNING 0
#define QUEUE_STATUS_SLEEPING 1
#define QUEUE_STATUS_READY 2
#define QUEUE_STATUS_LOADING 3
#define QUEUE_STATUS_TERMINATED 4
#define QUEUE_STATUS_SUSPENDED 5

class CommandInstance {
public:
	CommandInstance();
	CommandInstance(string command, int type);

	string GetCmd();
	int SetCmd(string command);

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

	int LoadCommandQueueFromFile(string filename);
	int DumpCommandQueueToFile();

	int InsertCommand(CommandInstance command);
	int InsertCommand(CommandInstance command, int index);

	int DeleteCommand(string command);
	int DeleteCommand(int index);
private:
	vector<CommandInstance> Commands;

	string queuename;

	int queuestatus;
	int queuetype;
	int timeslice;
	int currentindex;
	int executorindex;

	bool unstoppable;
	bool immutable;
	bool restart;
	bool controlbyexecutor;
};

vector<CommandQueue> CommandQueues;
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
class QueueExecutor {
public:
	int StartExecutorThread();
private:
	int ExecutorThread();
};

vector<QueueExecutor> Executors;

int StartQueueExecuting();
