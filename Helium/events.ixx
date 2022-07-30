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
			EMPTY_EVENT,
			HELIUM_STARTUP,
			HELIUM_INITIALIZATION_START,
			HELIUM_INITIALIZATION_FINISH,
			HELIUM_FINALIZATION_START,
			HELIUM_FINALIZATION_FINISH,
			EXTENSION_LOAD,
			EXTENSION_UNLOAD,
			SERVER_START,
			SERVER_INITIALIZATION_FINISH,
			SERVER_STOP,
			PLAYER_JOIN,
			PLAYER_LEAVE,
			GENERAL_INPUT,
			CONSOLE_INPUT,
			SERVER_INPUT,
			USER_DEFINED_MIN
		};

		const string helium_event_str[] = {
			"EMPTY_EVENT",
			"HELIUM_STARTUP",
			"HELIUM_INITIALIZATION_START",
			"HELIUM_INITIALIZATION_FINISH",
			"HELIUM_FINALIZATION_START",
			"HELIUM_FINALIZATION_FINISH",
			"EXTENSION_LOAD",
			"EXTENSION_UNLOAD",
			"SERVER_START",
			"SERVER_INITIALIZATION_FINISH",
			"SERVER_STOP",
			"PLAYER_JOIN",
			"PLAYER_LEAVE",
			"GENERAL_INPUT",
			"CONSOLE_INPUT",
			"SERVER_INPUT",
			"USER_DEFINED_MIN"
		};

		class HeliumEventManager {
		public:
			typedef boost::function<int(const list<any>)> StandardHeliumListener;
			typedef signal<int(const list<any>)> StandardHeliumSignal;

			HeliumEventManager() {};
			~HeliumEventManager() {};

			int RegisterEventListener(const int& event_num, const StandardHeliumListener func);
			int CreateEvent(const int& event_num, const list<any> param);
		private:
			map<int, shared_ptr<StandardHeliumSignal>> event_map;
		};

		HeliumEventManager helium_event_manager;
	}
}

namespace Helium {
	int HeliumEventManager::RegisterEventListener(const int& event_num, const StandardHeliumListener func) {
		auto iter = this->event_map.find(event_num);
		log << HLL::LL_INFO << "Registering an event listener for event : " << event_num
			<< "(" << helium_event_str[event_num] << ")" << hendl;
		if (iter != this->event_map.end()) {
			iter->second->connect(func);
		}
		else {
			this->event_map[event_num] = make_shared<StandardHeliumSignal>();
			this->event_map[event_num]->connect(func);
		}
		return 0;
	}
	int HeliumEventManager::CreateEvent(const int& event_num, const list<any> param) {
		auto iter = this->event_map.find(event_num);
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
}