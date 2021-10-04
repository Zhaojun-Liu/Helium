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

deque<HeliumEventInstance> eventsqueue;
map<int, HeliumEvent> eventmap;

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
