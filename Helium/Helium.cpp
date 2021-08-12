﻿#pragma region Includes
//不要随意调换include顺序 awa

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<Windows.h>
#include<thread>
#include<strstream>
#include<regex>
#include<functional>

#include"confuses.h"
#include"logger.h"
#include"tinyxml2.h"
#include"parse.h"
#include"xmlutils.h"
#include"xmlmacros.h"
#include"minecraftserver.h"
#include"extension.h"

#include<spdlog/spdlog.h>
#pragma comment(lib, "replxx-static-rd.lib")
#define REPLXX_STATIC
#include"replxx/replxx.hxx"

using namespace std;
using namespace replxx;

#pragma endregion

#pragma region Macros
#define PROJECT_NAME_STR "Helium"
#define PROJECT_VER_STR "0.4.2.03"
#define PROJECT_DEVSTAT "Pre-Alpha"

#define CFG_FILENAME "HeliumConfig.xml"
#define gnsbn(name) DuN(pRootEle,name)
START_CONFIG_NODES_REGISTER(ConfigNode);
#pragma endregion

#pragma region Constants
#define print(a) std::cout<< a << endl;
#pragma endregion

#pragma region Types

#pragma endregion

#pragma region Var
Logger logger;
map<string, HeliumExtension> extensions;
#pragma endregion

#pragma region Callback
Replxx::completions_t hook_completion(std::string const& context, int& contextLen, std::vector<std::string> const& examples) {
    Replxx::completions_t completions;
    int utf8ContextLen = context.length();
    int prefixLen = context.length() - utf8ContextLen;
    if ((prefixLen > 0) && (context[prefixLen - 1] == '\\')) {
        --prefixLen;
        ++utf8ContextLen;
    }
    contextLen = context.length() + prefixLen;

    std::string prefix{ context.substr(prefixLen) };
    for (auto const& e : examples) {
        if (e.compare(0, prefix.size(), prefix) == 0) {
            Replxx::Color c = Replxx::Color::DEFAULT;
            completions.emplace_back(e.c_str(), c);
        }
    }

    return completions;
}

Replxx::hints_t hook_hint(std::string const& context, int& contextLen, Replxx::Color& color, std::vector<std::string> const& examples) {
    Replxx::hints_t hints;
    // only show hint if prefix is at least 'n' chars long
    // or if prefix begins with a specific character

    int utf8ContextLen = context.length();
    int prefixLen = context.length() - utf8ContextLen;
    contextLen = context.length();
    std::string prefix{ context.substr(prefixLen) };

    if (prefix.size() >= 2 || (!prefix.empty() && prefix.at(0) == '.')) {
        for (auto const& e : examples) {
            if (e.compare(0, prefix.size(), prefix) == 0) {
                hints.emplace_back(e.c_str());
            }
        }
    }

    // set hint color to green if single match found
    if (hints.size() == 1) {
        color = Replxx::Color::GREEN;
    }

    return hints;
}
void hook_color(std::string const& context, Replxx::colors_t& colors, std::vector<std::pair<std::string, Replxx::Color>> const& regex_color) {
    // highlight matching regex sequences
    for (auto const& e : regex_color) {
        size_t pos{ 0 };
        std::string str = context;
        std::smatch match;

        while (std::regex_search(str, match, std::regex(e.first))) {
            std::string c{ match[0] };
            std::string prefix(match.prefix().str());
            pos += prefix.length();
            int len = c.length();

            for (int i = 0; i < len; ++i) {
                colors.at(pos + i) = e.second;
            }

            pos += len;
            str = match.suffix();
        }
    }
}
#pragma endregion

