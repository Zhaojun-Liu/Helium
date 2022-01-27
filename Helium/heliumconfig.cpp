/*
* Helium
* Copyright (C) 2021-2022 HeliumDevTeam
*
* Helium is a customizable extension system for Minecraft server which is written in C++.
* This project is inspired by the [Fallen-Breath/MCDReforged](https://github.com/Fallen-Breath/MCDReforged).
* We target to provide a liter, faster, and more customizable choice.
* As a trade-off, we sacrifice its portability and the simplicity of writing extensions.
* (we r sry that we haven't finish the first alpha version yet, if u r interested in our project, we recommend u to use mcdr as a temporary alternative)
* This project is licensed by the GPL-3.0-or-later license.
*
* Very very special thank to contributors of the following projects:
* [Fallen-Breath/MCDReforged](https://github.com/Fallen-Breath/MCDReforged)
* [kpeeters/tree.hh](https://github.com/kpeeters/tree.hh)
* [leethomason/tinyxml2](https://github.com/leethomason/tinyxml2/)
* [jcwangxp/Crossline](https://github.com/jcwangxp/Crossline/)
*
* You can get the lastest source code and releases of Helium at :
* https://github.com/Minecraft1248/Helium
*
* -------------------------------------------------------------------------------------------------------------------------------------------------------
*    This file is part of Helium.
*
*    Helium is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    Helium is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with Helium.  If not, see <https://www.gnu.org/licenses/>.
* -------------------------------------------------------------------------------------------------------------------------------------------------------
*/

#include"heliumconfig.h"

namespace Helium {
	HeliumLogger cfgl("HeliumConfigReader");
	const char* permdescstr[] = { "Guest", "User", "Admin", "ServerOwner", "HeliumOwner" };
	HeliumSetting Settings;
	vector<PermissionNamespace> Permissions;
	extern vector<HeliumMinecraftServer> heliumservers;

	int ReadHeliumConfig() {
		XMLDocument cfg;
		XMLElement* root;
		XMLElement* set;
		XMLElement* perm;
		XMLElement* server;
		XMLElement* rcon;
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

		if (rcon = set->FirstChildElement("rcon"); rcon == NULL) {
			cfgl << HLL::LL_ERR << "Failed to get the rcon element of helium config file : " << cfg.ErrorID() << "(" << cfg.ErrorName() << ")" << hendl;
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

		while (servernode) {
			HeliumMinecraftServer tempins;
			XMLElement* servernodechild;

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

			tempins.GenServerUUID();

			heliumservers.push_back(tempins);
			servernode = servernode->NextSiblingElement("MinecraftServer");
		}

		while (true) {
			PermissionNamespace tempns;
			ZeroMemory(&tempns, sizeof(tempns));
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
		tinyxml2::XMLDocument doc;

		cfgl << HLL::LL_INFO << "Creating Helium Config File" << hendl;

		if (auto ret = doc.Parse(declaration); ret != XMLError::XML_SUCCESS) {
			cfgl << HLL::LL_ERR << "Failed to create XML file declaration for the helium config file" << hendl;
			cfgl << doc.ErrorStr() << hendl;
			return ret;
		}


	}
}