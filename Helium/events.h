#pragma once

#ifndef _H_EVENTS
#define _H_EVENTS
#define EXPORTFUNC extern "C" _declspec(dllexport)

#include<deque>
#include<map>
#include<string>
#include<vector>
#include<guiddef.h>

using namespace std;

typedef int (_stdcall* HeliumEventCallbackType)(int events);

class HeliumEvent;
class HeliumEventInstance;

extern deque<HeliumEventInstance> eventsqueue;
extern map<int, HeliumEvent> eventmap;

EXPORTFUNC int RegisterHeliumEvent(HeliumEvent* event, int eventnum);
EXPORTFUNC int DeleteHeliumEvent(int eventnum);
EXPORTFUNC int GetHeliumEvent(int eventnum, HeliumEvent* event);
EXPORTFUNC int GetHeliumEventIterator(int eventnum, map<int, HeliumEvent>::iterator* outit);

EXPORTFUNC int CreateHeliumEvent(int eventnum, int quantity = 1);
EXPORTFUNC int BlockHeliumEvent(int eventnum);

typedef int (*RegisterHeliumEvent_FuncT)(HeliumEvent* event, int eventnum);
typedef int (*DeleteHeliumEvent_FuncT)(int eventnum);
typedef int (*GetHeliumEvent_FuncT)(int eventnum, HeliumEvent* event);
typedef int (*GetHeliumEventIterator_FuncT)(int eventnum, map<int, HeliumEvent>::iterator* outit);

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
