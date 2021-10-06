#pragma once

#ifndef _H_EVENTS
#define _H_EVENTS
#define EXPORTFUNC extern "C" _declspec(dllexport)

#define HELIUM_EVENT_EXTENSION_ON_LOAD 0
#define HELIUM_EVENT_EXTENSION_ON_FULLY_LOADED 1
#define HELIUM_EVENT_EXTENSION_ON_UNLOAD 2
#define HELIUM_EVENT_SERVER_ON_OUTPUT 3
#define HELIUM_EVENT_SERVER_ON_INFO 4
#define HELIUM_EVENT_SERVER_ON_USER_INFO 5
#define HELIUM_EVENT_SERVER_START 6
#define HELIUM_EVENT_SERVER_STARTUP 7
#define HELIUM_EVENT_SERVER_STOP 8
#define HELIUM_EVENT_PLAYER_JOIN 9
#define HELIUM_EVENT_PLAYER_LEFT 10
#define HELIUM_EVENT_HELIUM_START 11
#define HELIUM_EVENT_HELIUM_FINISHED_INIT 12
#define HELIUM_EVENT_HELIUM_STOP 13
#define HELIUM_EVENT_USER_CUSTOM_START 20

#define HELIUM_EVENT_EXTENSION_ON_LOAD_DEF_FUNC_NAME "OnExtensionLoad"
#define HELIUM_EVENT_EXTENSION_ON_FULLY_LOADED_DEF_FUNC_NAME "OnExtensionFullyLoaded"
#define HELIUM_EVENT_EXTENSION_ON_UNLOAD_DEF_FUNC_NAME "OnExtensionUnload"
#define HELIUM_EVENT_SERVER_ON_OUTPUT_DEF_FUNC_NAME "OnServerOutput"
#define HELIUM_EVENT_SERVER_ON_INFO_DEF_FUNC_NAME "OnServerInfo"
#define HELIUM_EVENT_SERVER_ON_USER_INFO_DEF_FUNC_NAME "OnUserInfo"
#define HELIUM_EVENT_SERVER_START_DEF_FUNC_NAME "OnServerStart"
#define HELIUM_EVENT_SERVER_STARTUP_DEF_FUNC_NAME "OnServerStartup"
#define HELIUM_EVENT_SERVER_STOP_DEF_FUNC_NAME "OnServerStop"
#define HELIUM_EVENT_PLAYER_JOIN_DEF_FUNC_NAME "OnPlayerJoin"
#define HELIUM_EVENT_PLAYER_LEFT_DEF_FUNC_NAME "OnPlayerLeft"
#define HELIUM_EVENT_HELIUM_START_DEF_FUNC_NAME "OnHeliumStart"
#define HELIUM_EVENT_HELIUM_FINISHED_INIT_DEF_FUNC_NAME "OnHeliumFinishedInit"
#define HELIUM_EVENT_HELIUM_STOP_DEF_FUNC_NAME "OnHeliumStop"

#define GET_EVENT_NUM(eventtype, eventname) (HELIUM_EVENT##_##eventtype##_##eventname)
#define GET_EVENT_DEF_FUNC_NAME(eventtype, eventname) (HELIUM_EVENT##_##eventtype##_##eventname##_##_DEF_FUNC_NAME)

#include<deque>
#include<map>
#include<string>
#include<vector>
#include<guiddef.h>

using namespace std;

typedef int (_stdcall* HeliumEventCallbackType)(int events);

class HeliumEvent;
class HeliumEventInstance;

extern deque<HeliumEventInstance*> eventsqueue;
extern map<int, HeliumEvent*> eventmap;

EXPORTFUNC int RegisterHeliumEvent(HeliumEvent* event, int eventnum);
EXPORTFUNC int DeleteHeliumEvent(int eventnum);
EXPORTFUNC int GetHeliumEvent(int eventnum, HeliumEvent* event);
EXPORTFUNC int GetHeliumEventIterator(int eventnum, map<int, HeliumEvent*>::iterator* outit);

EXPORTFUNC int CreateHeliumEvent(int eventnum, int quantity = 1);
EXPORTFUNC int BlockHeliumEvent(int eventnum);

typedef int (*RegisterHeliumEvent_FuncT)(HeliumEvent* event, int eventnum);
typedef int (*DeleteHeliumEvent_FuncT)(int eventnum);
typedef int (*GetHeliumEvent_FuncT)(int eventnum, HeliumEvent* event);
typedef int (*GetHeliumEventIterator_FuncT)(int eventnum, map<int, HeliumEvent*>::iterator* outit);

typedef int (*CreateHeliumEvent_FuncT)(int eventnum, int quantity);
typedef int (*BlockHeliumEvent_FuncT)(int eventnum);

class HeliumEvent {
public:
	struct CallbackFunctionInfo {
		GUID funcguid;
		HeliumEventCallbackType funcptr;
		bool funccallbackenable;

		CallbackFunctionInfo();
	};
	HeliumEvent();

	int RegisterListenerFunction(HeliumEventCallbackType funcptr);
	CallbackFunctionInfo GetListenerFunction(LPGUID guid);
	int DeleteListenerFunction(LPGUID guid);
	void EnableCallback();
	void DisableCallback();
	void EnableFunctionCallback(LPGUID guid);
	void DisableFunctionCallback(LPGUID guid);
protected:
	string eventname;
	string eventdesc;
	bool callbackenable;

	vector<CallbackFunctionInfo> listenerfuncs;
};

class HeliumEventInstance {

};

#endif // !_H_EVENTS
