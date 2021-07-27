#pragma once

#ifndef _H_XMLMACROS
#define _H_XMLMACROS

#define _CRT_SECURE_NO_WARNINGS

#include<string>
#include<vector>
#include<variant>
#include<iostream>

using namespace std;

static const char* boolstr[] = { "True", "False" };
#define VALUE_TYPE_INTEGER 0
#define VALUE_TYPE_DOUBLE 1
#define VALUE_TYPE_STRING 2
#define VALUE_TYPE_BOOLEAN 3

struct ConfigNode
{
	string nodename;
	int valuetype = VALUE_TYPE_INTEGER;
	variant<int, double, string, bool> var;

	int Print();
};

#define START_CONFIG_NODES_REGISTER(node) vector<node> _confignodes_
#define ADD_CONFIG_NODE(nodenamestr, _nodename, _valuetype, defaultvalue) ConfigNode _newnode_##_nodename##_;\
_newnode_##_nodename##_.nodename = nodenamestr;\
_newnode_##_nodename##_.valuetype = _valuetype;\
_newnode_##_nodename##_.var.emplace<_valuetype>(defaultvalue);\
_confignodes_.push_back(_newnode_##_nodename##_);

#endif // !_H_XMLMACROS