#pragma once

#ifndef _H_PARSE
#define _H_PARSE

#define NULL 0
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include<regex>
#include<vector>
#include<string>
#include<map>
#include<algorithm>
#include<thread>

#include"events.h"
#include"utils.h"

using namespace std;

class ParseEvent {
public:
	ParseEvent();

	int SetParseRegex(regex* preg);
	int AddResultStringRegex(regex* preg);
	int AddResultStringRegex(vector<regex> pregvec);

protected:
	regex parseregex;
	vector<regex> resultstringsregex;
	vector<int> eventnum;
	bool parseenable;
};

typedef struct ServerStart {
	LONG port = NULL;
	ServerStart() {
		this->port = 0;
	}
} ServerStartEvent;

typedef struct ServerStarted {
	long itime;
	ServerStarted() {
		this->itime = 0;
	}
}ServerStarted;

class Info {
private:
	bool IsPlayer = false;
	char* lpRawOutput = NULL;
	char* lpPlayer = NULL;
	char* lpContent = NULL;
public:
	Info() {/*do something*/ }
	bool isPlayer() {
		return IsPlayer;
	}
	bool isServer() {
		return !IsPlayer;
	}
};

//[10:36:31] [Server thread/INFO]: Time elapsed: 15215 ms

class VanillaParser {
public:
	WINAPI VanillaParser();
	WINAPI ~VanillaParser();
	void* WINAPI parse(const char*);
private:
	ServerStarted _stdcall parseServerStarted(const char*);
	ServerStart _stdcall parseServerStart(const char*);
	Info WINAPI parsePlayerInfo(const char*);
};



#endif // !_H_PARSE
