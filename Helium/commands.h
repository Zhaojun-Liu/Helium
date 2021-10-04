#pragma once

#include<map>
#include<string>

#include"tree.hh"
#include"replxx/replxx.hxx"

using namespace std;
//fully rewrited command module during the 72th national day xd
class _BasicHeliumCommand;	//纯抽象类

class _CommandArgument;
class _CommandEntry;
class _CommandRoot;
class _CommandBinding;

class CommandConstantString;
class CommandPlaceHolder;
class RequiredArgument;
class OptionalArgument;
class CommandEntry;

class SingleFixedCommandBind;
class SingleVariableCommandBind;
class MultiFixedCommandBind;
class MultiVariableCommandBind;


class _BasicHeliumCommandQueue;	//纯抽象类

class ShellCommandQueue;
class RuntimeCommandQueue;
class SaveableCommandQueue;

extern tree<_BasicHeliumCommand> HeliumCommandTree;

class _BasicHeliumCommand {
protected:
	string commanddesc;
	string commandstr;
	
	bool listenabled;
	bool execenabled;
	bool hintenabled;
	bool autocompenabled;
public:
	virtual _BasicHeliumCommand* GetCommandClassType() = 0;
};
class _CommandRoot : virtual public _BasicHeliumCommand {
public:
	virtual _CommandRoot* GetCommandClassType();
};
class _CommandArgument : virtual public _BasicHeliumCommand {
protected:
	int argutype;

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

class CommandConstantString : virtual public _BasicHeliumCommand {
public:
	virtual CommandConstantString* GetCommandClassType();
};
class CommandPlaceHolder : virtual public _BasicHeliumCommand {
public:
	virtual CommandPlaceHolder* GetCommandClassType();
};
class RequiredArgument : virtual public _CommandArgument {
public:
	virtual RequiredArgument* GetCommandClassType();
};
class OptionalArgument : virtual public _CommandArgument {
public:
	virtual OptionalArgument* GetCommandClassType();
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
	virtual _BasicHeliumCommandQueue* GetCommandQueueClassType() = 0;
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