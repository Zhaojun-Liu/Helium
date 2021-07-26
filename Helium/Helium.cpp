#pragma region Includes
//不要随意调换include顺序 awa

#define _SILENCE_CXX17_STRSTREAM_DEPRECATION_WARNING


#include<iostream>
#include<Windows.h>
#include<sstream>

#include"logger.h"
#include"tinyxml2.h"
#include"parse.h"
#include"xmlutils.h"
#include"xmlmacros.h"
#include "confuses.h"
using namespace std;

#pragma endregion

#pragma region Macros
#define PROJECT_NAME_STR "Helium"
#define PROJECT_VER_STR "0.4.0"
#define PROJECT_DEVSTAT "Pre-Alpha"

#define CFG_FILENAME "HeliumConfig.xml"
#define gnsbn(name) DuN(pRootEle,name);
#pragma endregion

#pragma region Constants
#define print(a) std::cout<< a << endl;

#pragma endregion

#pragma region Types
typedef SsS (*pOnload)(int, int, void*);



#pragma endregion

#pragma region Var
AeX logger;
hCr xms, xmx, serverdir, serverjar, plugindir, lang, handler, enabletimestamp, jvmoption, serveroption, zheshiyigelinshibianliangbuyaoshanchuxiexie;

#pragma endregion

#pragma region Server

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
START_CONFIG_NODES_REGISTER(ConfigNode);

int readCfg() {

    ADD_CONFIG_NODE("ServerMaxMem", ServerMaxMem, VALUE_TYPE_INTEGER);
    ADD_CONFIG_NODE("ServerMinMem", ServerMinMem, VALUE_TYPE_INTEGER);
    ADD_CONFIG_NODE("ServerDirectory", ServerDirectory, VALUE_TYPE_STRING);
    ADD_CONFIG_NODE("ServerJarName", ServerJarName, VALUE_TYPE_STRING);
    ADD_CONFIG_NODE("JvmOption", JvmOption, VALUE_TYPE_STRING);
    ADD_CONFIG_NODE("Handler", Handler, VALUE_TYPE_INTEGER);
    ADD_CONFIG_NODE("EnableTimeStamp", EnableTimeStamp, VALUE_TYPE_BOOLEAN);
    ADD_CONFIG_NODE("Language", Language, VALUE_TYPE_INTEGER);
    ADD_CONFIG_NODE("PluginDirectory", PluginDirectory, VALUE_TYPE_STRING);
    ADD_CONFIG_NODE("MaxQueue", MaxQueue, VALUE_TYPE_INTEGER);
    ADD_CONFIG_NODE("ServerWorkingDirectory", ServerWorkingDirectory, VALUE_TYPE_STRING)

    tinyxml2::XMLDocument config;
    tinyxml2::XMLElement* pRootEle;
    
    if (!config.LoadFile(CFG_FILENAME)) {
        CreateConfigFile();
    }
    pRootEle = config.RootElement();
    if (pRootEle == NULL) {
        return -114514;
    }
    for (vector<ConfigNode>::iterator it = _confignodes_.begin(); it <= _confignodes_.end(); it++) {
        switch (it->valuetype)
        {
        case VALUE_TYPE_BOOLEAN:
            break;
        case VALUE_TYPE_DOUBLE:
            break;
        case VALUE_TYPE_INTEGER:
            break;
        case VALUE_TYPE_STRING:
            break;
        default:
            break;
        }
    }
    return 0;
}
#pragma endregion


#pragma region Main
int main()
{
    SetConsoleTitle(PROJECT_NAME_STR);
    string pns = PROJECT_NAME_STR;
    pns.append(" ").append(PROJECT_VER_STR).append(" ").append(PROJECT_DEVSTAT);
    cout << pns << endl;
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

    auto ret = readCfg();

    system("pause");
}
#pragma endregion