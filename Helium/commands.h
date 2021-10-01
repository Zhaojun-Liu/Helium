#pragma once

#include<map>
#include<string>

#include"tree.hh"
#include"replxx/replxx.hxx"

using namespace std;
//fully rewrited command module during the 72th national day xd
class _BasicHeliumCommand;
class _CommandArgument;
class _CommandEntry;
class _CommandRoot;
class CommandConstantString;
class CommandPlaceHolder;
class RequiredArgument;
class OptionalArgument;
class CommandEntry;

class _BasicHeliumCommandQueue;
class ShellCommandQueue;
class RuntimeCommandQueue;
class SaveableCommandQueue;

extern tree<_BasicHeliumCommand> HeliumCommandTree;

class _BasicHeliumCommand {
protected:
	string commanddesc;
	string commandstr;

	int execcounter;
	
	bool execenabled;
	bool hintenabled;
	bool autocompenabled;
};
class _CommandRoot : virtual public _BasicHeliumCommand {

};
class _CommandArgument : virtual public _BasicHeliumCommand {
protected:
	int argutype;
};
class _CommandEntry : virtual public _BasicHeliumCommand {
protected:
	bool hasargument;
};

class CommandConstantString : public _BasicHeliumCommand {

};
class CommandPlaceHolder : public _BasicHeliumCommand {

};
class RequiredArgument : public _CommandArgument {

};
class OptionalArgument : public _CommandArgument {

};
class CommandEntry : public _CommandEntry {

};


class _BasicHeliumCommandQueue {

};
class ShellCommandQueue : public _BasicHeliumCommandQueue {

};
class RuntimeCommandQueue : public _BasicHeliumCommandQueue {

};
class SaveableCommandQueue : public _BasicHeliumCommandQueue {

};