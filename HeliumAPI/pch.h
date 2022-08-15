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

#ifndef PCH_H
#define PCH_H

#ifdef HELIUMAPI_EXPORTS
#define HELIUMAPI_API extern "C" _declspec(dllexport)
#else
#define HELIUMAPI_API extern "C" _declspec(dllimport)
#endif

#include"framework.h"
#include"semver/semver.hpp"
#include"_TransferFuncMap.h"

#include<any>
#include<map>
#include<strstream>
#include<string>
#include<iostream>

#include<boost/uuid/uuid.hpp>
#include<boost/uuid/uuid_generators.hpp>
#include<boost/dll.hpp>
#include<boost/function.hpp>
#include<boost/signals2.hpp>

constexpr semver::version apiver = semver::version{ 0, 0, 5, semver::prerelease::alpha };

#endif
