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

export module Helium.Parser;

import Helium.MinecraftServer;
import Helium.Events;

import <string>;

using namespace std;

export{
	namespace Helium {
		class _BasicHeliumParser {
		public:
			_BasicHeliumParser() {

			}
			virtual ~_BasicHeliumParser() {

			}

			virtual string StopCommand() = 0;
			virtual string MessageCommand() = 0;
			virtual string BroadcastCommand() = 0;
			virtual int Parse(string rawoutput) = 0;
		};

		class VanillaParser : public _BasicHeliumParser {
		public:
			virtual string StopCommand();
			virtual string MessageCommand();
			virtual string BroadcastCommand();
			virtual int Parse(string rawoutput);
		};

		class ForgeParser : public _BasicHeliumParser {
		public:
		};

		class BukkitParser : public _BasicHeliumParser {
		public:
		};

		class Bukkit14Parser : public _BasicHeliumParser {
		public:
		};

		class BungeeCordParser : public _BasicHeliumParser {
		public:
		};

		class WaterfallParser : public _BasicHeliumParser {
		public:
		};

		class CatParser : public _BasicHeliumParser {
		public:
		};

		class Beta18Parser : public _BasicHeliumParser {
		public:
		};

		_BasicHeliumParser* GetParserByType(int type);

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
		int VanillaParser::Parse(string rawoutput) {
			return 0;
		}

		_BasicHeliumParser* GetParserByType(int type) {
			switch (type) {
			case HeliumServerType::VANILLA:
				return new VanillaParser;
			case HeliumServerType::FORGE:
				return new VanillaParser;
			case HeliumServerType::BUKKIT:
				return new VanillaParser;
			case HeliumServerType::BUKKIT14:
				return new VanillaParser;
			case HeliumServerType::BUNGEECORD:
				return new VanillaParser;
			case HeliumServerType::WATERFALL:
				return new VanillaParser;
			case HeliumServerType::CAT:
				return new VanillaParser;
			case HeliumServerType::BETA18:
				return new VanillaParser;
			default:
				return new VanillaParser;
			}
		}
	}
}