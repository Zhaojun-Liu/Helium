/*
* Helium is a customizable extension system for Minecraft server.
* You can get the lastest source code and releases of Helium at :
* https://github.com/Minecraft1248/Helium
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

#include<strstream>
#include<boost/uuid/uuid.hpp>

#include"tinyxml2/tinyxml2.h"


#define CFG_FILENAME "HeliumConfig.xml"
#define en_US 0
#define zh_CN 1
#define PERMISSION_LEVEL_GUEST 0
#define PERMISSION_LEVEL_USER 1
#define PERMISSION_LEVEL_ADMIN 2
#define PERMISSION_LEVEL_SERVEROWNER 3
#define PERMISSION_LEVEL_HELIUMOWNER 4

module Helium.Config;

using namespace tinyxml2;
using namespace std;
using namespace boost::uuids;

import Helium.Logger;
import Helium.XMLUtils;
import Helium.Utils;
import Helium.MinecraftServer;

HeliumSetting Settings;
vector<PermissionNamespace> Permissions;
const char* permdescstr[] = { "Guest", "User", "Admin", "ServerOwner", "HeliumOwner" };

namespace Helium {
	HeliumLogger cfgl("HeliumConfigReader");
	vector<HeliumMinecraftServer> heliumservers;

	int ReadHeliumConfig() {
		XMLDocument cfg;
		XMLElement* root;
		XMLElement* set;
		XMLElement* perm;
		XMLElement* server;
		XMLElement* servernode;
		XMLElement* permns;
		HeliumEndline hendl;
		strstream sstr;
		string tempstr;
		int tempi;

		cfgl << HLL::LL_INFO << "Reading Helium config file." << hendl;

		if (auto ret = cfg.LoadFile(CFG_FILENAME); ret != XMLError::XML_SUCCESS) {	//Load config file
			cfgl << HLL::LL_ERR << "Failed to load helium config file : " << ret << "(" << cfg.ErrorIDToName(ret) << ")" << hendl;
			cfgl << cfg.ErrorStr() << hendl;
			return ret;
		}

		if (root = cfg.FirstChildElement("HeliumConfig"); root == NULL) {	//Get root element
			cfgl << HLL::LL_ERR << "Failed to get the root element of helium config file : " << cfg.ErrorID() << "(" << cfg.ErrorName() << ")" << hendl;
			cfgl << cfg.ErrorStr() << hendl;
			return cfg.ErrorID();
		}

		if (set = root->FirstChildElement("Settings"); set == NULL) {	//Get "Settings" element
			cfgl << HLL::LL_ERR << "Failed to get the settings element of helium config file : " << cfg.ErrorID() << "(" << cfg.ErrorName() << ")" << hendl;
			cfgl << cfg.ErrorStr() << hendl;
			return cfg.ErrorID();
		}

		if (perm = root->FirstChildElement("Permissions"); perm == NULL) {	//Get "Permissions" element
			cfgl << HLL::LL_ERR << "Failed to get the permissions element of helium config file : " << cfg.ErrorID() << "(" << cfg.ErrorName() << ")" << hendl;
			cfgl << cfg.ErrorStr() << hendl;
			return cfg.ErrorID();
		}

		if (server = root->FirstChildElement("Servers"); server == NULL) {	//Get "Servers" element
			cfgl << HLL::LL_ERR << "Failed to get the servers element of helium config file : " << cfg.ErrorID() << "(" << cfg.ErrorName() << ")" << hendl;
			cfgl << cfg.ErrorStr() << hendl;
			return cfg.ErrorID();
		}

		if (servernode = server->FirstChildElement("MinecraftServer"); servernode == NULL) {
			cfgl << HLL::LL_ERR << "Failed to get the MinecraftServer element of helium config file : " << cfg.ErrorID() << "(" << cfg.ErrorName() << ")" << hendl;
			cfgl << cfg.ErrorStr() << hendl;
			return cfg.ErrorID();
		}

		if (permns = perm->FirstChildElement("PermissionNamespace"); permns == NULL) {
			cfgl << HLL::LL_ERR << "Failed to get the PermissionNamespace element of helium config file : " << cfg.ErrorID() << "(" << cfg.ErrorName() << ")" << hendl;
			cfgl << cfg.ErrorStr() << hendl;
			return cfg.ErrorID();
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

		tempstr = GetNodeStringByName(set, "AutoUpdate");
		if (tempstr == "true") Settings.AutoUpdate = true;
		else Settings.AutoUpdate = false;

		while (servernode) {
			HeliumMinecraftServer tempins;
			XMLElement* servernodechild;
			XMLElement* rcon;

			servernodechild = servernode->FirstChildElement("ServerName");
			if (servernodechild)
				if (servernodechild->GetText()) {
					tempins.SetServerName(servernodechild->GetText());
				}

			servernodechild = servernode->FirstChildElement("ServerDirectory");
			if (servernodechild)
				if (servernodechild->GetText()) {
					tempins.SetServerDirectory(servernodechild->GetText());
				}

			servernodechild = servernode->FirstChildElement("StartCommand");
			if (servernodechild)
				if (servernodechild->GetText()) {
					tempins.SetServerStartCommand(servernodechild->GetText());
				}

			servernodechild = servernode->FirstChildElement("ServerType");
			if (servernodechild)
				if (servernodechild->GetText()) {
					tempins.SetServerType(ServerTypeStrToID(servernodechild->GetText()));
				}

			servernodechild = servernode->FirstChildElement("AutoStart");
			if (servernodechild)
				if (servernodechild->GetText()) {
					if ((string)servernodechild->GetText() == "true")
						tempins.EnableAutoStart();
					else
						tempins.DisableAutoStart();
				}

			servernodechild = servernode->FirstChildElement("OutputVisible");
			if (servernodechild)
				if (servernodechild->GetText()) {
					if ((string)servernodechild->GetText() == "true")
						tempins.EnableOutputVisibility();
					else
						tempins.DisableOutputVisibility();
				}

			rcon = servernode->FirstChildElement("rcon");
			if (rcon) {
				tempstr = GetNodeStringByName(rcon, "Enable");
				if (tempstr == "true") tempins.EnableRCON();
				else tempins.DisableRCON();

				if (Settings.rconEnable) {
					tempstr = GetNodeStringByName(rcon, "Port");
					sstr << tempstr;
					sstr >> tempi;
					sstr.clear();
					tempins.SetRCONPort(tempi);

					tempstr = GetNodeStringByName(rcon, "Password");
					tempins.SetRCONPassword(tempstr);
				}
			}

			tempins.GenServerUUID();

			AddServer(tempins);
			servernode = servernode->NextSiblingElement("MinecraftServer");
		}

		while (true) {
			PermissionNamespace tempns;
			string tempstr;

			tinyxml2::XMLAttribute* attr = const_cast<tinyxml2::XMLAttribute*>(permns->FindAttribute("server"));
			if (attr->Value()) {
				string tempstr = attr->Value();
				for (auto& server : heliumservers) {
					if (server.GetServerName() == tempstr) {
						uuid suuid;
						suuid = server.GetServerUUID();
						tempns.serveruuid = suuid;
					}
				}
			}
			else {
				cfgl << HLL::LL_ERR << "Failed to read the \"server\" attribute of permission namespace." << hendl;
				cfgl << cfg.ErrorStr() << hendl;
				return cfg.ErrorID();
			}

			attr = const_cast<tinyxml2::XMLAttribute*>(permns->FindAttribute("default"));
			if (attr->Value()) {
				tempns.defaultpermission = PERMISSION_LEVEL_GUEST;
				string tempstr = attr->Value();
				if (tempstr == permdescstr[PERMISSION_LEVEL_GUEST]) tempns.defaultpermission = PERMISSION_LEVEL_GUEST;
				if (tempstr == permdescstr[PERMISSION_LEVEL_USER]) tempns.defaultpermission = PERMISSION_LEVEL_USER;
				if (tempstr == permdescstr[PERMISSION_LEVEL_ADMIN]) tempns.defaultpermission = PERMISSION_LEVEL_ADMIN;
				if (tempstr == permdescstr[PERMISSION_LEVEL_SERVEROWNER]) tempns.defaultpermission = PERMISSION_LEVEL_SERVEROWNER;
				if (tempstr == permdescstr[PERMISSION_LEVEL_HELIUMOWNER]) tempns.defaultpermission = PERMISSION_LEVEL_HELIUMOWNER;
			}
			else {
				cfgl << HLL::LL_ERR << "Failed to read the \"default\" attribute, setting the default permission level to guest" << hendl;
				tempns.defaultpermission = PERMISSION_LEVEL_GUEST;
			}

			tinyxml2::XMLElement* permlevel = permns->FirstChildElement("HeliumOwner");
			if (permlevel != NULL) {
				auto player = permlevel->FirstChildElement("Player");
				if (player != NULL) {
					while (true) {
						if (player->GetText()) {
							tempns.permissions.push_back(make_pair<string, int>(player->GetText(), PERMISSION_LEVEL_SERVEROWNER));
						}

						player = permlevel->NextSiblingElement("Player");

						if (player == NULL) break;
					}
				}
			}

			permlevel = permns->FirstChildElement("ServerOwner");
			if (permlevel != NULL) {
				auto player = permlevel->FirstChildElement("Player");
				if (player != NULL) {
					while (true) {
						if (player->GetText()) {
							tempns.permissions.push_back(make_pair<string, int>(player->GetText(), PERMISSION_LEVEL_SERVEROWNER));
						}

						player = permlevel->NextSiblingElement("Player");

						if (player == NULL) break;
					}
				}
			}

			permlevel = permns->FirstChildElement("Admin");
			if (permlevel != NULL) {
				auto player = permlevel->FirstChildElement("Player");
				if (player != NULL) {
					while (true) {
						if (player->GetText()) {
							tempns.permissions.push_back(make_pair<string, int>(player->GetText(), PERMISSION_LEVEL_ADMIN));
						}

						player = permlevel->NextSiblingElement("Player");

						if (player == NULL) break;
					}
				}
			}

			permlevel = permns->FirstChildElement("User");
			if (permlevel != NULL) {
				auto player = permlevel->FirstChildElement("Player");
				if (player != NULL) {
					while (true) {
						if (player->GetText()) {
							tempns.permissions.push_back(make_pair<string, int>(player->GetText(), PERMISSION_LEVEL_USER));
						}

						player = permlevel->NextSiblingElement("Player");

						if (player == NULL) break;
					}
				}
			}

			permlevel = permns->FirstChildElement("Guest");
			if (permlevel != NULL) {
				auto player = permlevel->FirstChildElement("Player");
				if (player != NULL) {
					while (true) {
						if (player->GetText()) {
							tempns.permissions.push_back(make_pair<string, int>(player->GetText(), PERMISSION_LEVEL_GUEST));
						}

						player = permlevel->NextSiblingElement("Player");

						if (player == NULL) break;
					}
				}
			}

			Permissions.push_back(tempns);

			permns = permns->NextSiblingElement("PermissionNamespace");
			if (permns == NULL) {
				break;
			}
		}
		
		return XMLError::XML_SUCCESS;
	}
	int CreateHeliumConfig() {
		HeliumEndline hendl;
		const char* declaration = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
		XMLDocument doc;
		XMLElement* root;
		XMLElement* set;
		XMLElement* perm;
		XMLElement* server;

		cfgl << HLL::LL_INFO << "Creating Helium Config File." << hendl;

		if (auto ret = doc.Parse(declaration); ret != XMLError::XML_SUCCESS) {
			cfgl << HLL::LL_ERR << "Failed to create declaration of helium config file : " << doc.ErrorID() << "(" << doc.ErrorName() << ")" << hendl;
			cfgl << doc.ErrorStr() << hendl;
			return ret;
		}

		if (root = doc.NewElement("HeliumConfig"); root == NULL) {
			cfgl << HLL::LL_ERR << "Failed to create root element of helium config file : " << doc.ErrorID() << "(" << doc.ErrorName() << ")" << hendl;
			cfgl << doc.ErrorStr() << hendl;
			return doc.ErrorID();
		}

		if (set = doc.NewElement("Settings"); set == NULL) {
			cfgl << HLL::LL_ERR << "Failed to create Settings element of helium config file : " << doc.ErrorID() << "(" << doc.ErrorName() << ")" << hendl;
			cfgl << doc.ErrorStr() << hendl;
			return doc.ErrorID();
		}

		if (perm = doc.NewElement("Permissions"); perm == NULL) {
			cfgl << HLL::LL_ERR << "Failed to create Permissions element of helium config file : " << doc.ErrorID() << "(" << doc.ErrorName() << ")" << hendl;
			cfgl << doc.ErrorStr() << hendl;
			return doc.ErrorID();
		}

		if (server = doc.NewElement("Servers"); server == NULL) {
			cfgl << HLL::LL_ERR << "Failed to create Servers element of helium config file : " << doc.ErrorID() << "(" << doc.ErrorName() << ")" << hendl;
			cfgl << doc.ErrorStr() << hendl;
			return doc.ErrorID();
		}

		if (auto ele = doc.NewElement("Language"); ele != NULL)
			set->InsertEndChild(ele);
		else {
			cfgl << HLL::LL_ERR << "Failed to create element of helium config file : " << doc.ErrorID() << "(" << doc.ErrorName() << ")" << hendl;
			cfgl << doc.ErrorStr() << hendl;
			return doc.ErrorID();
		}
		if (auto ele = doc.NewElement("Encoding"); ele != NULL)
			set->InsertEndChild(ele);
		else {
			cfgl << HLL::LL_ERR << "Failed to create element of helium config file : " << doc.ErrorID() << "(" << doc.ErrorName() << ")" << hendl;
			cfgl << doc.ErrorStr() << hendl;
			return doc.ErrorID();
		}
		if (auto ele = doc.NewElement("ExtensionDirectory"); ele != NULL)
			set->InsertEndChild(ele);
		else {
			cfgl << HLL::LL_ERR << "Failed to create element of helium config file : " << doc.ErrorID() << "(" << doc.ErrorName() << ")" << hendl;
			cfgl << doc.ErrorStr() << hendl;
			return doc.ErrorID();
		}
		if (auto ele = doc.NewElement("ScriptDirectory"); ele != NULL)
			set->InsertEndChild(ele);
		else {
			cfgl << HLL::LL_ERR << "Failed to create element of helium config file : " << doc.ErrorID() << "(" << doc.ErrorName() << ")" << hendl;
			cfgl << doc.ErrorStr() << hendl;
			return doc.ErrorID();
		}
		if (auto ele = doc.NewElement("AutoUpdate"); ele != NULL)
			set->InsertEndChild(ele);
		else {
			cfgl << HLL::LL_ERR << "Failed to create element of helium config file : " << doc.ErrorID() << "(" << doc.ErrorName() << ")" << hendl;
			cfgl << doc.ErrorStr() << hendl;
			return doc.ErrorID();
		}
		root->InsertEndChild(set);

		if (auto ele = doc.NewElement("PermissionNamespace"); ele != NULL) {
			if (auto child = doc.NewElement("Guest"); child != NULL) {
				if (auto player = doc.NewElement("Player"); player != NULL) {
					child->InsertEndChild(player);
					ele->InsertEndChild(child);
				}
			}
			if (auto child = doc.NewElement("User"); child != NULL) {
				if (auto player = doc.NewElement("Player"); player != NULL) {
					child->InsertEndChild(player);
					ele->InsertEndChild(child);
				}
			}
			if (auto child = doc.NewElement("Admin"); child != NULL) {
				if (auto player = doc.NewElement("Player"); player != NULL) {
					child->InsertEndChild(player);
					ele->InsertEndChild(child);
				}
			}
			if (auto child = doc.NewElement("ServerOwner"); child != NULL) {
				if (auto player = doc.NewElement("Player"); player != NULL) {
					child->InsertEndChild(player);
					ele->InsertEndChild(child);
				}
			}
			if (auto child = doc.NewElement("HeliumOwner"); child != NULL) {
				if (auto player = doc.NewElement("Player"); player != NULL) {
					child->InsertEndChild(player);
					ele->InsertEndChild(child);
				}
			}
			perm->InsertEndChild(ele);
			root->InsertEndChild(perm);
		}
		else {
			cfgl << HLL::LL_ERR << "Failed to create element of helium config file : " << doc.ErrorID() << "(" << doc.ErrorName() << ")" << hendl;
			cfgl << doc.ErrorStr() << hendl;
			return doc.ErrorID();
		}

		if (auto ele = doc.NewElement("ServerName"); ele != NULL) {
			if (auto s = doc.NewElement("ServerType"); s != NULL) ele->InsertEndChild(s);
			if (auto s = doc.NewElement("AutoStart"); s != NULL) ele->InsertEndChild(s);
			if (auto s = doc.NewElement("OutputVisible"); s != NULL) ele->InsertEndChild(s);
			if (auto s = doc.NewElement("ServerUUID"); s != NULL) ele->InsertEndChild(s);
			if (auto rcon = doc.NewElement("rcon"); rcon != NULL) {
				auto e = doc.NewElement("Enable");
				auto p = doc.NewElement("Port");
				auto a = doc.NewElement("Password");
				if (e != NULL && p != NULL && a != NULL) {
					rcon->InsertEndChild(e);
					rcon->InsertEndChild(p);
					rcon->InsertEndChild(a);
					ele->InsertEndChild(rcon);
				}
			}
			server->InsertEndChild(ele);
			root->InsertEndChild(server);
		}
		else {
			cfgl << HLL::LL_ERR << "Failed to create element of helium config file : " << doc.ErrorID() << "(" << doc.ErrorName() << ")" << hendl;
			cfgl << doc.ErrorStr() << hendl;
			return doc.ErrorID();
		}

		doc.InsertEndChild(root);

		if (auto ret = doc.SaveFile(CFG_FILENAME); ret != XMLError::XML_SUCCESS) {
			cfgl << HLL::LL_ERR << "Failed to create helium config file : " << doc.ErrorID() << "(" << doc.ErrorName() << ")" << hendl;
			cfgl << doc.ErrorStr() << hendl;
			return doc.ErrorID();
		}
		
		return XMLError::XML_SUCCESS;
	}

	int GetLanguage() {
		return Settings.Language;
	}
	string GetEncoding() {
		return Settings.Encoding;
	}
	string GetExtensionDirectory() {
		return Settings.ExtDir;
	}
	string GetScriptDirectory() {
		return Settings.ScrDir;
	}
	bool IsAutoUpdate() {
		return Settings.AutoUpdate;
	}
	int QueryPermission(string server, string name) {

	}
	int QueryPermission(uuid server, string name) {

	}
	int QueryDefaultPermission(string server) {

	}
	int QuertDefaultPermission(uuid server) {

	}
}