#include"commands.h"

vector<HeliumCommandQueue> cmdqueuelist;
vector<vector<string>> cmdcompletions;
vector<pair<string, Replxx::Color>> cmdcolor;

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
/*
vector<string> cmdcompletions{
	"!!He",

	"help",

	"cmdqueue",
	"add", "remove", "start", "stop", "pause", "rename", "status", "list", "reload", "load", "query", "delete", "insert",// "setattr"


	"config",
	"save", "setattr",//"reload"

	"permission",
	"set",//"reload", "save", "query", "list", "remove"

	"extensions",
	"unload", "enable", "disable",//, "list", "reload", "load"

	"server",
	"setdefault", "restart", "stop", "rcon"//, "setattr", "status", "start"
};

vector<pair<string, Replxx::Color>> cmdcolors{
	{"!!He", Replxx::Color::BRIGHTBLUE},

	{"help", Replxx::Color::BRIGHTMAGENTA},
	{"cmdqueue", Replxx::Color::BRIGHTMAGENTA},
	{"permission", Replxx::Color::BRIGHTMAGENTA},
	{"extensions", Replxx::Color::BRIGHTMAGENTA},
	{"server", Replxx::Color::BRIGHTMAGENTA},
	{"config", Replxx::Color::BRIGHTMAGENTA},

	{"add", Replxx::Color::YELLOW},
	{"remove", Replxx::Color::YELLOW},
	{"start", Replxx::Color::YELLOW},
	{"stop", Replxx::Color::YELLOW},
	{"pause", Replxx::Color::YELLOW},
	{"rename", Replxx::Color::YELLOW},
	{"status", Replxx::Color::YELLOW},
	{"list", Replxx::Color::YELLOW},
	{"reload", Replxx::Color::YELLOW},
	{"load", Replxx::Color::YELLOW},
	{"query", Replxx::Color::YELLOW},
	{"delete", Replxx::Color::YELLOW},
	{"insert", Replxx::Color::YELLOW},
	{"save", Replxx::Color::YELLOW},
	{"setattr", Replxx::Color::YELLOW},
	{"set", Replxx::Color::YELLOW},
	{"unload", Replxx::Color::YELLOW},
	{"enable", Replxx::Color::YELLOW},
	{"disable", Replxx::Color::YELLOW},
	{"setdefault", Replxx::Color::YELLOW},
	{"restart", Replxx::Color::YELLOW},
	{"stop", Replxx::Color::YELLOW},
	{"rcon", Replxx::Color::YELLOW},

	{"[\\-|+]{0,1}[0-9]+", Replxx::Color::BRIGHTGREEN},
	{"[\\-|+]{0,1}[0-9]*\\.[0-9]+", Replxx::Color::BRIGHTGREEN},
	{"[\\-|+]{0,1}[0-9]+e[\\-|+]{0,1}[0-9]+", Replxx::Color::BRIGHTGREEN}
};
*/
#pragma region Callback
Replxx::completions_t hook_completion(std::string const& context, int& contextLen) {
	Replxx::completions_t completions;
	string prefix, temp;
	prefix = context.substr(context.length() - contextLen);
	cout << endl << prefix << endl;
	temp = context.substr(0, context.length() - contextLen);
	cout << temp << endl;
	int cmdlevel = 0;
	while (true) {
		if (temp.find(' ') != string::npos) {
			temp.erase(0, temp.find(' '));
			cmdlevel++;
		}
	}

	for (auto const& e : cmdcompletions[cmdlevel]) {
		if (e.compare(0, prefix.size(), prefix) == 0) {
			Replxx::Color c = Replxx::Color::DEFAULT;
			completions.emplace_back(e.c_str(), c);
		}
	}

	return completions;
}

Replxx::hints_t hook_hint(std::string const& context, int& contextLen, Replxx::Color& color) {
	Replxx::hints_t hints;
	// only show hint if prefix is at least 'n' chars long
	// or if prefix begins with a specific character

	string prefix, temp;
	prefix = context.substr(context.length() - contextLen);
	cout << endl << prefix << endl;
	temp = context.substr(0, context.length() - contextLen);
	cout << temp << endl;
	int cmdlevel = 0;
	while (true) {
		if (temp.find(' ') != string::npos) {
			temp.erase(0, temp.find(' '));
			cmdlevel++;
		}
	}

	if (prefix.size() >= 1 && !prefix.empty()) {
		for (auto const& e : cmdcompletions[cmdlevel]) {
			if (e.compare(0, prefix.size(), prefix) == 0) {
				hints.emplace_back(e.c_str());
			}
		}
	}

	// set hint color to green if single match found
	if (hints.size() == 1) {
		color = Replxx::Color::GREEN;
	}

	return hints;
}
void hook_color(std::string const& context, Replxx::colors_t& colors) {
	int blankpos = 0, cmdlevel = 0;
	for (int i = 0; i < context.length(); i++) {
		if (context[i] == ' ') {
			auto word = context.substr(blankpos, i - blankpos);
				for (auto const& e : cmdcolor) {
					std::smatch match;

					while (regex_match(word, match, std::regex(e.first))) {
						if (match[0] == word) {
							for (int i = 0; i < word.length(); i++) {
								colors.at(blankpos + i) = e.second;
							}
						}
					}
				}
			
		}
	}
}
#pragma endregion

void _stdcall AddCompletion(int level, string cmd) {
	if (level < cmdcompletions.size()) {
		cmdcompletions[level].push_back(cmd);
	}
	else {
		cmdcompletions.resize(level - 1);
		cmdcompletions[level].push_back(cmd);
	}
}
int _stdcall DeleteCompletion(int level, string cmd) {
	if (level < cmdcompletions.size()) {
		for (auto it = cmdcompletions[level].begin(); it < cmdcompletions[level].end(); it++) {
			if (*it == cmd) cmdcompletions[level].erase(it);
		}
	}
	else {
		return -1;
	}
	return 0;
}