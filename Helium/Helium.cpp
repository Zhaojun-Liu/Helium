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
#include"permissions.h"

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
#define PROJECT_VER_STR "0.4.8"
#define PROJECT_DEVSTAT "Pre-Alpha"
#define NOT_STABLE
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
int _stdcall StartInfoThread(MinecraftServerInstance *lpIns) {
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
    ostringstream str;

    SetConsoleTitleA(PROJECT_NAME_STR);

    pns.append(" ").append(PROJECT_VER_STR).append(" ").append(PROJECT_DEVSTAT);
    spdlog::info(pns);

#ifdef NOT_STABLE
    spdlog::warn("This is a early version of Helium, don't use this in a productive environment.");
#endif


    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    

    if (auto ret = Config(); ret != 0) {
        spdlog::critical("Failed to read config,exiting...");
        system("pause");
        return -1;
    }

    if (auto ret = ReadServerFile(); ret != 0) {
        CreateServerFile();
        spdlog::critical("Failed to read global server config,exiting...");
        system("pause");
        return -1;
    }

    if (auto ret = ReadPermissionFile(); ret != 0) {
        CreatePermissionFile();
        spdlog::critical("Failed to read permission file,exiting...");
        system("pause");
        return -1;
    }

#undef ins
    for (auto ins = serverlist.begin(); ins < serverlist.end(); ins++) {
        int ret;
        if (ins->GetAutoStart()) {
            str << "Starting Minecraft server : " << ins->GetServerName();
            spdlog::info(str.str());
            str.clear();
            ret = ins->StartServer();
            str << "Started with return code : " << ret << endl;
            spdlog::info(str.str());
            str.clear();
            StartInfoThread(&(*ins));
        }
        else {
            continue;
        }
        if (ret != 0) {
            str << "Error starting Minecraft server : " << ins->GetServerName() << endl;
            spdlog::error(str.str());
            str.clear();
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
    str << "[Helium@" << infoBuf << "] #";

    while (true) {
        string inputcmd = rx.input(str.str().c_str());
        cout << inputcmd << endl;
        rx.history_add(inputcmd);
    }

    rx.history_sync("heliumcommandhistory.txt");
    rx.history_save("heliumcommandhistory.txt");

    if (auto ret = SaveConfigFile(); ret != 0) {
        spdlog::error("Failed to save the config file, your changes may not be saved.");
    }

    if (auto ret = SaveServerFile(); ret != 0) {
        spdlog::error("Failed to save the global server config file, your changes may not be saved.");
    }

    if (auto ret = SavePermissionFile(); ret != 0) {
        spdlog::error("Failed to save the permission file, your changes may not be saved.");
    }

    system("pause");
}
#pragma endregion


