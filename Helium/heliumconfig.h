#pragma once

#ifndef _H_HELIUMCONFIG
#define _H_HELIUMCONFIG

#define CFG_FILENAME "HeliumConfig.xml"

#include<string>
#include<vector>
#include<strstream>

#include"tinyxml2/tinyxml2.h"
#include"boost/uuid/uuid.hpp"

#include"logger.h"
#include"xmlutils.h"
#include"minecraftserver.h"
#include"utils.h"

namespace Helium {
	using namespace tinyxml2;
	using namespace boost::uuids;
	using namespace std;

#define en_US 0
#define zh_CN 1

#define PERMISSION_LEVEL_GUEST			0
#define PERMISSION_LEVEL_USER			1
#define PERMISSION_LEVEL_ADMIN			2
#define PERMISSION_LEVEL_SERVEROWNER	3
#define PERMISSION_LEVEL_HELIUMOWNER	4

	struct HeliumSetting {
		int Language;
		string Encoding;
		string ExtDir;
		string ScrDir;
		bool rconEnable;
		int rconPort;
		string rconPassword;
		bool AutoUpdate;
	};

	struct PermissionNamespace {
		string servername;
		uuid serveruuid;
		int defaultpermission;
		vector<pair<string, int>> permissions;
	};

	int ReadHeliumConfig();
	int CreateHeliumConfig();
}

#endif // !_H_HELIUMCONFIG
