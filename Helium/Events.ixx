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

#include<boost/uuid/uuid.hpp>
#include<boost/utility/result_of.hpp>
#include<boost/typeof/typeof.hpp>
#include<boost/assign.hpp>
#include<boost/ref.hpp>
#include<boost/bind.hpp>
#include<boost/function.hpp>
#include<boost/signals2.hpp>

export module Helium.Events;

import Helium.UUIDManager;
import Helium.Logger;

import <iostream>;
import <vector>;
import <thread>;
import <list>;

using namespace std;
using namespace boost::uuids;
using namespace boost::signals2;

export{
	namespace Helium {
		thread dispatcher;

		vector<shared_ptr<_BasicHeliumEvent>> eventlist;

		int InitEventEnv();
		int CreateHeliumEvent(shared_ptr<_BasicHeliumEvent> eventins);
		int EventDispatcherThread();
	}
}

namespace Helium {
	int InitEventEnv() {
		log << LINFO << "Start initialize Helium event system." << hendl;
		thread tempthread(EventDispatcherThread);
		dispatcher = move(tempthread);
		log << LINFO << "Successfully initialized Helium event system." << hendl;
		return 0;
	}
	int CreateHeliumEvent(shared_ptr<_BasicHeliumEvent> eventins) {
		eventlist.push_back(eventins);
		return 0;
	}
	int EventDispatcherThread() {
		while (true) {
			if (!eventlist.empty()) {
				cout << "Get an event in eventlist!" << endl;
				auto tempevent = eventlist.front();
				tempevent->CallAllListenerFunc();
				eventlist.erase(eventlist.begin());
			}
		}
		return 0;
	}
}