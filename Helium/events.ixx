/*
* Helium is a customizable extension system for Minecraft server.
* You can get the lastest source code and releases of Helium at :
* https://github.com/Helium-DevTeam/Helium
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

export module Helium.Events;

import Helium.UUIDManager;
import Helium.Logger;

import <string>;
import <iostream>;
import <vector>;
import <thread>;
import <list>;
import <any>;
import <boost/function.hpp>;
import <boost/signals2.hpp>;

using namespace std;
using namespace boost::signals2;

export{
	namespace Helium {
		enum HeliumEventList {
			EMPTY_EVENT = 0,	//done
			HELIUM_START = 1,	//done
			HELIUM_STOP = 2,	//done
			EXTENSION_LOAD = 3,	//done
			EXTENSION_UNLOAD = 4,	//done
			SERVER_START = 5,	//done
			SERVER_INITIALIZATION_FINISH = 6,	//done
			SERVER_STOP = 7,	//done
			SERVER_OUTPUT = 8,	//done
			PLAYER_JOIN = 9,	//done
			PLAYER_LEAVE = 10,	//done
			GENERAL_INPUT = 11,	//done
			CONSOLE_INPUT = 12,	//done
			PLAYER_INPUT = 13,	//done
			USER_DEFINED_MIN = 25565	//reserved
		};

		const string helium_event_str[] = {
			"EMPTY_EVENT",
			"HELIUM_START",
			"HELIUM_STOP",
			"EXTENSION_LOAD",
			"EXTENSION_UNLOAD",
			"SERVER_START",
			"SERVER_INITIALIZATION_FINISH",
			"SERVER_STOP",
			"SERVER_OUTPUT",
			"PLAYER_JOIN",
			"PLAYER_LEAVE",
			"GENERAL_INPUT",
			"CONSOLE_INPUT",
			"PLAYER_INPUT",
			"USER_DEFINED_MIN"
		};

		const string helium_event_listener_str[] = {
			"EmptyEvent",
			"HeliumStart",
			"HeliumStop",
			"ExtensionLoad",
			"ExtensionUnload",
			"ServerStart",
			"ServerInitializationFinish",
			"ServerStop",
			"ServerOutput",
			"PlayerJoin",
			"PlayerLeave",
			"GeneralInput",
			"ConsoleInput",
			"PlayerInput",
			""
		};

		class HeliumEventManager {
		public:
			typedef boost::function<int(const list<any>)> StandardHeliumListener;
			typedef signal<int(const list<any>)> StandardHeliumSignal;

			HeliumEventManager() {};
			~HeliumEventManager() {};

			int RegisterEventListener(const int& event_num, const StandardHeliumListener func);
			int DispatchEvent(const int& event_num, const list<any> param);

			void TraceEvent(const int& event_num) noexcept;
			void UntraceEvent(const int& event_num) noexcept;
			bool IsEventTraced(const int& event_num) noexcept;
		private:
			map<int, shared_ptr<StandardHeliumSignal>> event_map;
			static map<int, bool> is_traced;
		};

		HeliumEventManager helium_event_manager;
		string EventIDToDesc(const int& id);
		string EventIDToListenerFunc(const int& id);
	}
}

namespace Helium {
	map<int, bool> HeliumEventManager::is_traced = map<int, bool>();

	int HeliumEventManager::RegisterEventListener(const int& event_num, const StandardHeliumListener func) {
		auto iter = this->event_map.find(event_num);
		if (iter != this->event_map.end()) {
			iter->second->connect(func);
		}
		else {
			this->event_map[event_num] = make_shared<StandardHeliumSignal>();
			this->event_map[event_num]->connect(func);
		}
		return 0;
	}
	int HeliumEventManager::DispatchEvent(const int& event_num, const list<any> param) {
		auto iter = this->event_map.find(event_num);
		if (this->is_traced.count(event_num) > 0 && this->is_traced[event_num]) {
			log << HLL::LL_WARN << "Traced event created " << event_num
				<< "(" << EventIDToDesc(event_num) << ")." << hendl;
		}
		if (iter != this->event_map.end()) {
			auto signal_ptr = iter->second;
			(*signal_ptr)(param);
		}
		else {
			log << HLL::LL_ERR << "Cannot find the event : " << event_num
				<< "(" << helium_event_str[event_num] << ")" << hendl;
			return -1;
		}
		return 0;
	}

	void HeliumEventManager::TraceEvent(const int& event_num) noexcept {
		this->is_traced[event_num] = true;
	}
	void HeliumEventManager::UntraceEvent(const int& event_num) noexcept {
		this->is_traced[event_num] = false;
	}
	bool HeliumEventManager::IsEventTraced(const int& event_num) noexcept {
		if (this->is_traced.count(event_num) > 0) {
			if (this->is_traced[event_num]) return true;
		}
		return false;
	}

	string EventIDToDesc(const int& id) {
		if (id >= HeliumEventList::EMPTY_EVENT && id <= HeliumEventList::USER_DEFINED_MIN) {
			return helium_event_str[id];
		}
		return "";
	}
	string EventIDToListenerFunc(const int& id) {
		if (id >= HeliumEventList::EMPTY_EVENT && id <= HeliumEventList::USER_DEFINED_MIN) {
			return helium_event_listener_str[id];
		}
		return "";
	}
}