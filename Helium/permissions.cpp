#include"permissions.h"

vector<PermissionNamespace> permissions;
const char* permdescstr[] = {"Guest", "User", "Admin", "ServerOwner", "HeliumOwner"};

[[nodiscard("Ignoring return value of ReadPermissionFile()")]]
int _stdcall ReadPermissionFile() {
	tinyxml2::XMLDocument permdoc;
	PermissionNamespace tempns;
	auto lastxmlerr = permdoc.LoadFile(PERMISSION_FILENAME);
	if (lastxmlerr != tinyxml2::XMLError::XML_SUCCESS) {
		spdlog::error("Cannot read permission file, using default permission level.");
		return -1;
	}

	auto root = permdoc.RootElement();
	if (root == NULL) {
		spdlog::error("Cannot get the root element of the permission file, using default permission level");
		return -1;
	}

	auto permns = root->FirstChildElement("PermissionNamespace");
	if(permns == NULL) {
		spdlog::error("Error reading the permission namespace element, using default permission level");
		return -1;
	}

	while (true) {
		ZeroMemory(&tempns, sizeof(tempns));
		string tempstr;

		auto attr = permns->FindAttribute("server");
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
			spdlog::error("Error reading the \"server\" attribute,  using default permission level");
		}

		auto attr = permns->FindAttribute("default");
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
			spdlog::error("Error reading the \"server\" attribute,  using default permission level");
		}
		
		auto permlevel = permns->FirstChildElement("ServerOwner");
		if (permlevel != NULL) {
			auto player = permlevel->FirstChildElement("Player");
			if (player != NULL) {
				while (true) {
					if (player->GetText()) {
						tempns.permissions.push_back(make_pair(player->GetText(), PERMISSION_LEVEL_SERVEROWNER));
					}

					player = permlevel->NextSiblingElement("Player");

					if (player == NULL) break;
				}
			}
		}

		auto permlevel = permns->FirstChildElement("Admin");
		if (permlevel != NULL) {
			auto player = permlevel->FirstChildElement("Player");
			if (player != NULL) {
				while (true) {
					if (player->GetText()) {
						tempns.permissions.push_back(make_pair(player->GetText(), PERMISSION_LEVEL_ADMIN));
					}

					player = permlevel->NextSiblingElement("Player");

					if (player == NULL) break;
				}
			}
		}

		auto permlevel = permns->FirstChildElement("User");
		if (permlevel != NULL) {
			auto player = permlevel->FirstChildElement("Player");
			if (player != NULL) {
				while (true) {
					if (player->GetText()) {
						tempns.permissions.push_back(make_pair(player->GetText(), PERMISSION_LEVEL_USER));
					}

					player = permlevel->NextSiblingElement("Player");

					if (player == NULL) break;
				}
			}
		}

		auto permlevel = permns->FirstChildElement("GUEST");
		if (permlevel != NULL) {
			auto player = permlevel->FirstChildElement("Player");
			if (player != NULL) {
				while (true) {
					if (player->GetText()) {
						tempns.permissions.push_back(make_pair(player->GetText(), PERMISSION_LEVEL_GUEST));
					}

					player = permlevel->NextSiblingElement("Player");

					if (player == NULL) break;
				}
			}
		}

		permissions.push_back(tempns);

		permns = root->NextSiblingElement("PermissionNamespace");
		if (permns == NULL) {
			break;
		}
	}
	return 0;
}
[[nodiscard("Ignoring return value of SavePermissionFile()")]]
int _stdcall SavePermissionFile() {
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
int _stdcall CreatePermissionFile() {
	tinyxml2::XMLDocument doc;
	doc.NewDeclaration("?xml version=\"1.0\"?");

	auto root = doc.NewElement("HeliumPermission");
	doc.InsertEndChild(root);

	for (auto perm : permissions) {
		tinyxml2::XMLElement* ns;

		for (auto& server : serverlist) {
			GUID guid;
			server.GetServerGUID(&guid);
			if (perm.serverguid == guid) {
				ns = doc.NewElement(server.GetServerName().c_str());
				
			}
		}
	}

	return 0;
}