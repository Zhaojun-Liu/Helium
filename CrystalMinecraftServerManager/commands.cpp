#include"commands.h"

int empty_queue_counter = 0;

vector<thread> Executors;
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
		this->cmdtype = CMD_TYPE_DONOTHING;
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
	this->queuename = "EMPTY_QUEUE_" + empty_queue_counter;
	this->qid = NewQID();
	this->controlbyexecutor = true;
	this->currentindex = 0;
	this->immutable = false;
	this->queuestatus = QUEUE_STATUS_LOADING;
	this->queuetype = QUEUE_TYPE_NORMAL;
	this->unstoppable = false;
	this->restart = false;
	empty_queue_counter++;
	CommandQueues.push_back(*this);
}

int CommandQueue::Queue_Suspend()
{
	if (this->unstoppable == true) {
		return -1;
	}
	this->queuestatus = QUEUE_STATUS_SUSPENDED;
	DeleteRunnableQueue(*this);
	return 0;
}

int CommandQueue::Queue_Resume()
{
	if (this->unstoppable == false) {
		this->queuestatus = QUEUE_STATUS_READY;
		RunnableCommandQueues.push_back(*this);
		return 0;
	}
	return -1;
}

int CommandQueue::Queue_Sleep(int slptime)
{
	this->queuestatus = QUEUE_STATUS_SLEEPING;
	DeleteRunnableQueue(*this);
	return 0;
}

int CommandQueue::Reinitialize()
{
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
	this->_cmdqueue.push_back(command);
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

#pragma region CmdQueueAttrs
int CommandQueue::SetStatus(int stat) {
	this->queuestatus = stat;
	return stat;
}
int CommandQueue::GetStatus() {
	return this->queuestatus;
}

int CommandQueue::SetType(int type) {
	this->queuetype = type;
	return type;
}
int CommandQueue::GetType() {
	return this->queuetype;
}

int CommandQueue::SetTS(int ts) {
	this->timeslice = ts;
	return ts;
}
int CommandQueue::GetTS() {
	return this->timeslice;
}

int CommandQueue::SetCurrIndex(int index) {
	this->currentindex = index;
	return index;
}
int CommandQueue::GetCurrIndex() {
	return this->currentindex;
}

int CommandQueue::SetExecutor(int execindex) {
	this->executorindex = execindex;
	return execindex;
}
int CommandQueue::GetExecutor() {
	return this->executorindex;
}

int CommandQueue::SetQID(int qid) {
	this->qid = qid;
	return qid;
}
int CommandQueue::GetQID() {
	return this->qid;
}

bool CommandQueue::IsUnstoppable() {
	return this->unstoppable;
}
bool CommandQueue::IsImmutable() {
	return this->immutable;
}
bool CommandQueue::IsCanBeRestarted() {
	return this->restart;
}
bool CommandQueue::IsControlledByExecutor() {
	return this->controlbyexecutor;
}

bool CommandQueue::SetUnstoppable(bool unstoppable) {
	this->unstoppable = unstoppable;
	return unstoppable;
}
bool CommandQueue::SetImmutable(bool immutable) {
	this->immutable = immutable;
	return immutable;
}
bool CommandQueue::SetCanBeRestarted(bool restart) {
	this->restart = restart;
	return restart;
}
bool CommandQueue::SetControlledByExecutor(bool cbe) {
	this->controlbyexecutor = cbe;
	return cbe;
}

#pragma endregion

#pragma region Executor

#pragma endregion

int ExecutorThread()
{
	return 0;
}

int StartQueueExecuting(int exec)
{
	for (int i = 0; i < exec; i++) {
		Executors.push_back(*(new thread(ExecutorThread)));
		Executors.back().detach();
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
	shellqueue.SetCanBeRestarted(false);
	shellqueue.SetControlledByExecutor(false);
	shellqueue.SetImmutable(false);
	shellqueue.SetUnstoppable(true);
	shellqueue.SetType(QUEUE_TYPE_SHELL);
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
