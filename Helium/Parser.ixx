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

#include<ctime>

export module Helium.Parser;

import Helium.Events;
import Helium.Logger;

import <string>;
import <sstream>;
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
			VanillaParser(const string& server_name) : server_name(server_name) {}
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
		regex rdone("Done \\([0-9.]*s\\)! For help, type \"help\"( or \"\\ ? \")?");
		regex rtime("\\[[0-9][0-9]:[0-9][0-9]:[0-9][0-9]\\] ");
		regex rthd_src("\\[[A-Za-z ]*/[A-Za-z ]*\\]: ");
		regex rjoin("[A-Za-z0-9_]* joined the game");
		regex rleave("[A-Za-z0-9_]* left the game");
		regex rplayer_info("<[A-Za-z0-9_]*> ");
		smatch m;
		string time_str, thread_source_str, text = rawtext, thrd, srce;
		tm timestamp;

		temp_any = this->server_name;
		param.push_back(temp_any);

		try {
			if (regex_search(text, m, rtime)) {
				time_str = m.str();
				text = regex_replace(text, rtime, "");
				regex rsplit_time("[0-9][0-9]");
				smatch temp_m;
				sregex_iterator it(time_str.begin(), time_str.end(), rsplit_time), end;
				int tempi = 1;
				for (; it != end; it++) {
					stringstream sstr;
					int tempint;
					sstr << it->str();
					sstr >> tempint;
					sstr.clear();
					if (tempi == 1)
						timestamp.tm_hour = tempint;
					if (tempi == 2)
						timestamp.tm_min = tempint;
					if (tempi == 3)
						timestamp.tm_sec = tempint;
					tempi++;
				}
				temp_any = timestamp;
				param.push_back(temp_any);
			}
			if (regex_search(text, m, rthd_src)) {
				thread_source_str = m.str();
				text = regex_replace(text, rthd_src, "");
				regex rthread("[A-Za-z ]*/"), rsource("/[A-Za-z ]*");
				smatch temp_m;
				regex_search(thread_source_str, temp_m, rthread);
				thrd = temp_m.str();
				thrd.erase(thrd.end() - 1);
				temp_any = thrd;
				param.push_back(temp_any);
				regex_search(thread_source_str, temp_m, rsource);
				srce = temp_m.str();
				srce.erase(srce.begin());
				temp_any = srce;
				param.push_back(temp_any);
			}
			if (regex_search(text, rjoin)) {
				regex rsplit(" joined the game");
				text = regex_replace(text, rsplit, "");
				temp_any = text;
				param.push_back(temp_any);
				helium_event_manager.DispatchEvent(HeliumEventList::PLAYER_JOIN, param);
			}
			if (regex_search(text, rleave)) {
				regex rsplit(" left the game");
				text = regex_replace(text, rsplit, "");
				temp_any = text;
				param.push_back(temp_any);
				helium_event_manager.DispatchEvent(HeliumEventList::PLAYER_LEAVE, param);
			}
			if (regex_search(text, m, rplayer_info)) {
				string player_name = m.str();
				player_name.erase(player_name.begin());
				player_name.erase(player_name.end() - 1);
				player_name.erase(player_name.end() - 1);
				text = regex_replace(text, rplayer_info, "");
				string player_info = text;
				temp_any = player_name;
				param.push_back(temp_any);
				temp_any = player_info;
				param.push_back(temp_any);
				helium_event_manager.DispatchEvent(HeliumEventList::PLAYER_INPUT, param);
			}
			if (regex_search(text, rdone)) {
				regex rsplit_usetime("[0-9]*.[0-9]*s");
				smatch temp_m;
				regex_search(text, temp_m, rsplit_usetime);
				string temp_str = temp_m.str();
				temp_str.erase(temp_str.end() - 1);
				stringstream sstr;
				double temp_d;
				sstr << temp_str;
				sstr >> temp_d;
				temp_any = temp_d;
				param.push_back(temp_any);
				helium_event_manager.DispatchEvent(HeliumEventList::SERVER_INITIALIZATION_FINISH, param);
			}
		}
		catch (exception& e) {
			log << HLL::LL_ERR << e.what() << hendl;
		}
		return ret;
	}
}