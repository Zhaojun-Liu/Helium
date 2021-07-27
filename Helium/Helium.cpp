#pragma region Includes
//不要随意调换include顺序 awa

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#include<iostream>
#include<Windows.h>
#include<strstream>

#include"confuses.h"
#include"logger.h"
#include"tinyxml2.h"
#include"parse.h"
#include"xmlutils.h"
#include"xmlmacros.h"

using namespace std;

#pragma endregion

#pragma region Macros
#define PROJECT_NAME_STR "Helium"
#define PROJECT_VER_STR "0.4.1.01"
#define PROJECT_DEVSTAT "Pre-Alpha"

#define CFG_FILENAME "HeliumConfig.xml"
#define gnsbn(name) DuN(pRootEle,name)
START_CONFIG_NODES_REGISTER(ConfigNode);
#pragma endregion

#pragma region Constants
#define print(a) std::cout<< a << endl;

#pragma endregion

#pragma region Types
typedef SsS (*pOnload)(int, int, void*);

struct RedirectInformation
{

    HANDLE hStdInRead = NULL;   //子进程用的stdin的读入端  
    HANDLE hStdInWrite = NULL;  //主程序用的stdin的读入端 

    HANDLE hStdOutRead = NULL;  //主程序用的stdout的读入端  
    HANDLE hStdOutWrite = NULL; //子进程用的stdout的写入端  

    HANDLE hStdErrWrite = NULL; //子进程用的stderr的写入端  

    RedirectInformation& operator=(RedirectInformation& a) {
        if (this != &a)
        {
            this->hStdErrWrite = a.hStdErrWrite;
            this->hStdInRead = a.hStdInRead;
            this->hStdInWrite = a.hStdInWrite;
            this->hStdOutRead = a.hStdOutRead;
            this->hStdOutWrite = a.hStdOutWrite;
            return *this;
        }
        else
        {
            exception e;
            throw e;
        }
    }
};

#pragma endregion

#pragma region Var
Logger logger;
#pragma endregion

