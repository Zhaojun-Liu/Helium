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

module Helium.MinecraftServer:API;

import :Class;
import <string>;

using namespace std;
using namespace boost::uuids;

namespace Helium {
	void AddServer(HeliumMinecraftServer server) {
		
	}
	int StartServer(string name) {
	
	}
	int StartServer(uuid server) {
		
	}
	int StartServer() {
	
	}
	int StartAllServer() {
	
	}

	int AutoStartServer(string name) {
	
	}
	int AutoStartServer(uuid server) {
	
	}
	int AutoStartServer() {
	
	}
	int AutoStartAllServer() {
	
	}

	int StopServer(string name) {
	
	}
	int StopServer(uuid server) {
	
	}
	int StopServer() {
	
	}
	int StopAllServer() {
	
	}

	int PauseServer(string name) {
	
	}
	int PauseServer(uuid server) {
	
	}
	int PauseServer() {
	
	}
	int PauseAllServer() {
	
	}

	int ResumeServer(string name) {
	
	}
	int ResumeServer(uuid server) {
	
	}
	int ResumeServer() {
	
	}
	int ResumeAllServer() {
	
	}

	int DeleteServer(string name) {
	
	}
	int DeleteServer(uuid server) {
	
	}
	int DeleteSerevr(int stat) {
	
	}
	void ClearServerList() {
	
	}

	auto QueryServer(string servername) {
	
	}
	auto QueryServer(uuid server) {
	
	}
}