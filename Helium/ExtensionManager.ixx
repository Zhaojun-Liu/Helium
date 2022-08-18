/*
* Helium is a customizable extension system for Minecraft server.
* You can get the lastest source code and releases of Helium at :
* https://github.com/Helium-DevTeam/Helium
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

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "cpp-httplib/httplib.h"

export module Helium.ExtensionManager;

import <iostream>;
import <cstdlib>;
import <string>;

using namespace std;

export {
	namespace Helium {
		int test() {
			httplib::Client cli("https://raw.githubusercontent.com");
			if (auto res = cli.Get("/Helium-DevTeam/Helium-Extensions-Main/main/main/TestExtension/0.0.1/TestExtension.json")) {
				if (res->status == 200) {
					std::cout << res->body << std::endl;
				}
				cout << res->status << endl;
			}
			else {
				auto err = res.error();
				std::cout << "HTTP error: " << httplib::to_string(err) << std::endl;
			}
			return 0;
		}
	}
}

namespace Helium {
}