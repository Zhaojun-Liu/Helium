#pragma once

#ifndef _H_PARSE
#define _H_PARSE

#define NULL 0
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include<string>
#include<map>
#include<algorithm>
#include<thread>
#include"utils.h"

using namespace std;

typedef struct ServerStartEvent {
	LONG port = NULL;
	ServerStartEvent(int port_) {
		this->port = port_;
	}
} ServerStartEvent;

typedef struct ServerStartedEvent {
	long itime;
	ServerStartedEvent(long itime) {
		this->itime = itime;
	}
}ServerStartedEvent;

typedef struct ServerStopEvent {
	int exitcode = 0;
	ServerStopEvent(int code) {
		this->exitcode = code;
	}
} ServerStopEvent;

typedef struct ServerInfoEvent {
	char* lpRawOutput = NULL;
} ServerInfoEvent;

typedef struct PlayerInfoEvent {
	char* lpRawOutput = NULL;
	char* lpPlayer = NULL;
} PlayerInfoEvent;

//[10:36:31] [Server thread/INFO]: Time elapsed: 15215 ms
ServerStartedEvent _stdcall ParseServerStarted(const char* content);
ServerStartEvent _stdcall ParseServerStart(const char* content);
#endif // !_H_PARSE
