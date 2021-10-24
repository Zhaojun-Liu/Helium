#pragma once

#ifndef _H_PERMISSIONS
#define _H_PERMISSIONS
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include<vector>
#include<guiddef.h>
#include<string>
#include<spdlog/spdlog.h>

#include"tinyxml2.h"
#include"minecraftserver.h"
namespace Helium {

	using namespace std;

#define PERMISSION_FILENAME "permission.xml"

#define PERMISSION_LEVEL_GUEST			0
#define PERMISSION_LEVEL_USER			1
#define PERMISSION_LEVEL_ADMIN			2
#define PERMISSION_LEVEL_SERVEROWNER	3
#define PERMISSION_LEVEL_HELIUMOWNER	4

	extern const char* permdescstr[];

	int _stdcall ReadPermissionFile();
	int _stdcall CreatePermissionFile();
	int _stdcall SavePermissionFile();

	struct PermissionNamespace {
		GUID serverguid;
		int defaultpermission;
		vector<pair<string, int>> permissions;
	};

	extern vector<PermissionNamespace> permissions;

}
#endif // !_H_PERMISSIONS
