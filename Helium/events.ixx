/*
* Helium is a customizable extension system for Minecraft server.
* You can get the lastest source code and releases of Helium at :
* https://github.com/Minecraft1248/Helium
* ----------------------------------------------------------------------------------------
* Helium Copyright (C) 2021-2022 HeliumDevTeam
*
* This file is a part of Helium
*
* Helium is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Helium is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Helium.  If not, see <https://www.gnu.org/licenses/>.
* ----------------------------------------------------------------------------------------
*/

module;

#include<deque>
#include<map>
#include<string>
#include<vector>
#include<guiddef.h>

export module Helium.Events;

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

#define EXPORTFUNC extern "C" _declspec(dllexport)

using namespace std;

export{
	namespace Helium {
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
	}
}