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

export module Helium.Events;

import Helium.Extension;
import Helium.UUIDManager;
import Helium.Extension;

import <vector>;
import <list>;

using namespace std;
using namespace boost::uuids;

export{
	namespace Helium {
		class _BasicHeliumEvent {
			virtual int AddListenerFunc(void* func);
			virtual int CallAllListenerFunc();
		protected:
			list<void*> listenerfunc;
		};

		class _HeliumEventInput : public _BasicHeliumEvent{

		};
		class _HeliumSelfEvent : public _BasicHeliumEvent{

		};
		class _HeliumServerEvent : public _BasicHeliumEvent {

		};
		class _HeliumExtensionEvent : public _BasicHeliumEvent {

		};
		class _HeliumEventTransmission : public _BasicHeliumEvent {

		};

		vector<_BasicHeliumEvent> eventlist;

		int InitEventEnv();
		int CreateEvent();
		int EventDispatcherThread();
	}
}

namespace Helium {
	int _BasicHeliumEvent::AddListenerFunc(void* func) {
		this->listenerfunc.push_back(func);
		return 0;
	}
	int _BasicHeliumEvent::CallAllListenerFunc() {
		int count = 0;
		for (auto ptr : this->listenerfunc) {
			int i = ptr();
			count++;
			if (i == -1) break;
		}
		return count;
	}

	int InitEventEnv();
	int CreateEvent();
	int EventDispatcherThread();
}