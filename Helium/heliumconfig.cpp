#include"heliumconfig.h"

namespace Helium {
	HeliumLogger cfgl("HeliumConfigReader");
	HeliumSetting Settings;
	PermissionNamespace Permissions;

	int HeliumConfig() {

	}

	int ReadHeliumConfig() {
		XMLDocument* cfg;
		XMLElement* root;
		XMLElement* set;
		XMLElement* perm;
		XMLElement* server;
		XMLElement* rcon;
		HeliumEndline hendl;
		strstream sstr;
		string tempstr;
		int tempi;

		if (auto ret = cfg->LoadFile(CFG_FILENAME); ret != XMLError::XML_SUCCESS) {	//Load config file
			cfgl << HLL::LL_ERR << "Failed to load helium config file : " << ret << "(" << cfg->ErrorIDToName(ret) << ")" << hendl;
			cfgl << cfg->ErrorStr() << hendl;
			return ret;
		}

		if (root = cfg->FirstChildElement("HeliumConfig"); root == NULL) {	//Get root element
			cfgl << HLL::LL_ERR << "Failed to get the root element of helium config file : " << cfg->ErrorID() << "(" << cfg->ErrorName() << ")" << hendl;
			cfgl << cfg->ErrorStr() << hendl;
			return cfg->ErrorID();
		}

		if (set = root->FirstChildElement("Settings"); set == NULL) {	//Get "Settings" element
			cfgl << HLL::LL_ERR << "Failed to get the settings element of helium config file : " << cfg->ErrorID() << "(" << cfg->ErrorName() << ")" << hendl;
			cfgl << cfg->ErrorStr() << hendl;
			return cfg->ErrorID();
		}

		if (perm = root->FirstChildElement("Permissions"); perm == NULL) {	//Get "Permissions" element
			cfgl << HLL::LL_ERR << "Failed to get the permissions element of helium config file : " << cfg->ErrorID() << "(" << cfg->ErrorName() << ")" << hendl;
			cfgl << cfg->ErrorStr() << hendl;
			return cfg->ErrorID();
		}

		if (server = root->FirstChildElement("Servers"); server == NULL) {	//Get "Servers" element
			cfgl << HLL::LL_ERR << "Failed to get the servers element of helium config file : " << cfg->ErrorID() << "(" << cfg->ErrorName() << ")" << hendl;
			cfgl << cfg->ErrorStr() << hendl;
			return cfg->ErrorID();
		}

		if (rcon = set->FirstChildElement("rcon"); rcon == NULL) {
			cfgl << HLL::LL_ERR << "Failed to get the rcon element of helium config file : " << cfg->ErrorID() << "(" << cfg->ErrorName() << ")" << hendl;
			cfgl << cfg->ErrorStr() << hendl;
			return cfg->ErrorID();
		}

		tempstr = GetNodeStringByName(set, "Language");
		if (tempstr == "en-US")
			Settings.Language = en_US;
		else if (tempstr == "zh-CN")
			Settings.Language = zh_CN;
		else
			Settings.Language = en_US;

		tempstr = GetNodeStringByName(set, "Encoding");
		Settings.Encoding = tempstr;

		tempstr = GetNodeStringByName(set, "ExtensionDirectory");
		if (!tempstr.empty()) Settings.ExtDir = tempstr;
		else Settings.ExtDir = "extensions";
		
		tempstr = GetNodeStringByName(set, "ScriptDirectory");
		if (!tempstr.empty())Settings.ScrDir = tempstr;
		else Settings.ScrDir = "scripts";

		tempstr = GetNodeStringByName(rcon, "Enable");
		if (tempstr == "true") Settings.rconEnable = true;
		else Settings.rconEnable = false;

		if (Settings.rconEnable) {
			tempstr = GetNodeStringByName(rcon, "Port");
			sstr << tempstr;
			sstr >> tempi;
			sstr.clear();
			Settings.rconPort = tempi;

			tempstr = GetNodeStringByName(rcon, "Password");
			Settings.rconPassword = tempstr;
		}

		tempstr = GetNodeStringByName(set, "AutoUpdate");
		if (tempstr == "true") Settings.AutoUpdate = true;
		else Settings.AutoUpdate = false;
		
		return XMLError::XML_SUCCESS;
	}
	int SaveHeliumConfig() {

	}
	int CreateHeliumConfig() {

	}
}