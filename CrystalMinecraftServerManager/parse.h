#pragma once
#define NULL 0
#include<string>
#include<map>
#include<algorithm>
#include<thread>
#include"utils.h"
using namespace std;
typedef struct ServerStartEvent {
	string port = NULL;
} ServerStartEvent;

typedef struct ServerStartedEvent {
	size_t itime;
	ServerStartedEvent(size_t itime) {
		this->itime = itime;
	}
}ServerStartedEvent;

typedef struct ServerStopEvent {

} ServerStopEvent;

typedef struct ServerInfoEvent {
	char* lpRawOutput = NULL;
} ServerInfoEvent;

typedef struct PlayerInfoEvent {
	char* lpRawOutput = NULL;
	char* lpPlayer = NULL;
} PlayerInfoEvent;

//[10:36:31] [Server thread/INFO]: Time elapsed: 15215 ms
ServerStartedEvent ParseServerStarted(const char* content);


