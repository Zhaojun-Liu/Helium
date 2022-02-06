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
#include<list>

export module Helium.Events;

import Helium.Extension;

using namespace std;
using namespace boost::uuids;

export{
	namespace Helium {
		enum HeliumEvents {
			UndefinedEvent,
			ExtensionLoaded,
			ExtensionUnloaded,
			ServerOutput,
			UserOutput,
			ServerStart,
			ServerInited,
			ServerPause,
			ServerResume,
			ServerStop,
			HeliumStart,
			HeliumStop,
			PlayerJoined,
			PlayerLeft
		};

		class _BasicHeliumEvent {
		public:
			_BasicHeliumEvent();
			virtual ~_BasicHeliumEvent();
			virtual HeliumEvents GetEventType() = 0;

			virtual bool IsGlobalBlockable();
			virtual bool IsGlobalBlocked();
			virtual bool EnableGlobalBlock();
			virtual bool DisableGlobalBlock();

			virtual bool IsExtensionBlockable();
			virtual list<uuid> GetBlockedExtensionList();
			virtual bool IsExtensionBlocked(uuid extuuid);
			virtual bool IsExtensionUnblocked(uuid extuuid);
			virtual int BlockExtension(uuid extuuid);
			virtual int UnblockExtension(uuid extuuid);

			virtual bool IsServerBlockable();
			virtual list<uuid> GetBlockedServerList();
			virtual bool IsServerBlocked(uuid serveruuid);
			virtual bool IsServerUnblocked(uuid serveruuid);
			virtual int BlockServer(uuid serveruuid);
			virtual int UnblockServer(uuid serveruuid);
		protected:
			bool globalblock;
			list<uuid> blockexts;
			list<uuid> blockservers;
		};

		class UndefinedEvent : public _BasicHeliumEvent {
		public:
			virtual HeliumEvents GetEventType() { return HeliumEvents::UndefinedEvent; }
		};

		class _ExtensionEvent : public _BasicHeliumEvent {
		public:
			virtual HeliumEvents GetEventType() = 0;
		};
		class _ServerEvent : public _BasicHeliumEvent {
		public:
			virtual HeliumEvents GetEventType() = 0;
		};
		class _HeliumEvent : public _BasicHeliumEvent {
		public:
			virtual HeliumEvents GetEventType() = 0;
		};

		class ExtensionLoaded : public _ExtensionEvent {
		public:
			virtual HeliumEvents GetEventType() { return HeliumEvents::ExtensionLoaded; }
		};
		class ExtensionUnloaded : public _ExtensionEvent {
		public:
			virtual HeliumEvents GetEventType() { return HeliumEvents::ExtensionUnloaded; }
		};

		class ServerOutput : public _ServerEvent {
		public:
			virtual HeliumEvents GetEventType() { return HeliumEvents::ServerOutput; }
		};
		class UserOutput : public _ServerEvent {
		public:
			virtual HeliumEvents GetEventType() { return HeliumEvents::UserOutput; }
		};
		class ServerStart : public _ServerEvent {
		public:
			virtual HeliumEvents GetEventType() { return HeliumEvents::ServerStart; }
		};
		class ServerInited : public _ServerEvent {
		public:
			virtual HeliumEvents GetEventType() { return HeliumEvents::ServerInited; }
		};
		class ServerPause : public _ServerEvent {
		public:
			virtual HeliumEvents GetEventType() { return HeliumEvents::ServerPause; }
		};
		class ServerResume : public _ServerEvent {
		public:
			virtual HeliumEvents GetEventType() { return HeliumEvents::ServerResume; }
		};
		class ServerStop : public _ServerEvent {
		public:
			virtual HeliumEvents GetEventType() { return HeliumEvents::ServerStop; }
		};
		class PlayerJoined : public _ServerEvent {
		public:
			virtual HeliumEvents GetEventType() { return HeliumEvents::PlayerJoined; }
		};
		class PlayerLeft : public _ServerEvent {
		public:
			virtual HeliumEvents GetEventType() { return HeliumEvents::PlayerLeft; }
		};

		class HeliumStart : public _HeliumEvent {
		public:
			virtual HeliumEvents GetEventType() { return HeliumEvents::HeliumStart; }
		};
		class HeliumStop : public _HeliumEvent {
		public:
			virtual HeliumEvents GetEventType() { return HeliumEvents::HeliumStop; }
		};
	}
}