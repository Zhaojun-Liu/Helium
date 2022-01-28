module;

export module Helium.Config;

#define CFG_FILENAME "HeliumConfig.xml"

import <string>;
import <vector>;
import <strstream>;

import "tinyxml2/tinyxml2.h";
import "boost/uuid/uuid.hpp";

import "logger.h";
import "xmlutils.h";
import "minecraftserver.h";
import "utils.h";

using namespace std;
using namespace tinyxml2;
using namespace boost::uuids;

export{
	namespace Helium {
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
}