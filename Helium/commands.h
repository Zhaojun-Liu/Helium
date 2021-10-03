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
class CommandConstantString;
class CommandPlaceHolder;
class RequiredArgument;
class OptionalArgument;
class CommandEntry;

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
	bool hasargument;
public:
	virtual _CommandEntry* GetCommandClassType();
};

class CommandConstantString : public _BasicHeliumCommand {
public:
	virtual CommandConstantString* GetCommandClassType();
};
class CommandPlaceHolder : public _BasicHeliumCommand {
public:
	virtual CommandPlaceHolder* GetCommandClassType();
};
class RequiredArgument : public _CommandArgument {
public:
	virtual RequiredArgument* GetCommandClassType();
};
class OptionalArgument : public _CommandArgument {
public:
	virtual OptionalArgument* GetCommandClassType();
};
class CommandEntry : public _CommandEntry {
public:
	virtual CommandEntry* GetCommandClassType();
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
class ShellCommandQueue : public _BasicHeliumCommandQueue {
public:
	virtual ShellCommandQueue* GetCommandQueueClassType();
};
class RuntimeCommandQueue : public _BasicHeliumCommandQueue {
public:
	virtual RuntimeCommandQueue* GetCommandQueueClassType();
};
class SaveableCommandQueue : public _BasicHeliumCommandQueue {
public:
	virtual SaveableCommandQueue* GetCommandQueueClassType();
};