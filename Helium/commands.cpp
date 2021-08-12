#include"commands.h"

vector<HeliumCommandQueue> cmdqueuelist;

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

int _stdcall HeliumCommand::AutoSetType() {
	if (this->command.empty()) this->commandtype = CMD_TYPE_EMPTY;
	if (this->command.find_first_of("!!He") == 0) this->commandtype = CMD_TYPE_HELIUM;
	else this->commandtype = CMD_TYPE_MINECRAFT;
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
	while(this->queuestatus == QUEUE_STAT_EXECUTING) {
		if (this->commands.size() > 0) {
			auto cmdstr = this->commands.at(this->ip).command;
			switch (this->commands.at(this->ip).commandtype)
			{
			case CMD_TYPE_EMPTY:
				this->commands.at(this->ip).IncExecCounter();
				this->ip++;
				break;
			case CMD_TYPE_HELIUM:
				this->commands.at(this->ip).IncExecCounter();
				this->ip++;
				break;
			case CMD_TYPE_MINECRAFT:
				this->commands.at(this->ip).IncExecCounter();
				this->ip++;
				break;
			default:
				return -1;
				break;
			}
		}
	}
	return 0;
}

_stdcall HeliumCommandQueue::HeliumCommandQueue() {
	this->queuestatus = QUEUE_STAT_EMPTY;
	this->restart = false;
	this->immutable = false;
	this->unstoppable = false;
	this->isshell = false;
	CoCreateGuid(&this->queueguid);
}
_stdcall HeliumCommandQueue::HeliumCommandQueue(const HeliumCommandQueue& queue) {
	this->commands = queue.commands;
	this->immutable = queue.immutable;
	this->unstoppable = queue.unstoppable;
	this->restart = queue.restart;
	CoCreateGuid(&this->queueguid);
	this->server = queue.server;
	this->queuename = queue.queuename;
	this->isshell = false;
	if (queue.queuestatus != QUEUE_STAT_DUMPING && queue.queuestatus != QUEUE_STAT_LOADING && queue.queuestatus != QUEUE_STAT_EMPTY)
		this->queuestatus = QUEUE_STAT_READY;
	else
		this->queuestatus = queue.queuestatus;
}
_stdcall HeliumCommandQueue::HeliumCommandQueue(const vector<HeliumCommand>* cmds) {
	this->commands = *cmds;
	CoCreateGuid(&this->queueguid);
	this->restart = false;
	this->immutable = false;
	this->unstoppable = false;
	this->isshell = false;
	this->queuestatus = QUEUE_STAT_READY;
}

_stdcall HeliumCommandQueue::HeliumCommandQueue(string name) {
	this->queuestatus = QUEUE_STAT_EMPTY;
	this->restart = false;
	this->immutable = false;
	this->unstoppable = false;
	this->queuename = name;
	this->isshell = false;
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
		this->queuestatus = QUEUE_STAT_EXECUTING;
		thread exec(&HeliumCommandQueue::ExecThreadFunc, this);
		this->execthread = move(exec);
	}
	return 0;
}

int _stdcall HeliumCommandQueue::QueryCommand(string cmd) {
	int i = 0;
	for (vector<HeliumCommand>::iterator it = this->commands.begin(); it != this->commands.end(); it++) {
		i++;
		if (it->command == cmd) return i;
	}
	return -1;
}
int _stdcall HeliumCommandQueue::QueryCommand(LPCGUID guid) {
	int i = 0;
	for (vector<HeliumCommand>::iterator it = this->commands.begin(); it < this->commands.end(); it++) {
		i++;
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

int _stdcall InitShellQueue() {
	HeliumCommandQueue shellqueue;
	shellqueue.queuename = "HeliumShell";
	shellqueue.queuestatus = QUEUE_STAT_READY;
	shellqueue.unstoppable = true;
	shellqueue.restart = false;
	shellqueue.isshell = true;
	shellqueue.immutable = true;
	cmdqueuelist.push_back(shellqueue);
	cmdqueuelist.begin()->StartExecute();
	return 0;
}

int _stdcall NewShellCommand(string cmd) {
	HeliumCommand newcmd(cmd);
	cmdqueuelist.begin()->InsertCommand(&newcmd);
	return 0;
}
