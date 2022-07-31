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

export module Helium.Parser;

import Helium.Events;
import Helium.Logger;

import <string>;
import <list>;
import <any>;
import <regex>;

using namespace std;

export{
	namespace Helium {
		class BasicHeliumParser {

		};
		class VanillaParser : public BasicHeliumParser{
		public:
			VanillaParser() : server_name("empty_server_name") {}
			VanillaParser(string server_name) : server_name(server_name) {}
			int Parse(const string& rawtext);
		private:
			string server_name;
		};
	}
}

namespace Helium {
	int VanillaParser::Parse(const string& rawtext) {
		auto ret = 0;
		list<any> param;
		any temp_any = 0;
		log << HLL::LL_INFO << "Start parse : " << rawtext << hendl;
		regex done("Done \\([0-9.]*s\\)! For help, type \"help\"( or \"\\ ? \")?");
		if (regex_search(rawtext, done)) {
			log << HLL::LL_WARN << "Recognized a done pharse." << hendl;
		}
		return ret;
	}
}