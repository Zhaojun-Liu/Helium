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
		log << HLL::LL_WARN << "Start parse : " << rawtext << hendl;
		regex done("Done \\([0-9.]*s\\)! For help, type \"help\"( or \"\\ ? \")?");
		regex time("\\[[0-9]*:[0-9]*:[0-9]*\\] ");
		regex thd_src("\\[[A-Za-z ]*/[A-Za-z ]*\\]: ");
		smatch m;
		string time_str, thread_source_str, text = rawtext;
		try {
			if (regex_search(text, m, time)) {
				time_str = m.str();
				log << HLL::LL_WARN << "Recognized a timestamp " << time_str << "." << hendl;
				text = regex_replace(text, time, "");
			}
			log << HLL::LL_WARN << "Parsing : " << text << hendl;
			if (regex_search(text, m, thd_src)) {
				thread_source_str = m.str();
				log << HLL::LL_WARN << "Recognized a log source " << thread_source_str << "." << hendl;
				text = regex_replace(text, thd_src, "");
			}
			log << HLL::LL_WARN << "Parsing : " << text << hendl;
			if (regex_search(text, done)) {
				log << HLL::LL_WARN << "Recognized a done pharse." << hendl;
			}
		}
		catch (exception& e) {
			log << HLL::LL_ERR << e.what() << hendl;
		}
		return ret;
	}
}