#pragma region Server
/*
[[nodiscard("你他妈做个返回值检查有那么难吗")]]
int LaunchMinecraftServer() {
    int maxmem, minmem;
    string jvmpath, serverdir, serverjarname, jvmoption;
    for (auto node : _confignodes_) {
        if (node.nodename == "JvmDirectory") {

        }
    }
    HANDLE hStdInRead = NULL;   //子进程用的stdin的读入端  
    HANDLE hStdInWrite = NULL;  //主程序用的stdin的读入端 
    HANDLE hStdOutRead = NULL;  //主程序用的stdout的读入端  
    HANDLE hStdOutWrite = NULL; //子进程用的stdout的写入端  
    HANDLE hStdErrWrite = NULL; //子进程用的stderr的写入端  

    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    SECURITY_ATTRIBUTES sa;
    RedirectInformation inf;

    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

    unsigned int serverexitcode = 0;

    //产生一个用于stdin的管道，得到两个HANDLE:  hStdInRead用于子进程读出数据，hStdInWrite用于主程序写入数据  
    //其中saAttr是一个STARTUPINFO结构体，定义见CreatePipe函数说明  
    if (!CreatePipe(&hStdInRead, &hStdInWrite, &sa, 0))
        return -1;
    //产生一个用于stdout的管道，得到两个HANDLE:  hStdOutRead用于主程序读出数据，hStdOutWrite用于子程序写入数据  
    if (!CreatePipe(&hStdOutRead, &hStdOutWrite, &sa, 0))
        return -1;

    if (hStdInRead == NULL || hStdInWrite == NULL) return -1;
    if (hStdOutRead == NULL || hStdOutWrite == NULL) return -1;

    string startupcmd;
    if (servercmdline.find(".bat") != string::npos || servercmdline.find(".cmd") != string::npos)//判断启动命令是否为bat或cmd文件
    {
        startupcmd = servercmdline;
        dp("startupcmd:" + startupcmd);
    }
    else//不是bat或cmd文件
    {
        vector < string > vecstr = split(servercmdline, " ");//切丝
        startupcmd.append(jvmpath).append(" ");
        string servcmd;
        for (auto i : vecstr)//循环
        {
            if (have(i, ".jar"))
            {
                servcmd.append(servercwd + "\\" + i + " ");//加上服务器jar文件所在目录然后append
            }
            else
            {
                servcmd.append(i + " ");//不含有 .jar 的直接append
            }
            dp("startupcmd:" + startupcmd);
        }
        startupcmd.append(servcmd);
        dp("startupcmd:" + startupcmd);
    }

    LPSTR _startcmd = new char[startupcmd.length() + 1];
    memset(_startcmd, '\0', startupcmd.length() + 1);
    strcat_s(_startcmd, startupcmd.length() + 1, startupcmd.c_str());
    dp("#");
    dp(_startcmd);

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    si.hStdOutput = hStdOutWrite;   //意思是：子进程的stdout输出到hStdOutWrite  
    si.hStdError = hStdErrWrite;    //意思是：子进程的stderr输出到hStdErrWrite  
    si.hStdInput = hStdInRead;
#ifdef DEBUG_FUNC_ENABLE
    si.wShowWindow = SW_SHOW;
#else
    si.wShowWindow = SW_HIDE;
#endif

    // STARTF_USESHOWWINDOW:The wShowWindow member contains additional information.
    // STARTF_USESTDHANDLES:The hStdInput, hStdOutput, and hStdError members contain additional information.
    // from MSDN

    dp(servercwd);

    BOOL bSuc = CreateProcess(NULL
        , _startcmd
        , NULL
        , NULL
        , TRUE
        , CREATE_SUSPENDED
        , NULL
        , servercwd.c_str()
        , &si
        , &pi);

    //CloseHandle(pi.hThread);

    if (bSuc == FALSE) {
        dp("CreateProcess() Failed!");
        return -1;
    }

    inf = *priInformation;

    inf.hStdErrWrite = hStdErrWrite;
    inf.hStdInRead = hStdInRead;
    inf.hStdInWrite = hStdInWrite;
    inf.hStdOutRead = hStdOutRead;
    inf.hStdOutWrite = hStdOutWrite;

    thread ServerOut(ServerSTDOUT, inf, pi.hProcess);
    ServerOut.detach();

    if (ResumeThread(pi.hThread) == -1) {
        redout.error("Cannot Start Minecraft Server!");
        TerminateProcess(pi.hProcess, serverexitcode);
        return -1;
    }

    dp("##############################################");
    delete[] _startcmd;
    _startcmd = NULL;
    dp("###############################################");

    writeinf = inf;

    return 0;
    return 0;
}
*/
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
            if (temp == "True") {
                node->var.emplace<VALUE_TYPE_BOOLEAN>(true);
            }
            else {
                node->var.emplace<VALUE_TYPE_BOOLEAN>(false);
            }
        }
    }

    return 0;
}

int Config() {
    ADD_CONFIG_NODE("ServerMaxMem", ServerMaxMem, VALUE_TYPE_INTEGER, 1024);
    ADD_CONFIG_NODE("ServerMinMem", ServerMinMem, VALUE_TYPE_INTEGER, 1024);
    ADD_CONFIG_NODE("ServerDirectory", ServerDirectory, VALUE_TYPE_STRING, "server");
    ADD_CONFIG_NODE("ServerJarName", ServerJarName, VALUE_TYPE_STRING, "server.jar");
    ADD_CONFIG_NODE("JvmOption", JvmOption, VALUE_TYPE_STRING, "-jar");
    ADD_CONFIG_NODE("Handler", Handler, VALUE_TYPE_INTEGER, 0);
    ADD_CONFIG_NODE("EnableTimeStamp", EnableTimeStamp, VALUE_TYPE_BOOLEAN, true);
    ADD_CONFIG_NODE("Language", Language, VALUE_TYPE_INTEGER, 0);
    ADD_CONFIG_NODE("PluginDirectory", PluginDirectory, VALUE_TYPE_STRING, "plugins");
    ADD_CONFIG_NODE("MaxQueue", MaxQueue, VALUE_TYPE_INTEGER, 2048);
    string jvmpath = getenv("JAVA_HOME");
    jvmpath.append("bin\\javaw.exe");
    ADD_CONFIG_NODE("JvmDirectory", JvmDirectory, VALUE_TYPE_STRING, jvmpath);
    if (auto ret = readCfg(); ret == -1) {
        cout << "Failed to read the config file" << endl;
        return -1;
    }
    return 0;
}
#pragma endregion


#pragma region Main
int main()
{
    SetConsoleTitleA(PROJECT_NAME_STR);
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

    Config();

    system("pause");
}
#pragma endregion