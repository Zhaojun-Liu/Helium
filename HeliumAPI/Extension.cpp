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

#include"Extension.h"
#include"pch.h"

namespace HeliumAPI {
	typedef int(*t1)(string);
	typedef string(*t2)(string);
	typedef int(*t3)(string);
	typedef int(*t4)();
	typedef vector<string>(*t5)(int);

	list<any> GetExtensionMetaData(string extname) {

	}
	string GetExtensionDirectory(string extname) {

	}
	string GetExtensionConfigDirectory(string extname) {

	}
	int GetExtensionStatus(string extname) {

	}
	int CreateExtension(string configpath) {

	}
	int LoadExtension(string extname) {

	}
	int UnloadExtension(string extname) {

	}
	int ReloadExtension(string extname) {

	}
	int LockExtension(string extname) {

	}
	int UnlockExtension(string extname) {

	}
	int InitializeAllExtension() {

	}
	int ReinitializeAllExtension() {

	}
	int LoadAllExtension() {

	}
	int UnloadAllExtension() {

	}
	int ReloadAllExtension() {

	}
	int LockAllExtension() {

	}
	int UnlockAllExtension() {

	}
	vector<string> GetExtensionList(int mask = -1) {

	}
}