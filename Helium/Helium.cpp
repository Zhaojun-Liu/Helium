#pragma region Includes
//不要随意调换include顺序 awa

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<Windows.h>
#include<thread>
#include<strstream>
#include<functional>

#include"confuses.h"
#include"logger.h"
#include"tinyxml2.h"
#include"parse.h"
#include"xmlutils.h"
#include"xmlmacros.h"
#include"minecraftserver.h"

#define REPLXX_STATIC

#include"replxx/replxx.hxx"

using namespace std;
using namespace replxx;

#pragma endregion

#pragma region Macros
#define PROJECT_NAME_STR "Helium"
#define PROJECT_VER_STR "0.4.2.02"
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
vector<MinecraftServerInstance> serverlist;
#pragma endregion

#pragma region Callback

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

#pragma endregion

#pragma region Config

[[nodiscard("Do not discard return value of SaveConfigFile() plz")]]
int SaveConfigFile() {
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
int CreateConfigFile()
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
int readCfg() {
    cout << "Enter readCfg()" << endl;

    tinyxml2::XMLDocument config;
    tinyxml2::XMLElement* pRootEle;
    tinyxml2::XMLElement* servernode;
    tinyxml2::XMLElement* servernodechild;
    tinyxml2::XMLAttribute* attr;
    bool tempbool;
    stringstream sstr;
    
    auto ret = config.LoadFile(CFG_FILENAME);

    if (ret != 0) {
        return CreateConfigFile();
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
            
        if (strcmp(attr->Value(), "vanilla"))       tempins.SetServerType(SERVER_TYPE_VANILLA);
        if (strcmp(attr->Value(), "forge"))         tempins.SetServerType(SERVER_TYPE_FORGE);
        if (strcmp(attr->Value(), "bukkit"))        tempins.SetServerType(SERVER_TYPE_BUKKIT);
        if (strcmp(attr->Value(), "bukkit14"))      tempins.SetServerType(SERVER_TYPE_BUKKIT14);
        if (strcmp(attr->Value(), "bungeecord"))    tempins.SetServerType(SERVER_TYPE_BUNGEECORD);
        if (strcmp(attr->Value(), "waterfall"))     tempins.SetServerType(SERVER_TYPE_WATERFALL);
        if (strcmp(attr->Value(), "cat"))           tempins.SetServerType(SERVER_TYPE_CAT);
        if (strcmp(attr->Value(), "beta18"))        tempins.SetServerType(SERVER_TYPE_BETA18);
        attr = const_cast<tinyxml2::XMLAttribute*>(servernode->FindAttribute("startuptype"));
        
        if (strcmp(attr->Value(), "jar"))           tempins.SetStartupType(STARTUP_TYPE_JAR);
        if (strcmp(attr->Value(), "bat"))           tempins.SetStartupType(STARTUP_TYPE_BAT);
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
                print(servernodechild->GetText())
            }

        servernodechild = servernode->FirstChildElement("ServerDirectory");
        if (servernodechild)
            if (servernodechild->GetText()) { 
                tempins.SetServerDirectory(servernodechild->GetText());
                print(servernodechild->GetText())
        }

        servernodechild = servernode->FirstChildElement("JVMDirectory");
        if (servernodechild)
            if (servernodechild->GetText()) { 
                tempins.SetJVMDirectory(servernodechild->GetText()); 
                print(servernodechild->GetText())
            }

        servernodechild = servernode->FirstChildElement("JVMOption");
        if (servernodechild)
            if (servernodechild->GetText()) { 
                tempins.SetJVMOption(servernodechild->GetText()); 
                print(servernodechild->GetText())
            }

        servernodechild = servernode->FirstChildElement("ServerFileName");
        if (servernodechild)
            if (servernodechild->GetText()) { 
                tempins.SetServerFileName(servernodechild->GetText()); 
                print(servernodechild->GetText())
            }

        servernodechild = servernode->FirstChildElement("MaxMemory");
        if (servernodechild)
            if (servernodechild->GetText()) { 
                tempins.SetMaxmem(servernodechild->GetText()); 
                print(servernodechild->GetText())
            }

        servernodechild = servernode->FirstChildElement("MinMemory");
        if (servernodechild)
            if (servernodechild->GetText()) { 
                tempins.SetMinmem(servernodechild->GetText()); 
                print(servernodechild->GetText())
            }


        serverlist.push_back(move(tempins));
        servernode = servernode->NextSiblingElement("MinecraftServer");
    }
    print("exiting readCfg()");
    return 0;
}

