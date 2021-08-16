#pragma once

#ifndef _H_CMDTREE
#define _H_CMDTREE

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS  

#include<vector>
#include<string>
#include<iostream>

#include"tree.hh"
#include"utils.h"

using namespace std;

typedef int(*HeliumCommandCallback)(pair<string, int>, string);

struct HeliumCommandRegisterInstance {
	HeliumCommandCallback callbackfn;
	string cmddesc;
	string cmd;

	int _stdcall operator=(HeliumCommandRegisterInstance* ins);
};

extern tree<HeliumCommandRegisterInstance> commandtree;

int _stdcall RegisterCommand(tree<HeliumCommandRegisterInstance>::iterator root, HeliumCommandRegisterInstance ins);
int _stdcall DeleteCommand(tree<HeliumCommandRegisterInstance>::iterator root);
int _stdcall SetupBuiltinCommand();

#endif // !_H_CMDTREE