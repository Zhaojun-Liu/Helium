#pragma once

#ifndef _H_XMLMACROS
#define _H_XMLMACROS

#include<string>
#include<vector>
#include<variant>

using namespace std;

struct ConfigNode
{
	string nodename;
	int valuetype;
	variant<int, double, string, bool> var;
};

#define START_CONFIG_NODES_REGISTER() vector<ConfigNode> _confignodes_
#define ADD_CONFIG_NODE(nodenamestr, nodename, valuetype) ConfigNode _newnode_##nodename##_ = {nodenamestr, valuetype};\
_confignodes_.push_back(_newnode_##nodename##_);
#define VALUE_TYPE_INTEGER 0
#define VALUE_TYPE_DOUBLE 1
#define VALUE_TYPE_STRING 2
#define VALUE_TYPE_BOOLEAN 3

#endif // !_H_XMLMACROS