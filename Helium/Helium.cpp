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

#pragma endregion

#pragma region Macros
#define PROJECT_NAME_STR "Helium"
#define PROJECT_VER_STR "0.4.2.06"
#define PROJECT_DEVSTAT "Pre-Alpha"

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
    for (auto ins = serverlist.begin(); ins < serverlist.end(); ins++) {
        int ret;
        if (ins->GetAutoStart()) {
            cout << "Starting Minecraft Server : " << ins->GetServerName() << endl;
            ret = ins->StartServer();
            cout << "Started with return code : " << ret << endl;
        }
        else {
            continue;
        }
        if (ret != 0) {
            cout << "Error starting Minecraft server : " << ins->GetServerName() << endl;
        }
    }
    
    Replxx rx;
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

    TCHAR  infoBuf[32767];
    DWORD  bufCharCount = 32767;
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