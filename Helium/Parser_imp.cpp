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

#include<regex>

module Helium.Parser;

import Helium.MinecraftServer;
import Helium.Event;
import <string>;

namespace Helium {
	string VanillaParser::StopCommand() {
		return "stop";
	}
	string VanillaParser::MessageCommand() {
		string cmd;
		return cmd;
	}
	string VanillaParser::BroadcastCommand() {
		string cmd;
		return cmd;
	}
	string VanillaParser::Parse(string rawoutput) {

	}

	_BasicHeliumParser* GetParserByType(int type) {
		switch (type) {
		case HeliumServerType::VANILLA:
			return new VanillaParser;
		case HeliumServerType::FORGE:
			return new ForgeParser;
		case HeliumServerType::BUKKIT:
			return new BukkitParser;
		case HeliumServerType::BUKKIT14:
			return new Bukkit14Parser;
		case HeliumServerType::BUNGEECORD:
			return new BungeeCordParser;
		case HeliumServerType::WATERFALL:
			return new WaterfallParser;
		case HeliumServerType::CAT:
			return new CatParser;
		case HeliumServerType::BETA18:
			return new Beta18Parser;
		default:
			return new VanillaParser;
		}
	}
}