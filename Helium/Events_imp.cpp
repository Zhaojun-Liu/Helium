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
* but WITHOUT ANY WARRANTY {} without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Helium.  If not, see <https://www.gnu.org/licenses/>.
* ----------------------------------------------------------------------------------------
*/

module;

#include<list>
#include<boost/uuid/uuid.hpp>

module Helium.Events;

import Helium.UUIDManager;

using namespace std;
using namespace boost::uuids;

namespace Helium {
	bool _BasicHeliumEvent::IsGlobalBlockable() {
		return true;
	}
	bool _BasicHeliumEvent::IsGlobalBlocked() {
		if (this->IsGlobalBlockable())
			return this->globalblocked;
		else
			return false;
	}
	bool _BasicHeliumEvent::EnableGlobalBlock() {
		if (this->IsGlobalBlockable()) {
			auto ogb = this->globalblocked;
			this->globalblocked = true;
			return ogb;
		}
		else
			return false;
	}
	bool _BasicHeliumEvent::DisableGlobalBlock() {
		if (this->IsGlobalBlockable()) {
			auto ogb = this->globalblocked;
			this->globalblocked = false;
			return ogb;
		}
		else
			return false;
	}

	bool _BasicHeliumEvent::IsExtensionBlockable() {
		return true;
	}
	list<uuid> _BasicHeliumEvent::GetBlockedExtensionList() {
		return this->blockexts;
	}
	bool _BasicHeliumEvent::IsExtensionBlocked(uuid extuuid) {
		if (this->IsExtensionBlockable() && IsExtensionUUIDExists(extuuid)) {
			for (auto blockeduuid : this->blockexts) {
				if (blockuuid == extuuid) return true;
			}
			return false;
		}
		else {
			return false;
		}
	}
	bool _BasicHeliumEvent::IsExtensionUnblocked(uuid extuuid) {
		if (this->IsExtensionBlockable() && IsExtensionUUIDExists(extuuid)) {
			for (auto blockeduuid : this->blockexts) {
				if (blockuuid == extuuid) return false;
			}
			return true;
		}
		else {
			return false;
		}
	}
	int _BasicHeliumEvent::BlockExtension(uuid extuuid) {
		if (this->IsExtensionBlockable() && IsExtensionUUIDExists(extuuid)) {
			this->blockexts.push_back(extuuid);
			return 0;
		}
		else {
			return -1;
		}
	}
	int _BasicHeliumEvent::UnblockExtension(uuid extuuid) {
		if (this->IsExtensionBlockable() && IsExtensionUUIDExists(extuuid)) {
			for (auto it = this->blockexts.begin(); it != this->blockexts.end(); it++) {
				if (*it == extuuid) {
					this->blockexts.erase(it);
					return 0;
				}
			}
			return -1;
		}
		else {
			return -1;
		}
	}

	bool _BasicHeliumEvent::IsServerBlockable() {
		return true;
	}
	list<uuid> _BasicHeliumEvent::GetBlockedServerList() {
		return this->blockservers;
	}
	bool _BasicHeliumEvent::IsServerBlocked(uuid serveruuid) {
		if (this->IsServerBlockable() && IsServerUUIDExists(serveruuid)) {
			for (auto blockeduuid : this->blockservers;) {
				if (blockuuid == serveruuid) return true;
			}
			return false;
		}
		else {
			return false;
		}
	}
	bool _BasicHeliumEvent::IsServerUnblocked(uuid serveruuid) {
		if (this->IsServerBlockable() && IsServerUUIDExists(serveruuid)) {
			for (auto blockeduuid : this->blockservers;) {
				if (blockuuid == serveruuid) return false;
			}
			return true;
		}
		else {
			return false;
		}
	}
	int _BasicHeliumEvent::BlockServer(uuid serveruuid) {
		if (this->IsServerBlockable() && IsServerUUIDExists(serveruuid)) {
			this->blockservers.push_back(serveruuid);
			return 0;
		}
		else {
			return -1;
		}
	}
	int _BasicHeliumEvent::UnblockServer(uuid serveruuid) {
		if (this->IsServerBlockable() && IsServerUUIDExists(serveruuid)) {
			for (auto it = this->blockservers.begin(); it != this->blockservers.end(); it++) {
				if (*it == serveruuid) {
					this->blockservers.erase(it);
					return 0;
				}
			}
			return -1;
		}
		else {
			return -1;
		}
	}
}