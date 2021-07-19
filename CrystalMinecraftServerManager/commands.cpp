#include"commands.h"

int empty_queue_counter = 0;
thread executors[MAX_EXECUTORS];
vector<QueueExecutor> Executors;
vector<CommandQueue> CommandQueues;
vector<CommandQueue> RunnableCommandQueues;

#pragma region CommandInstanceFunc

CommandInstance::CommandInstance()
{
	this->command = EMPTY_CMD;
	this->cmdtype = CMD_TYPE_DONOTHING;
}

CommandInstance::CommandInstance(string command, int type)
{
	this->command = command;
	if (CMD_TYPE_BUILTINCMD <= type || type <= CMD_TYPE_DONOTHING)
		this->cmdtype = type;
	else
		;
}

string CommandInstance::GetCmd()
{
	return command;
}

string CommandInstance::SetCmd(string command)
{
	this->command = command;
	return command;
}

int CommandInstance::GetCmdType()
{
	return this->cmdtype;
}

int CommandInstance::SetCmdType(int type)
{
	this->cmdtype = type;
	return type;
}

int CommandInstance::IncExecuteCounter()
{
	this->executecounter++;
	return this->executecounter;
}

int CommandInstance::GetExecuteCounter()
{
	return this->executecounter;
}

int CommandInstance::ClearExecuteCounter()
{
	this->executecounter = 0;
	return 0;
}

#pragma endregion

#pragma region CommandQueue

CommandQueue::CommandQueue()
{
	CommandInstance cmdins;
	this->InsertCommand(cmdins);
	this->queuename = "EMPTY_QUEUE_" + empty_queue_counter;
	this->qid = NewQID();
	empty_queue_counter++;
	CommandQueues.push_back(*this);
}

int CommandQueue::Queue_Suspend()
{
	this->queuestatus = QUEUE_STATUS_SUSPENDED;
	DeleteRunnableQueue(*this);
	return 0;
}

int CommandQueue::Queue_Resume()
{
	this->queuestatus = QUEUE_STATUS_READY;
	RunnableCommandQueues.push_back(*this);
	return 0;
}

int CommandQueue::Queue_Sleep(int slptime)
{
	this->queuestatus = QUEUE_STATUS_SLEEPING;
	DeleteRunnableQueue(*this);
	return 0;
}

int CommandQueue::LoadCommandQueueFromFile(string filename)
{
	HANDLE queuefile;
	int filesize;
	DWORD readbytes;

	queuefile = CreateFile(
		filename.c_str(),
		GENERIC_ALL,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_SEQUENTIAL_SCAN,
		NULL
	);

	if ( queuefile == NULL ) {
		return GetLastError();
	}

	filesize = GetFileSize(queuefile, NULL);
	char* buf = new char[filesize];
	memset(buf, '\0', sizeof(buf));

	if (!ReadFile(
		queuefile,
		buf,
		sizeof(buf),
		&readbytes,
		NULL
	)) {

	}



	delete[] buf;
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

bool CommandQueue::operator==(CommandQueue queue)
{
	if (this->queuename == queue.queuename)
		return true;
	else
		return false;
}

#pragma endregion

#pragma region Executor

QueueExecutor::QueueExecutor()
{
	Executors.push_back(*this);
}

int QueueExecutor::StartExecutorThread()
{
	thread execthread((this->ExecutorThread));
	executors[this->index] =  ;
	return 0;
}

int QueueExecutor::ExecutorThread()
{
	return 0;
}

#pragma endregion

int StartQueueExecuting(int exec)
{
	for (int i = 0; i < exec; i++) {
		QueueExecutor newexec;
		newexec.index = i;
	}
	return 0;
}

int DeleteQueue(CommandQueue queue)
{
	vector<CommandQueue>::iterator it;
	for (it = CommandQueues.begin(); it <= CommandQueues.end(); it++) {
		if (*it == queue) {
			CommandQueues.erase(it);
		}
	}
	return 0;
}

int DeleteRunnableQueue(CommandQueue queue)
{
	vector<CommandQueue>::iterator it;
	for (it = RunnableCommandQueues.begin(); it <= RunnableCommandQueues.end(); it++) {
		if (*it == queue) {
			RunnableCommandQueues.erase(it);
		}
	}
	return 0;
}

int NewCommandFromConsole(LPCSTR cmd)
{
	return 0;
}

int CreateQueueForShell()
{
	CommandQueue shellqueue;
	return 0;
}

int NewQID()
{
	int newqid = 0;
	vector<CommandQueue>::iterator it;
	for (it = CommandQueues.begin(); it <= CommandQueues.end(); it++) {
		if (it->GetQID() == newqid) {
			newqid++;
			it = CommandQueues.begin();
		}
	}
	return newqid;
}

bool isCommand(LPCSTR cmd)
{
	return false;
}
