/*
* Helium Pre-Alpha 0.6.1
* Copyright (C) 2021-2022 HeliumDevTeam
*
* Helium is a customizable extension system for Minecraft server which is written in C++.
* This project is inspired by the [Fallen-Breath/MCDReforged](https://github.com/Fallen-Breath/MCDReforged).
* We target to provide a liter, faster, and more customizable choice.
* As a trade-off, we sacrifice its portability and the simplicity of writing extensions.
* (we r sry that we haven't finish the first alpha version yet, if u r interested in our project, we recommend u to use mcdr as a temporary alternative)
* This project is licensed by the GPL-3.0-or-later license.
*
* Very very special thank to contributors of the following projects:
* [Fallen-Breath/MCDReforged](https://github.com/Fallen-Breath/MCDReforged)
* [kpeeters/tree.hh](https://github.com/kpeeters/tree.hh)
* [leethomason/tinyxml2](https://github.com/leethomason/tinyxml2/)
* [jcwangxp/Crossline](https://github.com/jcwangxp/Crossline/)
*
* You can get the lastest source code and releases of Helium at :
* https://github.com/Minecraft1248/Helium
*
* -------------------------------------------------------------------------------------------------------------------------------------------------------
*    This file is part of Helium.
*
*    Helium is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    Helium is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with Helium.  If not, see <https://www.gnu.org/licenses/>.
* -------------------------------------------------------------------------------------------------------------------------------------------------------
*/

#pragma once

#ifndef _H_EVENTS
#define _H_EVENTS

#include<deque>
#include<map>
#include<string>
#include<vector>
#include<guiddef.h>

namespace Helium {
	using namespace std;

#define EXPORTFUNC extern "C" _declspec(dllexport)

enum HeliumEventEnum {
	HELIUM_EVENT_EXTENSION_ON_LOAD,
	HELIUM_EVENT_EXTENSION_ON_FULLY_LOADED,
	HELIUM_EVENT_EXTENSION_ON_UNLOAD,
	HELIUM_EVENT_SERVER_ON_OUTPUT,
	HELIUM_EVENT_SERVER_ON_INFO,
	HELIUM_EVENT_SERVER_ON_USER_INFO,
	HELIUM_EVENT_SERVER_START,
	HELIUM_EVENT_SERVER_STARTUP,
	HELIUM_EVENT_SERVER_STOP,
	HELIUM_EVENT_PLAYER_JOIN,
	HELIUM_EVENT_PLAYER_LEFT,
	HELIUM_EVENT_HELIUM_START,
	HELIUM_EVENT_HELIUM_FINISHED_INIT,
	HELIUM_EVENT_HELIUM_STOP,
	HELIUM_EVENT_USER_CUSTOM_START,
};

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

	typedef int(_stdcall* HeliumEventCallbackType)(int events);

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
}