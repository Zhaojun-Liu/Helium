/*
* Helium Pre-Alpha 0.6.1
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

#include"permissions.h"
namespace Helium {
	vector<PermissionNamespace> permissions;
	const char* permdescstr[] = { "Guest", "User", "Admin", "ServerOwner", "HeliumOwner" };
	HeliumLogger log("HeliumPermissionReader");

	[[nodiscard("Ignoring return value of ReadPermissionFile()")]]
	int ReadPermissionFile() {
		tinyxml2::XMLDocument permdoc;
		PermissionNamespace tempns;
		auto lastxmlerr = permdoc.LoadFile(PERMISSION_FILENAME);
		HeliumEndline hendl;

		if (lastxmlerr != tinyxml2::XMLError::XML_SUCCESS) {
			log << HLL::LL_ERR << "Failed to read permission file, using default permission level." << hendl;
			return -1;
		}

		auto root = permdoc.RootElement();
		if (root == NULL) {
			log << HLL::LL_ERR << "Failed to get the root element of the permission file, using default permission level" << hendl;
			return -1;
		}

		auto permns = root->FirstChildElement("PermissionNamespace");
		if (permns == NULL) {
			log << HLL::LL_ERR << "Failed to read the permission namespace element, using default permission level" << hendl;
			return -1;
		}

		while (true) {
			ZeroMemory(&tempns, sizeof(tempns));
			string tempstr;

			tinyxml2::XMLAttribute* attr = const_cast<tinyxml2::XMLAttribute*>(permns->FindAttribute("server"));
			if (attr->Value()) {
				string tempstr = attr->Value();
				for (auto& server : serverlist) {
					if (server.GetServerName() == tempstr) {
						GUID guid;
						server.GetServerGUID(&guid);
						tempns.serverguid = guid;
					}
				}
			}
			else {
				log << HLL::LL_ERR << "Failed to read the \"server\" attribute,  using default permission level" << hendl;
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
				log << HLL::LL_ERR << "Failed to read the \"server\" attribute,  using default permission level" << hendl;
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

			permissions.push_back(tempns);

			permns = permns->NextSiblingElement("PermissionNamespace");
			if (permns == NULL) {
				break;
			}
		}
		return 0;
	}
	[[nodiscard("Ignoring return value of SavePermissionFile()")]]
	int SavePermissionFile() {
		tinyxml2::XMLDocument doc;
		doc.NewDeclaration("?xml version=\"1.0\"?");

		auto root = doc.NewElement("HeliumPermission");

		for (auto perm : permissions) {
			tinyxml2::XMLElement* ns;

			tinyxml2::XMLElement* howner = doc.NewElement("HeliumOwner");
			tinyxml2::XMLElement* sowner = doc.NewElement("ServerOwner");
			tinyxml2::XMLElement* admin = doc.NewElement("Admin");
			tinyxml2::XMLElement* user = doc.NewElement("User");
			tinyxml2::XMLElement* guest = doc.NewElement("Guest");

			ns = doc.NewElement("PermissionNamespace");

			for (auto& server : serverlist) {
				GUID guid;
				server.GetServerGUID(&guid);
				if (perm.serverguid == guid) {
					ns->SetAttribute("server", server.GetServerName().c_str());
				}
			}

			if (perm.defaultpermission == PERMISSION_LEVEL_GUEST) {
				ns->SetAttribute("default", "guest");
			}
			if (perm.defaultpermission == PERMISSION_LEVEL_USER) {
				ns->SetAttribute("default", "user");
			}
			if (perm.defaultpermission == PERMISSION_LEVEL_ADMIN) {
				ns->SetAttribute("default", "admin");
			}
			if (perm.defaultpermission == PERMISSION_LEVEL_SERVEROWNER) {
				ns->SetAttribute("default", "serverowner");
			}
			if (perm.defaultpermission == PERMISSION_LEVEL_HELIUMOWNER) {
				ns->SetAttribute("default", "heliumowner");
			}

			for (auto permins : perm.permissions) {
				tinyxml2::XMLElement* player = doc.NewElement("Player");

				switch (permins.second) {
				case PERMISSION_LEVEL_GUEST:
					if (!permins.first.empty()) {
						tinyxml2::XMLText* playername = doc.NewText(permins.first.c_str());
						player->InsertEndChild(playername);
					}
					guest->InsertEndChild(player);
					break;
				case PERMISSION_LEVEL_USER:
					if (!permins.first.empty()) {
						tinyxml2::XMLText* playername = doc.NewText(permins.first.c_str());
						player->InsertEndChild(playername);
					}
					user->InsertEndChild(player);
					break;
				case PERMISSION_LEVEL_ADMIN:
					if (!permins.first.empty()) {
						tinyxml2::XMLText* playername = doc.NewText(permins.first.c_str());
						player->InsertEndChild(playername);
					}
					admin->InsertEndChild(player);
					break;
				case PERMISSION_LEVEL_SERVEROWNER:
					if (!permins.first.empty()) {
						tinyxml2::XMLText* playername = doc.NewText(permins.first.c_str());
						player->InsertEndChild(playername);
					}
					sowner->InsertEndChild(player);
					break;
				case PERMISSION_LEVEL_HELIUMOWNER:
					if (!permins.first.empty()) {
						tinyxml2::XMLText* playername = doc.NewText(permins.first.c_str());
						player->InsertEndChild(playername);
					}
					howner->InsertEndChild(player);
					break;
				default:
					break;
				}

				ns->InsertEndChild(guest);
				ns->InsertEndChild(user);
				ns->InsertEndChild(admin);
				ns->InsertEndChild(sowner);
				ns->InsertEndChild(howner);

				root->InsertEndChild(ns);
			}
		}

		doc.InsertEndChild(root);
		doc.SaveFile(PERMISSION_FILENAME);

		return 0;
	}
	[[nodiscard("Ignoring return value of CreatePermissionFile()")]]
	int CreatePermissionFile() {
		tinyxml2::XMLDocument doc;
		HeliumEndline hendl;

		doc.NewDeclaration("?xml version=\"1.0\"?");

		auto root = doc.NewElement("HeliumPermission");
		doc.InsertEndChild(root);

		tinyxml2::XMLElement* ns;
		ns = doc.NewElement("PermissionNamespace");
		ns->SetAttribute("server", "");
		root->InsertEndChild(ns);

		if (doc.SaveFile(PERMISSION_FILENAME) != tinyxml2::XMLError::XML_SUCCESS) {
			log << HLL::LL_ERR << "Failed to create permission.xml." << hendl;
			return -1;
		}

		return 0;
	}
}