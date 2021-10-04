#pragma once

#ifndef _H_EVENTS
#define _H_EVENTS

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

int RegisterEvent(HeliumEvent* event, int eventnum);
int DeleteEvent(int eventnum);
int GetEvent(int eventnum, HeliumEvent* event);
int GetEventIterator(int eventnum, map<int, HeliumEvent>::iterator* outit);

int CreateEvent(int eventnum, int quantity = 1);

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
