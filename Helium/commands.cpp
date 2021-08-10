#include"commands.h"
#pragma region command
_stdcall HeliumCommand::HeliumCommand() {
	CoCreateGuid(&this->commandguid);
	this->commandtype = CMD_TYPE_EMPTY;
	this->executecounter = 0;
}
_stdcall HeliumCommand::HeliumCommand(const HeliumCommand* cmd) {
	this->commandguid = cmd->commandguid;
	this->command = cmd->command;
	this->commandtype = cmd->commandtype;
	this->executecounter = cmd->executecounter;
}
_stdcall HeliumCommand::HeliumCommand(string cmd) {
	this->command = cmd;
	CoCreateGuid(&this->commandguid);
	this->executecounter = 0;
	this->AutoSetType();
}

int _stdcall HeliumCommand::Execute() {
	switch (this->commandtype)
	{
	case CMD_TYPE_EMPTY:
		return 0;
	case CMD_TYPE_HELIUM:
		break;
	case CMD_TYPE_MINECRAFT:
		break;
	default:
		break;
	}
	return 0;
}
int _stdcall HeliumCommand::AutoSetType() {
	return 0;
}

int _stdcall HeliumCommand::GetCommandGUID(LPGUID guid) {
	*guid = this->commandguid;
	return 0;
}

string _stdcall HeliumCommand::GetCommand() {
	return this->command;
}
string _stdcall HeliumCommand::SetCommand(string cmd) {
	this->command = cmd;
	return cmd;
}

int _stdcall HeliumCommand::GetExecCounter() {
	return this->executecounter;
}
int _stdcall HeliumCommand::IncExecCounter() {
	this->executecounter++;
	return this->executecounter;
}

int _stdcall HeliumCommand::GetCommandType() {
	return this->commandtype;
}
#pragma endregion

#pragma region commandqueue
int _stdcall HeliumCommandQueue::ExecThreadFunc() {
	return 0;
}

_stdcall HeliumCommandQueue::HeliumCommandQueue() {
	this->queuestatus = QUEUE_STAT_EMPTY;
	this->restart = false;
	this->immutable = false;
	this->unstoppable = false;
	CoCreateGuid(&this->queueguid);
}
_stdcall HeliumCommandQueue::HeliumCommandQueue(const HeliumCommandQueue* queue) {
	this->commands = queue->commands;
	this->immutable = queue->immutable;
	this->unstoppable = queue->unstoppable;
	this->restart = queue->restart;
	CoCreateGuid(&this->queueguid);
	this->server = queue->server;
	this->queuename = queue->queuename;
	if (queue->queuestatus != QUEUE_STAT_DUMPING && queue->queuestatus != QUEUE_STAT_LOADING && queue->queuestatus != QUEUE_STAT_EMPTY)
		this->queuestatus = QUEUE_STAT_READY;
	else
		this->queuestatus = queue->queuestatus;
}
_stdcall HeliumCommandQueue::HeliumCommandQueue(const vector<HeliumCommand>* cmds) {
	this->commands = *cmds;
	CoCreateGuid(&this->queueguid);
	this->restart = false;
	this->immutable = false;
	this->unstoppable = false;
	this->queuestatus = QUEUE_STAT_READY;
}

_stdcall HeliumCommandQueue::HeliumCommandQueue(string name) {
	this->queuestatus = QUEUE_STAT_EMPTY;
	this->restart = false;
	this->immutable = false;
	this->unstoppable = false;
	this->queuename = name;
	CoCreateGuid(&this->queueguid);
}

string _stdcall HeliumCommandQueue::GetQueueName() {
	return this->queuename;
}
int _stdcall HeliumCommandQueue::SetQueueName(string name) {
	if (!this->immutable) this->queuename = name;
	else return -1;
	return 0;
}

int _stdcall HeliumCommandQueue::GetGUID(LPGUID guid) {
	*guid = this->queueguid;
	return 0;
}

int _stdcall HeliumCommandQueue::GetQueueStatus() {
	return this->queuestatus;
}

bool HeliumCommandQueue::GetRestart() {
	return this->restart;
}
bool HeliumCommandQueue::SetRestart(bool r) {
	if (!this->immutable) this->restart = r;
	else return -1;
	return 0;
}

bool HeliumCommandQueue::GetUnstoppable() {
	return this->unstoppable;
}
bool HeliumCommandQueue::SetUnstoppable(bool u) {
	if (!this->immutable) this->unstoppable = u;
	else return -1;
	return 0;
}

bool HeliumCommandQueue::GetImmutable() {
	return this->immutable;
}
bool HeliumCommandQueue::SetImmutable(bool i) {
	if (!this->immutable) this->immutable = i;
	else return -1;
	return 0;
}

int _stdcall HeliumCommandQueue::StartExecute() {
	if (this->queuestatus == QUEUE_STAT_READY) {

	}
	return 0;
}

int _stdcall HeliumCommandQueue::QueryCommand(string cmd) {
	for (vector<HeliumCommand>::iterator it = this->commands.begin(), int i = 0; it < this->commands.end(); it++, i ++) {
		if (it->command == cmd) return i;
	}
	return -1;
}
int _stdcall HeliumCommandQueue::QueryCommand(LPCGUID guid) {
	for (vector<HeliumCommand>::iterator it = this->commands.begin(), int i = 0; it < this->commands.end(); it++, i++) {
		if (it->commandguid == *guid) return i;
	}
	return -1;
}

int _stdcall HeliumCommandQueue::DeleteCommand(string cmd) {
	for (vector<HeliumCommand>::iterator it = this->commands.begin(); it < this->commands.end(); it++) {
		if (it->command == cmd) {
			this->commands.erase(it);
			return 0;
		}
	}
	return -1;
}
int _stdcall HeliumCommandQueue::DeleteCommand(LPCGUID guid) {
	for (vector<HeliumCommand>::iterator it = this->commands.begin(); it < this->commands.end(); it++) {
		if (it->commandguid == *guid) {
			this->commands.erase(it);
			return 0;
		}
	}
	return -1;
}
int _stdcall HeliumCommandQueue::DeleteCommand(int index) {
	this->commands.erase(this->commands.begin() + index);
	return 0;
}

int _stdcall HeliumCommandQueue::InsertCommand(const HeliumCommand* cmd) {
	this->commands.push_back(*cmd);
	return 0;
}
int _stdcall HeliumCommandQueue::InsertCommand(const HeliumCommand* cmd, int index) {
	this->commands.insert(this->commands.begin() + index, *cmd);
	return 0;
}
int _stdcall HeliumCommandQueue::InsertCommand(const HeliumCommand* cmd, LPCGUID guid) {
	for (vector<HeliumCommand>::iterator it = this->commands.begin(); it < this->commands.end(); it++) {
		if (it->commandguid == *guid) {
			this->commands.insert(it, *cmd);
			return 0;
		}
	}
	return -1;
}
#pragma endregion

int _stdcall StartShellThread() {
	return 0;
}
int _stdcall ShellThread() {
	return 0;
}