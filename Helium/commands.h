#pragma once

#include<map>
#include<string>

#include"tree.hh"

using namespace std;
//fully rewrited command module during the 72th national day xd
class _BasicHeliumCommand;
class ConstantString;
class RequiredArgument;
class OptionalArgument;
class RequiredEntry;
class OptionalEntry;

class _BasicHeliumCommand {
private:
	string commanddesc;
	string commandstr;

	int execcounter;
	
	bool execenabled;
	bool hintenabled;
	bool autocompenabled;
};

class _CommandArgument : _BasicHeliumCommand {

};

class _CommandEntry : _BasicHeliumCommand {
private:
	bool hasargument;
};

class ConstantString : _BasicHeliumCommand {

};

class RequiredArgument : _CommandArgument {

};

class OptionalArgument : _CommandArgument {

};

class RequiredEntry : _CommandEntry {

};

class OptionalEntry : _CommandEntry {

};