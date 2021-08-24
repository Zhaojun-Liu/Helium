#pragma region Includes
//不要随意调换include顺序 awa

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<Windows.h>
#include<thread>
#include<strstream>
#include<regex>
#include<functional>

#include"logger.h"
#include"tinyxml2.h"
#include"parse.h"
#include"xmlutils.h"
#include"config.h"
#include"minecraftserver.h"
#include"extension.h"

#include<spdlog/spdlog.h>
#define REPLXX_STATIC
#include"replxx/replxx.hxx"

using namespace std;
using namespace replxx;
int  _stdcall ProcessServerOutput(MinecraftServerInstance*, string, HANDLE, HANDLE);
#pragma endregion

#pragma region Macros

/*
附注:此处版本号默认遵守 https://semver.org/lang/zh-CN/ 语义化版本控制规规范2.0.0
版本格式：主版本号.次版本号.修订号，版本号递增规则如下：

主版本号：当你做了不兼容的 API 修改，
次版本号：当你做了向下兼容的功能性新增，
修订号：当你做了向下兼容的问题修正。
先行版本号及版本编译信息可以加到“主版本号.次版本号.修订号”的后面，作为延伸。(摘自semver.org)
*/

#define PROJECT_NAME_STR "Helium"
#define PROJECT_VER_STR "0.4.7"
#define PROJECT_DEVSTAT "Pre-Alpha"
#define pass continue;
#pragma endregion

#pragma region Constants
#define print(a) std::cout<< a << endl;
#pragma endregion

#pragma region Types

#pragma endregion

#pragma region Var
Logger logger;
map<string, HeliumExtension> extensions;
string pns = PROJECT_NAME_STR;
Replxx rx;
vector<MinecraftServerInstance> serverlist;

#pragma endregion

#pragma region ServerFunc

