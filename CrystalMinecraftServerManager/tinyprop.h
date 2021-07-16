#pragma once
#include <iostream>
#include<string>
#include<map>
#include<cstdio>
#include<Windows.h>

using namespace std;
class TinyProp
{
public:
	TinyProp(const char* fname);
	~TinyProp();
	int read();
	int write();
	const char* get(const char* name);
	int set(const char* name, const char* value);
private:
	map<string, string> table;
	string filename;
};