#pragma region Parser
/*
香草
[10:33:44] [Worker-Main-5/INFO]: Loaded 7 recipes
[10:33:45] [Worker-Main-5/INFO]: Loaded 927 advancements
[10:33:47] [Server thread/INFO]: Starting minecraft server version 1.16.2
[10:33:47] [Server thread/INFO]: Loading properties
[10:33:47] [Server thread/INFO]: Default game type: SURVIVAL
[10:33:47] [Server thread/INFO]: Starting Minecraft server on *:25500
[10:33:48] [Server thread/INFO]: Preparing level "world"
[10:33:48] [Server thread/INFO]: Preparing start region for dimension minecraft:overworld
[10:33:51] [Server thread/INFO]: Preparing spawn area: 0%
[10:34:06] [Server thread/INFO]: Time elapsed: 17929 ms
[10:34:06] [Server thread/INFO]: Done (18.072s)! For help, type "help"
[10:35:32] [Server thread/INFO]: Stopping the server
[10:35:33] [Server thread/INFO]: Stopping server
[10:35:33] [Server thread/INFO]: Saving players
[10:35:33] [Server thread/INFO]: Saving worlds
[10:35:33] [Server thread/INFO]: Saving chunks for level 'ServerLevel[world]'/minecraft:overworld
[10:35:34] [Server thread/INFO]: ThreadedAnvilChunkStorage (world): All chunks are saved
[10:35:34] [Server thread/INFO]: Saving chunks for level 'ServerLevel[world]'/minecraft:the_nether
[10:35:34] [Server thread/INFO]: ThreadedAnvilChunkStorage (DIM-1): All chunks are saved
[10:35:34] [Server thread/INFO]: Saving chunks for level 'ServerLevel[world]'/minecraft:the_end
[10:35:34] [Server thread/INFO]: ThreadedAnvilChunkStorage (DIM1): All chunks are saved
[10:35:34] [Server thread/INFO]: ThreadedAnvilChunkStorage (world): All chunks are saved
[10:35:34] [Server thread/INFO]: ThreadedAnvilChunkStorage (DIM-1): All chunks are saved
[10:35:34] [Server thread/INFO]: ThreadedAnvilChunkStorage (DIM1): All chunks are saved
法布里克
[10:35:56] [main/INFO]: Loading for game Minecraft 1.16.2
[10:35:57] [main/INFO]: [FabricLoader] Loading 2 mods: minecraft@1.16.2, fabricloader@0.9.1+build.205
[10:35:57] [main/INFO]: SpongePowered MIXIN Subsystem Version=0.8.1 Source=file:/F:/MCDReforged-master/server/fabric-server-launch.jar Service=Knot/Fabric Env=SERVER
[10:36:10] [main/INFO]: Reloading ResourceManager: Default
[10:36:11] [Worker-Main-4/INFO]: Loaded 7 recipes
[10:36:12] [Worker-Main-4/INFO]: Loaded 927 advancements
[10:36:14] [Server thread/INFO]: Starting minecraft server version 1.16.2
[10:36:14] [Server thread/INFO]: Loading properties
[10:36:14] [Server thread/INFO]: Default game type: SURVIVAL
[10:36:14] [Server thread/INFO]: Starting Minecraft server on *:25500
[10:36:14] [Server thread/INFO]: Using default channel type
[10:36:16] [Server thread/INFO]: Preparing level "world"
[10:36:16] [Server thread/INFO]: Preparing start region for dimension minecraft:overworld
[10:36:30] [Worker-Main-6/INFO]: Preparing spawn area: 92%
[10:36:31] [Server thread/INFO]: Preparing spawn area: 97%
[10:36:31] [Server thread/INFO]: Time elapsed: 15215 ms
[10:36:31] [Server thread/INFO]: Done (15.483s)! For help, type "help"
[10:36:35] [Server thread/INFO]: Stopping the server
[10:36:35] [Server thread/INFO]: Stopping server
[10:36:35] [Server thread/INFO]: Saving players
[10:36:35] [Server thread/INFO]: Saving worlds
[10:36:35] [Server thread/INFO]: Saving chunks for level 'ServerLevel[world]'/minecraft:overworld
[10:36:36] [Server thread/INFO]: ThreadedAnvilChunkStorage (world): All chunks are saved
[10:36:36] [Server thread/INFO]: Saving chunks for level 'ServerLevel[world]'/minecraft:the_nether
[10:36:36] [Server thread/INFO]: ThreadedAnvilChunkStorage (DIM-1): All chunks are saved
[10:36:36] [Server thread/INFO]: Saving chunks for level 'ServerLevel[world]'/minecraft:the_end
[10:36:36] [Server thread/INFO]: ThreadedAnvilChunkStorage (DIM1): All chunks are saved
[10:36:36] [Server thread/INFO]: ThreadedAnvilChunkStorage (world): All chunks are saved
[10:36:36] [Server thread/INFO]: ThreadedAnvilChunkStorage (DIM-1): All chunks are saved
[10:36:36] [Server thread/INFO]: ThreadedAnvilChunkStorage (DIM1): All chunks are saved
*/

