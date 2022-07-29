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

		typedef int(*funcptr)();

		class _BasicHeliumEvent {
		public:
			_BasicHeliumEvent() {

			}

			virtual ~_BasicHeliumEvent() {

			}

			virtual int AddListenerFunc(void* func) {
				return 0;
			}
			virtual int DeleteListenerFunc(void* func) {
				return 0;
			}
			virtual int CallAllListenerFunc() {
				log << LWARN << "Enter CallAllListenerFunc()!" << hendl;
				return 0;
			}
			virtual void BlockEvent() {
				this->isblocked = true;
			}
			virtual void UnblockEvent() {
				this->isblocked = false;
			}
			virtual bool IsEventBlocked() {
				return this->isblocked;
			}
		protected:
			bool isblocked;
		};

		class HeliumEventExtensionLoaded : public _BasicHeliumEvent {
		public:
			HeliumEventExtensionLoaded() {
				this->innersigptr = make_shared<signal<int()>>();
			}
			virtual ~HeliumEventExtensionLoaded() {
				this->innersigptr->disconnect_all_slots();
			}

			virtual int AddListenerFunc(void* func) {
				funcptr ptr = (funcptr)func;
				this->innersigptr->connect(ptr);
				return 0;
			};
			virtual int DeleteListenerFunc(void* func) {
				funcptr ptr = (funcptr)func;
				this->innersigptr->disconnect(ptr);
				return 0;
			};
			virtual int CallAllListenerFunc() {
				log << LWARN << "Enter CallAllListenerFunc()!" << hendl;
				if (!this->isblocked) {
					auto tempptr = this->innersigptr;
					log << LWARN << (int)tempptr->num_slots() << hendl;
					(*tempptr)();
				}
				return 0;
			};
			
		protected:
			shared_ptr<signal<int()>> innersigptr;
		};
		class HeliumEventExtensionUnloaded : public _BasicHeliumEvent {
		public:
			virtual ~HeliumEventExtensionUnloaded() {
				//this->innersignal.disconnect_all_slots();
			}

			virtual int AddListenerFunc(void* func) {
				funcptr ptr = (funcptr)func;
				//innersignal.connect(ptr);
				return 0;
			};
			virtual int DeleteListenerFunc(void* func) {
				funcptr ptr = (funcptr)func;
				//innersignal.disconnect(ptr);
				return 0;
			};
			virtual int CallAllListenerFunc() {
				if (!this->isblocked)
					//this->innersignal();
				return 0;
			};

		protected:

		};

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