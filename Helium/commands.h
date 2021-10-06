#pragma once

#ifndef _H_COMMANDS
#define _H_COMMANDS

#include<map>
#include<string>

#include"tree.hh"
#define REPLXX_STATIC
#include"replxx/replxx.hxx"

using namespace std;
using namespace replxx;
//fully rewrited command module during the 72th national day xd
class _BasicHeliumCommand;

class _CommandArgument;
class _CommandEntry;
class _CommandRoot;
class _CommandBinding;
class _ArgumentNumber;
class _ArgumentString;

class CommandConstantString;
class CommandPlaceHolder;
class CommandEntry;

class SingleFixedCommandBind;
class SingleVariableCommandBind;
class MultiFixedCommandBind;
class MultiVariableCommandBind;

class _BasicHeliumCommandQueue;

class ShellCommandQueue;
class RuntimeCommandQueue;
class SaveableCommandQueue;

extern tree<_BasicHeliumCommand> HeliumCommandTree;
#pragma region CommandClassBase
class _BasicHeliumCommand {
protected:
	string commanddesc;
	string commandstr;
	
	bool listenabled;
	bool execenabled;
	bool hintenabled;
	bool autocompenabled;
public:
	virtual _BasicHeliumCommand* GetCommandClassType();
};
class _CommandRoot : virtual public _BasicHeliumCommand {
public:
	virtual _CommandRoot* GetCommandClassType();
};
class _CommandArgument : virtual public _BasicHeliumCommand {
protected:
	bool optional;
	bool preprocenable;
public:
	virtual _CommandArgument* GetCommandClassType();
	virtual bool EnablePreprocessing();
	virtual bool DisablePreprocessing();
};
class _CommandEntry : virtual public _BasicHeliumCommand {
protected:
	int exectype;
	union execinfo {

	};

	bool hasargument;
public:
	virtual _CommandEntry* GetCommandClassType();
};
class _CommandBinding : virtual public _BasicHeliumCommand {
public:
	virtual _CommandBinding* GetCommandClassType();
};
#pragma endregion
class CommandConstantString : virtual public _BasicHeliumCommand {
public:
	virtual CommandConstantString* GetCommandClassType();
};
class CommandPlaceHolder : virtual public _BasicHeliumCommand {
public:
	virtual CommandPlaceHolder* GetCommandClassType();
};
class CommandEntry : virtual public _CommandEntry {
public:
	virtual CommandEntry* GetCommandClassType();
};
class SingleFixedCommandBind : virtual public _CommandBinding{
public:
	virtual SingleFixedCommandBind* GetCommandClassType();
};
class SingleVariableCommandBind : virtual public _CommandBinding {
public:
	virtual SingleVariableCommandBind* GetCommandClassType();
};
class MultiFixedCommandBind : virtual public _CommandBinding {
public:
	virtual MultiFixedCommandBind* GetCommandClassType();
};
class MultiVariableCommandBind : virtual public _CommandBinding {
public:
	virtual MultiVariableCommandBind* GetCommandClassType();
};


class _BasicHeliumCommandQueue {
protected:
	int queuetype;
	int queuestate;
	vector<string>::iterator execit;

	vector<string> originalcommands;
public:
	virtual _BasicHeliumCommandQueue* GetCommandQueueClassType();
};
class ShellCommandQueue : virtual public _BasicHeliumCommandQueue {
public:
	virtual ShellCommandQueue* GetCommandQueueClassType();
};
class RuntimeCommandQueue : virtual public _BasicHeliumCommandQueue {
public:
	virtual RuntimeCommandQueue* GetCommandQueueClassType();
};
class SaveableCommandQueue : virtual public _BasicHeliumCommandQueue {
public:
	virtual SaveableCommandQueue* GetCommandQueueClassType();
};

Replxx::completions_t hook_completion(std::string const& context, int& contextLen);
Replxx::hints_t hook_hint(std::string const& context, int& contextLen, Replxx::Color& color);
void hook_color(std::string const& context, Replxx::colors_t& colors);
#endif // !_H_COMMANDS