void TestParser() {

    FaQ ost;
    ooOoo00o eCy = oOO("[10:36:14] [Server thread/INFO]: Starting Minecraft server on *:25500");
    ost << "服务器将在端口" << eCy.port << "启动\n";
    ooOo00o KbG = OOo("[10:36:31] [Server thread/INFO]: Time elapsed: 15215 ms");
    qfa ostr;
    ostr << "服务器已启动，用时" << KbG.itime << "ms\n";

    logger.info(ostr.str().c_str());
    logger.warn(ostr.str().c_str());
    logger.error(ostr.str().c_str());
    logger.fatal(ostr.str().c_str());
    logger.setTimeStamp(DISABLE_TIME_STAMP);
    logger.info(ostr.str().c_str());
    logger.warn(ostr.str().c_str());
    logger.error(ostr.str().c_str());
    logger.fatal(ostr.str().c_str());
    logger.setTimeStamp(ENABLE_TIME_STAMP);
    logger.info(ost.str().c_str());
    logger.warn(ost.str().c_str());
    logger.error(ost.str().c_str());
    logger.fatal(ost.str().c_str());
    logger.setTimeStamp(DISABLE_TIME_STAMP);
    logger.info(ost.str().c_str());
    logger.warn(ost.str().c_str());
    logger.error(ost.str().c_str());
    logger.fatal(ost.str().c_str());
    system("pause");
}

#pragma endregion

#pragma region Config

[[nodiscard("Do not discard return value of SaveConfigFile() plz")]]
int _stdcall SaveConfigFile() {
    tinyxml2::XMLDocument doc;
    if (auto ret = doc.LoadFile(CFG_FILENAME); ret != 0) {
        cout << "Failed to create XML file declaration" << endl;
        return -1;
    }

    tinyxml2::XMLElement* root = doc.NewElement("HeliumConfig");
    doc.InsertEndChild(root);

    for (auto node : _confignodes_) {
        stringstream sstr;

        switch (node.valuetype)
        {
        [[likely]] case VALUE_TYPE_INTEGER:
            try {
                sstr << std::get<int>(node.var); // access by type
                tinyxml2::XMLElement* newelement = doc.NewElement(node.nodename.c_str());
                tinyxml2::XMLText* newtext = doc.NewText(sstr.str().c_str());
                root->InsertEndChild(newelement);
                newelement->InsertEndChild(newtext);
            }
            catch (const std::bad_variant_access& e) { // in case a wrong type/index is used
                cout << "Failed to get the value" << endl;
            }
            break;
        [[likely]] case VALUE_TYPE_DOUBLE:
            try {
                sstr << std::get<double>(node.var); // access by type
                tinyxml2::XMLElement* newelement = doc.NewElement(node.nodename.c_str());
                tinyxml2::XMLText* newtext = doc.NewText(sstr.str().c_str());
                root->InsertEndChild(newelement);
                newelement->InsertEndChild(newtext);
            }
            catch (const std::bad_variant_access& e) { // in case a wrong type/index is used
                cout << "Failed to get the value" << endl;
            }
            break;
        [[likely]] case VALUE_TYPE_STRING:
            try {
                sstr << std::get<string>(node.var); // access by type
                tinyxml2::XMLElement* newelement = doc.NewElement(node.nodename.c_str());
                tinyxml2::XMLText* newtext = doc.NewText(sstr.str().c_str());
                root->InsertEndChild(newelement);
                newelement->InsertEndChild(newtext);
            }
            catch (const std::bad_variant_access& e) { // in case a wrong type/index is used
                cout << "Failed to get the value" << endl;
            }
            break;
        [[likely]] case VALUE_TYPE_BOOLEAN:
            try {
                sstr << boolstr[std::get<bool>(node.var)]; // access by type
                tinyxml2::XMLElement* newelement = doc.NewElement(node.nodename.c_str());
                tinyxml2::XMLText* newtext = doc.NewText(sstr.str().c_str());
                root->InsertEndChild(newelement);
                newelement->InsertEndChild(newtext);
            }
            catch (const std::bad_variant_access& e) { // in case a wrong type/index is used
                cout << "Failed to get the value" << endl;
            }
            break;
        [[unlikely]] default:
            break;
        }

        sstr.clear();
    }

    for (vector<MinecraftServerInstance>::iterator it = serverlist.begin(); it < serverlist.end(); it++) {
        tinyxml2::XMLElement* newelem = doc.NewElement("MinecraftServer");
        string temp;
        switch (it->GetServerType())
        {
        [[likely]] case SERVER_TYPE_VANILLA:
            temp = "vanilla";
            break;
        [[likely]] case SERVER_TYPE_FORGE:
            temp = "forge";
            break;
        [[likely]] case SERVER_TYPE_BUKKIT:
            temp = "bukkit";
            break;
        [[likely]] case SERVER_TYPE_BUKKIT14:
            temp = "bukkit14";
            break;
        [[likely]] case SERVER_TYPE_BUNGEECORD:
            temp = "bungeecord";
            break;
        [[likely]] case SERVER_TYPE_WATERFALL:
            temp = "waterfall";
            break;
        [[likely]] case SERVER_TYPE_CAT:
            temp = "cat";
            break;
        [[likely]] case SERVER_TYPE_BETA18:
            temp = "beta18";
            break;
        [[unlikely]] default:
            temp = "undef";
            break;
        }
        newelem->SetAttribute("type", temp.c_str());

        temp.clear();
        if (it->GetStartupType() == STARTUP_TYPE_JAR) temp = "jar";
        else temp = "bat";
        newelem->SetAttribute("startuptype", temp.c_str());

        temp.clear();
        if (it->GetAutoStart()) temp = "true";
        else temp = "false";
        newelem->SetAttribute("autostart", temp.c_str());

        temp.clear();
        if (it->GetVisibility()) temp = "true";
        else temp = "false";
        newelem->SetAttribute("outputvisibility", temp.c_str());

        tinyxml2::XMLElement* newchild = newelem->InsertNewChildElement("ServerName");
        newchild->SetText(it->GetServerName().c_str());

        newchild = newelem->InsertNewChildElement("ServerDirectory");
        newchild->SetText(it->GetServerDirectory().c_str());

        newchild = newelem->InsertNewChildElement("JVMDirectory");
        newchild->SetText(it->GetJVMDirectory().c_str());

        newchild = newelem->InsertNewChildElement("JVMOption");
        newchild->SetText(it->GetJVMOption().c_str());

        newchild = newelem->InsertNewChildElement("ServerFileName");
        newchild->SetText(it->GetServerFileName().c_str());

        newchild = newelem->InsertNewChildElement("MaxMemory");
        newchild->SetText(it->GetMaxmem().c_str());

        newchild = newelem->InsertNewChildElement("MinMemory");
        newchild->SetText(it->GetMinmem().c_str());
    }

    if (auto ret = doc.SaveFile(CFG_FILENAME); ret != 0) {
        cout << "Failed to save config file" << endl;
        return -1;
    }

    return 0;
}

