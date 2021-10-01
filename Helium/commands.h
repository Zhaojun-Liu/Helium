#pragma once

#include<map>
#include<string>

#include"tree.hh"

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
class RequiredEntry;
class OptionalEntry;

class _BasicHeliumCommand {
protected:
	string commanddesc;
	string commandstr;

	int execcounter;
	
	bool execenabled;
	bool hintenabled;
	bool autocompenabled;
};

class _CommandRoot : _BasicHeliumCommand {

};

class _CommandArgument : _BasicHeliumCommand {
protected:
	int argutype;
};

class _CommandEntry : _BasicHeliumCommand {
protected:
	bool hasargument;
};

class CommandConstantString : _BasicHeliumCommand {

};

class CommandPlaceHolder : _BasicHeliumCommand {

};

class RequiredArgument : _CommandArgument {

};

class OptionalArgument : _CommandArgument {

};

class RequiredEntry : _CommandEntry {

};

class OptionalEntry : _CommandEntry {

};