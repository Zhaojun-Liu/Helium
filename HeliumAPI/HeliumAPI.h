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
#ifdef HELIUMAPI_EXPORTS
#define HELIUMAPI_API __declspec(dllexport)
#else
#define HELIUMAPI_API __declspec(dllimport)
#endif

// 此类是从 dll 导出的
class HELIUMAPI_API CHeliumAPI {
public:
	CHeliumAPI(void);
	// TODO: 在此处添加方法。
};

extern HELIUMAPI_API int nHeliumAPI;

HELIUMAPI_API int fnHeliumAPI(void);