[[nodiscard("Ignoring return value may cause config file create incorrectly.")]]
int _stdcall CreateConfigFile()
{
    cout << "Enter CreateConfigFile()" << endl;
    const char* declaration = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
    tinyxml2::XMLDocument doc;
    if (auto ret = doc.Parse(declaration); ret != 0) {
        cout << "Failed to create XML file declaration" << endl;
        return -1;
    }
    
    tinyxml2::XMLElement* root = doc.NewElement("HeliumConfig");
    doc.InsertEndChild(root);

    for (auto node : _confignodes_) {
        stringstream sstr;
        
        switch (node.valuetype)
        {
        [[likely]]case VALUE_TYPE_INTEGER:
            try {
                sstr << std::get<int>(node.var); // access by type
                tinyxml2::XMLElement* newelement = doc.NewElement(node.nodename.c_str());
                tinyxml2::XMLText* newtext = doc.NewText(sstr.str().c_str());
                root->InsertEndChild(newelement);
                newelement->InsertEndChild(newtext);
            }
            catch (const std::bad_variant_access& e) { // in case a wrong type/index is used
                cout << "Failed to get the value" << endl;
            }
            break;
        [[likely]]case VALUE_TYPE_DOUBLE:
            try {
                sstr << std::get<double>(node.var); // access by type
                tinyxml2::XMLElement* newelement = doc.NewElement(node.nodename.c_str());
                tinyxml2::XMLText* newtext = doc.NewText(sstr.str().c_str());
                root->InsertEndChild(newelement);
                newelement->InsertEndChild(newtext);
            }
            catch (const std::bad_variant_access& e) { // in case a wrong type/index is used
                cout << "Failed to get the value" << endl;
            }
            break;
        [[likely]]case VALUE_TYPE_STRING:
            try {
                sstr << std::get<string>(node.var); // access by type
                tinyxml2::XMLElement* newelement = doc.NewElement(node.nodename.c_str());
                tinyxml2::XMLText* newtext = doc.NewText(sstr.str().c_str());
                root->InsertEndChild(newelement);
                newelement->InsertEndChild(newtext);
            }
            catch (const std::bad_variant_access& e) { // in case a wrong type/index is used
                cout << "Failed to get the value" << endl;
            }
            break;
        [[likely]]case VALUE_TYPE_BOOLEAN:
            try {
                sstr << boolstr[std::get<bool>(node.var)]; // access by type
                tinyxml2::XMLElement* newelement = doc.NewElement(node.nodename.c_str());
                tinyxml2::XMLText* newtext = doc.NewText(sstr.str().c_str());
                root->InsertEndChild(newelement);
                newelement->InsertEndChild(newtext);
            }
            catch (const std::bad_variant_access& e) { // in case a wrong type/index is used
                cout << "Failed to get the value" << endl;
            }
            break;
        [[unlikely]]default:
            break;
        }

        sstr.clear();
    }

    for (vector<MinecraftServerInstance>::iterator it = serverlist.begin(); it < serverlist.end(); it++) {
        tinyxml2::XMLElement* newelem = doc.NewElement("MinecraftServer");
        string temp;
        switch (it->GetServerType())
        {
        [[likely]]case SERVER_TYPE_VANILLA:
            temp = "vanilla";
            break;
        [[likely]] case SERVER_TYPE_FORGE:
            temp = "forge";
            break;
        [[likely]] case SERVER_TYPE_BUKKIT:
            temp = "bukkit";
            break;
        [[likely]] case SERVER_TYPE_BUKKIT14:
            temp = "bukkit14";
            break;
        [[likely]] case SERVER_TYPE_BUNGEECORD:
            temp = "bungeecord";
            break;
        [[likely]] case SERVER_TYPE_WATERFALL:
            temp = "waterfall";
            break;
        [[likely]] case SERVER_TYPE_CAT:
            temp = "cat";
            break;
        [[likely]]case SERVER_TYPE_BETA18:
            temp = "beta18";
            break;
        [[unlikely]]default:
            temp = "undef";
            break;
        }
        newelem->SetAttribute("type", temp.c_str());

        temp.clear();
        if (it->GetStartupType() == STARTUP_TYPE_JAR) temp = "jar";
        else temp = "bat";
        newelem->SetAttribute("startuptype", temp.c_str());

        temp.clear();
        if (it->GetAutoStart()) temp = "true";
        else temp = "false";
        newelem->SetAttribute("autostart", temp.c_str());

        temp.clear();
        if (it->GetVisibility()) temp = "true";
        else temp = "false";
        newelem->SetAttribute("outputvisibility", temp.c_str());

        tinyxml2::XMLElement* newchild = newelem->InsertNewChildElement("ServerName");
        newchild->SetText(it->GetServerName().c_str());

        newchild = newelem->InsertNewChildElement("ServerDirectory");
        newchild->SetText(it->GetServerDirectory().c_str());

        newchild = newelem->InsertNewChildElement("JVMDirectory");
        newchild->SetText(it->GetJVMDirectory().c_str());

        newchild = newelem->InsertNewChildElement("JVMOption");
        newchild->SetText(it->GetJVMOption().c_str());

        newchild = newelem->InsertNewChildElement("ServerFileName");
        newchild->SetText(it->GetServerFileName().c_str());

        newchild = newelem->InsertNewChildElement("MaxMemory");
        newchild->SetText(it->GetMaxmem().c_str());

        newchild = newelem->InsertNewChildElement("MinMemory");
        newchild->SetText(it->GetMinmem().c_str());
    }

    if (auto ret = doc.SaveFile(CFG_FILENAME); ret != 0) {
        cout << "Failed to save config file" << endl;
        return -1;
    }

    return 0;
}

