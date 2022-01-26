#include"heliumconfig.h"

namespace Helium {
	HeliumLogger cfgl("HeliumConfigReader");

	int HeliumConfig() {

	}

	int ReadHeliumConfig() {
		XMLDocument* cfg;
		XMLElement* root;
		HeliumEndline hendl;

		if (auto ret = cfg->LoadFile(CFG_FILENAME); ret != XMLError::XML_SUCCESS) {	//Load config file
			cfgl << "Failed to load helium config file : " << ret << "(" << cfg->ErrorIDToName(ret) << ")" << hendl;
			cfgl << cfg->ErrorStr() << hendl;
			return ret;
		}

		if (root = cfg->FirstChildElement("HeliumConfig"); root == NULL) {	//Get root element
			cfgl << "Failed to get the root element of helium config file : " << cfg->ErrorID() << "(" << cfg->ErrorName() << ")" << hendl;
			cfgl << cfg->ErrorStr() << hendl;
			return cfg->ErrorID();
		}


	}
	int SaveHeliumConfig() {

	}
	int CreateHeliumConfig() {

	}
}