int Config() {
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

#pragma region replxxfuncs
int utf8str_codepoint_len(char const* s, int utf8len) {
    int codepointLen = 0;
    unsigned char m4 = 128 + 64 + 32 + 16;
    unsigned char m3 = 128 + 64 + 32;
    unsigned char m2 = 128 + 64;
    for (int i = 0; i < utf8len; ++i, ++codepointLen) {
        char c = s[i];
        if ((c & m4) == m4) {
            i += 3;
        }
        else if ((c & m3) == m3) {
            i += 2;
        }
        else if ((c & m2) == m2) {
            i += 1;
        }
    }
    return (codepointLen);
}

int context_len(char const* prefix) {
    char const wb[] = " \t\n\r\v\f-=+*&^%$#@!,./?<>;:`~'\"[]{}()\\|";
    int i = (int)strlen(prefix) - 1;
    int cl = 0;
    while (i >= 0) {
        if (strchr(wb, prefix[i]) != NULL) {
            break;
        }
        ++cl;
        --i;
    }
    return (cl);
}

Replxx::completions_t 
ReplxxCompletionCallback(std::string const& context, int& contextLen, std::vector<std::string> const& comp) {
    Replxx::completions_t completions;
    int utf8ContextLen(context_len(context.c_str()));
    int prefixLen(static_cast<int>(context.length()) - utf8ContextLen);
    if ((prefixLen > 0) && (context[prefixLen - 1] == '\\')) {
        --prefixLen;
        ++utf8ContextLen;
    }
    contextLen = utf8str_codepoint_len(context.c_str() + prefixLen, utf8ContextLen);

    std::string prefix{ context.substr(prefixLen) };
    if (prefix == "\\pi") {
        completions.push_back("π");
    }
    else {
        for (auto const& e : comp) {
            if (e.compare(0, prefix.size(), prefix) == 0) {
                Replxx::Color c(Replxx::Color::DEFAULT);
                if (e.find("brightred") != std::string::npos) {
                    c = Replxx::Color::BRIGHTRED;
                }
                else if (e.find("red") != std::string::npos) {
                    c = Replxx::Color::RED;
                }
                completions.emplace_back(e.c_str(), c);
            }
        }
    }

    return completions;
}
#pragma endregion

#pragma region Main
int main()
{
    SetConsoleTitleA(PROJECT_NAME_STR);
    string pns = PROJECT_NAME_STR;
    pns.append(" ").append(PROJECT_VER_STR).append(" ").append(PROJECT_DEVSTAT);
    cout << pns << endl;

    Replxx rx;
    rx.install_window_change_handler();

    vector<string> commands{
        ".helium", "help"
    };
    string heliumhistory = ".\\helium_history.txt";
    rx.history_load(heliumhistory);
    rx.set_max_history_size(128);
    rx.set_max_hint_rows(3);

    using namespace placeholders;
    rx.set_completion_callback(std::bind(&ReplxxCompletionCallback, _1, _2, cref(commands)));

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

    if (auto ret = Config(); ret != 0) {
        print("Failed to read config");
        return -1;
    }

    for (auto ins : serverlist) {
        ins.Print();
        int ret;
        if (ins.GetAutoStart()) {
            cout << "Starting Minecraft Server : " << ins.GetServerName() << endl;
            ret = ins.StartServer();
        }
        else {
            continue;
        }
        if (ret != 0) {
            cout << "Error starting Minecraft server : " << ins.GetServerName() << endl;
        }
    }

    while (true) {
        string cmdinput = rx.input("Helium>");
        cout << "User input : " << cmdinput << endl;
    }

    system("pause");
}
#pragma endregion