[[nodiscard("Ignoring return value may cause invaild attribute value.")]]
int _stdcall readCfg() {
    spdlog::debug("Reading config file...");

    tinyxml2::XMLDocument config;
    tinyxml2::XMLElement* pRootEle;
    tinyxml2::XMLElement* servernode;
    tinyxml2::XMLElement* servernodechild;
    tinyxml2::XMLAttribute* attr;
    bool tempbool;
    stringstream sstr;
    string str;
    
    auto ret = config.LoadFile(CFG_FILENAME);

    if (ret != 0) {
         int iret = CreateConfigFile();
         return readCfg();
    }
    
    if (pRootEle = config.RootElement(); pRootEle == NULL) {
        return -1;
    }

    for (auto node = _confignodes_.begin(); node < _confignodes_.end(); node ++)
    {
        if (node->valuetype != VALUE_TYPE_BOOLEAN) {
            string temp = gnsbn(node->nodename);
            istringstream iss(temp);
            switch (node->valuetype)
            {
            case VALUE_TYPE_INTEGER:
                int itemp;
                iss >> itemp;
                node->var.emplace<VALUE_TYPE_INTEGER>(itemp);
                break;
            case VALUE_TYPE_DOUBLE:
                double dtemp;
                iss >> dtemp;
                node->var.emplace<VALUE_TYPE_DOUBLE>(dtemp);
                break;
            case VALUE_TYPE_STRING:
                node->var.emplace<VALUE_TYPE_STRING>(temp);
                break;
            default:
                break;
            }
        }
        else if (node->valuetype == VALUE_TYPE_BOOLEAN) {
            string temp = gnsbn(node->nodename);
            bool tempbool;
            istringstream(temp) >> boolalpha >> tempbool;
            if (temp == "True") {
                node->var.emplace<VALUE_TYPE_BOOLEAN>(tempbool);
           } 
            else {
                node->var.emplace<VALUE_TYPE_BOOLEAN>(tempbool);
            }
        }
    }

    servernode = pRootEle->FirstChildElement("MinecraftServer");
    servernodechild = servernode->FirstChildElement("ServerName");

    if (servernode == NULL)return -1;
    while (servernode) {
        MinecraftServerInstance tempins;
        ZeroMemory(&tempins, sizeof(tempins));

        attr = const_cast<tinyxml2::XMLAttribute*>(servernode->FindAttribute("type"));
        if (attr)
            if (attr->Value()) {
                str = attr->Value();
                if (str == "vanilla")       tempins.SetServerType(SERVER_TYPE_VANILLA);
                if (str == "forge")         tempins.SetServerType(SERVER_TYPE_FORGE);
                if (str == "bukkit")        tempins.SetServerType(SERVER_TYPE_BUKKIT);
                if (str == "bukkit14")      tempins.SetServerType(SERVER_TYPE_BUKKIT14);
                if (str == "bungeecord")    tempins.SetServerType(SERVER_TYPE_BUNGEECORD);
                if (str == "waterfall")     tempins.SetServerType(SERVER_TYPE_WATERFALL);
                if (str == "cat")           tempins.SetServerType(SERVER_TYPE_CAT);
                if (str == "beta18")        tempins.SetServerType(SERVER_TYPE_BETA18);
            }

        attr = const_cast<tinyxml2::XMLAttribute*>(servernode->FindAttribute("startuptype"));
        if (attr)
            if (attr->Value()) {
                str = attr->Value();
                if (str == "jar")           tempins.SetStartupType(STARTUP_TYPE_JAR);
                if (str == "bat")           tempins.SetStartupType(STARTUP_TYPE_BAT);
            }

        attr = const_cast<tinyxml2::XMLAttribute*>(servernode->FindAttribute("autostart"));
        istringstream(attr->Value()) >> boolalpha >> tempbool;
        tempins.SetAutoStart(tempbool);
        
        attr = const_cast<tinyxml2::XMLAttribute*>(servernode->FindAttribute("outputvisibility"));
        istringstream(attr->Value()) >> boolalpha >> tempbool;
        tempins.SetVisibility(tempbool);
        
        servernodechild = servernode->FirstChildElement("ServerName");
        if(servernodechild)
            if (servernodechild->GetText()) { 
                tempins.SetServerName(servernodechild->GetText()); 
            }

        servernodechild = servernode->FirstChildElement("ServerDirectory");
        if (servernodechild)
            if (servernodechild->GetText()) { 
                tempins.SetServerDirectory(servernodechild->GetText());
        }

        servernodechild = servernode->FirstChildElement("JVMDirectory");
        if (servernodechild)
            if (servernodechild->GetText()) { 
                tempins.SetJVMDirectory(servernodechild->GetText()); 
            }

        servernodechild = servernode->FirstChildElement("JVMOption");
        if (servernodechild)
            if (servernodechild->GetText()) { 
                tempins.SetJVMOption(servernodechild->GetText()); 
            }

        servernodechild = servernode->FirstChildElement("ServerFileName");
        if (servernodechild)
            if (servernodechild->GetText()) { 
                tempins.SetServerFileName(servernodechild->GetText()); 
            }

        servernodechild = servernode->FirstChildElement("MaxMemory");
        if (servernodechild)
            if (servernodechild->GetText()) { 
                tempins.SetMaxmem(servernodechild->GetText()); 
            }

        servernodechild = servernode->FirstChildElement("MinMemory");
        if (servernodechild)
            if (servernodechild->GetText()) { 
                tempins.SetMinmem(servernodechild->GetText()); 
            }


        serverlist.push_back(move(tempins));
        servernode = servernode->NextSiblingElement("MinecraftServer");
    }
    cout << "Done." << endl;
    return 0;
}