int _stdcall ReadServerFile() {
    tinyxml2::XMLDocument doc;
    auto error = doc.LoadFile(SERVER_FILENAME);
    if (error != tinyxml2::XMLError::XML_SUCCESS) {
        spdlog::critical("Cannot read server.xml");
        return -1;
    }

    tinyxml2::XMLElement* root = doc.RootElement();
    tinyxml2::XMLElement* servernode;
    tinyxml2::XMLElement* servernodechild;
    tinyxml2::XMLAttribute* attr;

    string str;
    bool tempbool;

    servernode = root->FirstChildElement("MinecraftServer");
    servernodechild = servernode->FirstChildElement("ServerName");

    if (servernode == NULL) {
        spdlog::critical("Failed to get the root element of the server.xml.");
        return -1;
    }

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
        if (servernodechild)
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

    return 0;
}
int _stdcall SaveServerFile() {
    tinyxml2::XMLDocument doc;
    auto dec = doc.NewDeclaration("<?xml version=\"1.0\"?>");
    doc.InsertEndChild(dec);

    auto root = doc.NewElement("HeliumServerConfig");

    if (root == NULL) {
        spdlog::error("Cannot create root element for server.xml.");
        return -1;
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

    auto error = doc.SaveFile(SERVER_FILENAME);
    if (error != tinyxml2::XMLError::XML_SUCCESS) {
        spdlog::error("Cannot save server.xml.");
        return -1;
    }

    return 0;
}
int _stdcall CreateServerFile() {
    tinyxml2::XMLDocument doc;
    auto dec = doc.NewDeclaration("<?xml version=\"1.0\"?>");
    doc.InsertEndChild(dec);

    auto root = doc.NewElement("HeliumServerConfig");

    if (root == NULL) {
        spdlog::error("Cannot create root element for server.xml.");
        return -1;
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

    auto error = doc.SaveFile(SERVER_FILENAME);
    if (error != tinyxml2::XMLError::XML_SUCCESS) {
        spdlog::error("Cannot save server.xml.");
        return -1;
    }

    return 0;
}
int StartInfoThread(MinecraftServerInstance *lpIns) {
    thread tempthread(ProcessServerOutput, lpIns, lpIns->GetServerName(), lpIns->GetRDInfo().hStdOutRead, lpIns->GetThreadHandle());
    tempthread.detach();
    this_thread::yield();

    spdlog::debug("Output processing thread create successfully at 0x{}","awa");
    return lpIns->GerServerPid();
}
int  _stdcall ProcessServerOutput(MinecraftServerInstance* ptr, string servername, HANDLE stdread, HANDLE hProc) {
    //cout << "Server started at PID : " << ptr->dwPid << endl;
    spdlog::debug("server started at PID:{}", ptr->GerServerPid());
    char out_buffer[BUFSIZE];
    DWORD dwRead;
    bool ret = FALSE;
    DWORD dwCode;
    string read;
    while (true)
    {
        ZeroMemory(out_buffer, BUFSIZE);
        //用WriteFile，从hStdOutRead读出子进程stdout输出的数据，数据结果在out_buffer中，长度为dwRead

        //ret = ReadFile(stdread, out_buffer, BUFSIZE - 1, &dwRead, NULL);
        char ch;
        //spdlog::critical(stdread);
        if (stdread == INVALID_HANDLE_VALUE || stdread == NULL)
            break;
        if (ReadFile(stdread, &ch, 1, &dwRead, NULL) == false)
            break;
        if (dwRead == 0)
        {
            pass;
        }
        if (ch != '\n') {
            read += ch;
            pass;
        }
        else
        {
            if (ptr->GetVisibility())
            {
                spdlog::info("{}->{}", servername, read);
            }
            read = "";
        }

        MSG msg;
        DWORD dwRet = MsgWaitForMultipleObjects(1, ptr->GetThreadPHandle(), FALSE, 20, QS_ALLINPUT);
        switch (dwRet) {
        case WAIT_OBJECT_0:
            break;
            break;
        case WAIT_OBJECT_0 + 1:
            PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
            DispatchMessage(&msg);
            continue;
        default:
            break;
        }
    }

    
    spdlog::info("服务器{0}已退出，返回值{1:d}(0x{1:x})",servername, dwCode);
    cout << "Exiting ProcessServerOutput()" << dwCode << endl;
    ptr->SetServerReturnValue(dwCode);
    ptr->SetServerStatus(1);
    return 114514;
}

#pragma endregion



#pragma region Main

int _stdcall main(int argc,char** argv)
{
    SetConsoleTitleA(PROJECT_NAME_STR);

    pns.append(" ").append(PROJECT_VER_STR).append(" ").append(PROJECT_DEVSTAT);
    cout << pns << endl;
    spdlog::set_level(spdlog::level::debug); // Set global log level to debug   

    if (auto ret = Config(); ret != 0) {
        print("Failed to read config");
        return -1;
    }
#undef ins
    for (auto ins = serverlist.begin(); ins < serverlist.end(); ins++) {
        int ret;
        if (ins->GetAutoStart()) {
            cout << "Starting Minecraft Server : " << ins->GetServerName() << endl;
            ret = ins->StartServer();
            cout << "Started with return code : " << ret << endl;
            StartInfoThread(&(*ins));
        }
        else {
            continue;
        }
        if (ret != 0) {
            cout << "Error starting Minecraft server : " << ins->GetServerName() << endl;
        }
    }
    

    rx.install_window_change_handler();
    rx.set_word_break_characters(" \t.,-%;:=*~^'\"/?<>|[](){}");
    rx.set_completion_callback(hook_completion);
    rx.set_hint_callback(hook_hint);
    rx.set_highlighter_callback(hook_color);
    rx.set_completion_count_cutoff(128);
    rx.set_max_hint_rows(4);
    rx.set_complete_on_empty(true);
    rx.set_double_tab_completion(false);
    rx.set_no_color(false);
    rx.set_immediate_completion(true);
    
    rx.history_load("heliumcommandhistory.txt");
    rx.set_max_history_size(256);

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

    TCHAR  infoBuf[64];
    DWORD  bufCharCount = 64;
    GetComputerNameA(infoBuf, &bufCharCount);
    ostringstream str;
    str << "[Helium@" << infoBuf << "] #";

    while (true) {
        string inputcmd = rx.input(str.str().c_str());
        cout << inputcmd << endl;
        rx.history_add(inputcmd);
    }

    rx.history_sync("heliumcommandhistory.txt");
    rx.history_save("heliumcommandhistory.txt");

    system("pause");
}
#pragma endregion


