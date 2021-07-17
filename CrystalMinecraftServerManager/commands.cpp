#include"commands.h"

#pragma region CommandInstanceFunc

CommandInstance::CommandInstance()
{
}

CommandInstance::CommandInstance(string command, int type)
{
}

string CommandInstance::GetCmd()
{
	return string();
}

int CommandInstance::SetCmd(string command)
{
	return 0;
}

int CommandInstance::GetCmdType()
{
	return 0;
}

int CommandInstance::SetCmdType(int type)
{
	return 0;
}

int CommandInstance::IncExecuteCounter()
{
	return 0;
}

int CommandInstance::GetExecuteCounter()
{
	return 0;
}

int CommandInstance::ClearExecuteCounter()
{
	return 0;
}

#pragma endregion

#pragma region CommandQueue

CommandQueue::CommandQueue()
{
}

CommandQueue::CommandQueue(CommandQueue queue)
{
}

int CommandQueue::Queue_Suspend()
{
	return 0;
}

int CommandQueue::Queue_Resume()
{
	return 0;
}

int CommandQueue::Queue_Sleep(int slptime)
{
	return 0;
}

int CommandQueue::LoadCommandQueueFromFile(string filename)
{
	return 0;
}

int CommandQueue::DumpCommandQueueToFile()
{
	return 0;
}

int CommandQueue::InsertCommand(CommandInstance command)
{
	return 0;
}

int CommandQueue::InsertCommand(CommandInstance command, int index)
{
	return 0;
}

int CommandQueue::DeleteCommand(string command)
{
	return 0;
}

int CommandQueue::DeleteCommand(int index)
{
	return 0;
}

#pragma endregion

#pragma region Executor

int QueueExecutor::StartExecutorThread()
{
	return 0;
}

int QueueExecutor::ExecutorThread()
{
	return 0;
}

int StartQueueExecuting()
{
	return 0;
}

#pragma endregion