int _stdcall Config() {
    ADD_CONFIG_NODE("EnableTimeStamp", EnableTimeStamp, VALUE_TYPE_BOOLEAN, true);
    ADD_CONFIG_NODE("Language", Language, VALUE_TYPE_INTEGER, 0);
    ADD_CONFIG_NODE("PluginDirectory", PluginDirectory, VALUE_TYPE_STRING, "plugins");
    ADD_CONFIG_NODE("MaxQueue", MaxQueue, VALUE_TYPE_INTEGER, 2048);
    
    if (auto ret = readCfg(); ret == -1) {
        cout << "Failed to read the config file" << endl;
        return -1;
    }
    return 0;
}
#pragma endregion

#pragma region Main
int _stdcall main()
{
    SetConsoleTitleA(PROJECT_NAME_STR);

    string pns = PROJECT_NAME_STR;
    pns.append(" ").append(PROJECT_VER_STR).append(" ").append(PROJECT_DEVSTAT);
    cout << pns << endl;
    spdlog::info("Welcome to spdlog!");
    spdlog::error("Some error message with arg: {}", 1);

    spdlog::warn("Easy padding in numbers like {:08d}", 12);
    spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    spdlog::info("Support for floats {:03.2f}", 1.23456);
    spdlog::info("Positional args are {1} {0}..", "too", "supported");
    spdlog::info("{:<30}", "left aligned");

    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    spdlog::debug("This message should be displayed..");
    

    if (auto ret = Config(); ret != 0) {
        print("Failed to read config");
        return -1;
    }
#undef ins
    for (auto ins : serverlist) {
        int ret;
        if (ins.GetAutoStart()) {
            cout << "Starting Minecraft Server : " << ins.GetServerName() << endl;
            ret = ins.StartServer();
            cout << "Started with return code : " << ret << endl;
        }
        else {
            continue;
        }
        if (ret != 0) {
            cout << "Error starting Minecraft server : " << ins.GetServerName() << endl;
        }
    }
    
    vector<string> cmdcompletions{
        "help", 

        "cmdqueue", 
        "add", "remove", "start", "stop", "pause", "rename", "status", "list", "reload", "load", "query", "delete", "insert",// "setattr"


        "config", 
        "save", "setattr",//"reload"

        "permission", 
        "set",//"reload", "save", "query", "list", "remove"

        "extensions", 
        "unload", "enable", "disable",//, "list", "reload", "load"

        "server", 
        "setdefault", "restart", "stop", "rcon"//, "setattr", "status", "start"
    };

    vector<pair<string, Replxx::Color>> cmdcolors{
        {"help", Replxx::Color::BRIGHTMAGENTA},
        {"cmdqueue", Replxx::Color::BRIGHTMAGENTA},
        {"permission", Replxx::Color::BRIGHTMAGENTA},
        {"extensions", Replxx::Color::BRIGHTMAGENTA},
        {"server", Replxx::Color::BRIGHTMAGENTA},
        {"config", Replxx::Color::BRIGHTMAGENTA},

        {"add", Replxx::Color::YELLOW},
        {"remove", Replxx::Color::YELLOW},
        {"start", Replxx::Color::YELLOW},
        {"stop", Replxx::Color::YELLOW},
        {"pause", Replxx::Color::YELLOW},
        {"rename", Replxx::Color::YELLOW},
        {"status", Replxx::Color::YELLOW},
        {"list", Replxx::Color::YELLOW},
        {"reload", Replxx::Color::YELLOW},
        {"load", Replxx::Color::YELLOW},
        {"query", Replxx::Color::YELLOW},
        {"delete", Replxx::Color::YELLOW},
        {"insert", Replxx::Color::YELLOW},
        {"save", Replxx::Color::YELLOW},
        {"setattr", Replxx::Color::YELLOW},
        {"set", Replxx::Color::YELLOW},
        {"unload", Replxx::Color::YELLOW},
        {"enable", Replxx::Color::YELLOW},
        {"disable", Replxx::Color::YELLOW},
        {"setdefault", Replxx::Color::YELLOW},
        {"restart", Replxx::Color::YELLOW},
        {"stop", Replxx::Color::YELLOW},
        {"rcon", Replxx::Color::YELLOW},

        {"[\\-|+]{0,1}[0-9]+", Replxx::Color::BRIGHTGREEN},
        {"[\\-|+]{0,1}[0-9]*\\.[0-9]+", Replxx::Color::BRIGHTGREEN},
        {"[\\-|+]{0,1}[0-9]+e[\\-|+]{0,1}[0-9]+", Replxx::Color::BRIGHTGREEN}
    };
    Replxx rx;
    rx.install_window_change_handler();
    rx.set_word_break_characters(" \t.,-%!;:=*~^'\"/?<>|[](){}");
    rx.set_completion_callback(bind(&hook_completion, placeholders::_1, placeholders::_2, cmdcompletions));
    rx.set_hint_callback(bind(&hook_hint, placeholders::_1, placeholders::_2, placeholders::_3, cmdcompletions));
    rx.set_highlighter_callback(bind(&hook_color, placeholders::_1, placeholders::_2, cmdcolors));

    rx.bind_key_internal(Replxx::KEY::BACKSPACE, "delete_character_left_of_cursor");
    rx.bind_key_internal(Replxx::KEY::DELETE, "delete_character_under_cursor");
    rx.bind_key_internal(Replxx::KEY::LEFT, "move_cursor_left");
    rx.bind_key_internal(Replxx::KEY::RIGHT, "move_cursor_right");
    rx.bind_key_internal(Replxx::KEY::UP, "history_previous");
    rx.bind_key_internal(Replxx::KEY::DOWN, "history_next");
    rx.bind_key_internal(Replxx::KEY::PAGE_UP, "history_first");
    rx.bind_key_internal(Replxx::KEY::PAGE_DOWN, "history_last");
    rx.bind_key_internal(Replxx::KEY::HOME, "move_cursor_to_begining_of_line");
    rx.bind_key_internal(Replxx::KEY::END, "move_cursor_to_end_of_line");
    rx.bind_key_internal(Replxx::KEY::TAB, "complete_line");
    rx.bind_key_internal(Replxx::KEY::control(Replxx::KEY::LEFT), "move_cursor_one_word_left");
    rx.bind_key_internal(Replxx::KEY::control(Replxx::KEY::RIGHT), "move_cursor_one_word_right");
    rx.bind_key_internal(Replxx::KEY::control(Replxx::KEY::UP), "hint_previous");
    rx.bind_key_internal(Replxx::KEY::control(Replxx::KEY::DOWN), "hint_next");
    rx.bind_key_internal(Replxx::KEY::control(Replxx::KEY::ENTER), "commit_line");
    rx.bind_key_internal(Replxx::KEY::control('R'), "history_incremental_search");
    rx.bind_key_internal(Replxx::KEY::control('W'), "kill_to_begining_of_word");
    rx.bind_key_internal(Replxx::KEY::control('U'), "kill_to_begining_of_line");
    rx.bind_key_internal(Replxx::KEY::control('K'), "kill_to_end_of_line");
    rx.bind_key_internal(Replxx::KEY::control('Y'), "yank");
    rx.bind_key_internal(Replxx::KEY::control('L'), "clear_screen");
    rx.bind_key_internal(Replxx::KEY::control('D'), "send_eof");
    rx.bind_key_internal(Replxx::KEY::control('C'), "abort_line");
    rx.bind_key_internal(Replxx::KEY::control('T'), "transpose_characters");
    TCHAR  infoBuf[32767];
    DWORD  bufCharCount = 32767;
    GetComputerNameA(infoBuf, &bufCharCount);
    ostringstream str;
    str << "[Helium@" << infoBuf << "] #";
    while (true) {
        string inputcmd = rx.input(str.str().c_str());
        cout << inputcmd << endl;
    }

    system("pause");
}
#pragma endregion