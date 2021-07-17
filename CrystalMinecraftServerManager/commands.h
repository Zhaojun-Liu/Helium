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
调度算法概述:
	回归轮转算法(Regressive Round-Robin)的变种:
		执行开始,给定一个初始指令数a,每个执行的队列在执行完a条指令后让出执行者线程,同时通过测量全部队列每次执行a条指令的时间,
		计算执行时间的指数平均.
		即设t1为第n个执行所需时间,t2为下一次执行时间的预测值,τ为过去执行时间的指数平均,对于a(0<=a<=1),有:
			t2 = a * t1 + ( 1 - a ) * τ
		a即为当前执行时间的权重,而(1-a)即为历史执行时间的权重,一般选择为1/2,在配置文件中给出选项.
		同时执行者线程比较当前队列所需执行时间,若超过t1,则适当减少其a,少于t1,则适当增加其a.
*/
class QueueExecutor {
public:
	int StartExecutorThread();
private:
	int ExecutorThread();
};

vector<QueueExecutor> Executors;

int StartQueueExecuting();
