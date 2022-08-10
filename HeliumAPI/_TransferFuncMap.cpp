/*
* Helium API is dll for remapping Helium API functions.
* You can get the lastest source code and releases of Helium API at :
* https://github.com/Helium-DevTeam/Helium
* ----------------------------------------------------------------------------------------
* Helium Copyright (C) 2021-2022 HeliumDevTeam
*
* This file is a part of Helium API
*
* Helium API is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Helium API is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Helium API.  If not, see <https://www.gnu.org/licenses/>.
* ----------------------------------------------------------------------------------------
*/

#include"_TransferFuncMap.h"
#include"pch.h"

namespace HeliumAPI {
	map<string, void*> HeliumAPIMap;
	string lname = "HeliumAPI";

	typedef int (*createptr)(string);
	typedef int (*deleteptr)(string);
	typedef int (*loggingptr)(string, string);

	HELIUMAPI_API int TransferFuncMap(map<string, void*> funcmap) {
		HeliumAPIMap = funcmap;
		auto crt_ptr = (createptr)HeliumAPIMap.at("CreateExtLogger");
		crt_ptr("HeliumAPI");
		auto ptr = (loggingptr)HeliumAPIMap.at("ExtLoggerInfo");
		string temp_str("Helium API ");
		temp_str.append(to_string(apiver));
		ptr("HeliumAPI", temp_str);
		ptr("HeliumAPI", "Copyright(C) 2021-2022 HeliumDevTeam");
		ptr("HeliumAPI", "This program comes with ABSOLUTELY NO WARRANTY;");
		ptr("HeliumAPI", "for details type \'#Helium show warranty\'.");
		ptr("HeliumAPI", "This is free software, and you are welcome to redistribute it");
		ptr("HeliumAPI", "under certain conditions; type \'#Helium show conditions\' for details.");
		temp_str.clear();
		temp_str.append("Transferred ").append(to_string(HeliumAPIMap.size())).append(" functions.");
		ptr("HeliumAPI", temp_str);
		return 0;
	}
}