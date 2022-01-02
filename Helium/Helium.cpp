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

#pragma region Includes
#include<Windows.h>
#include<thread>
#include<strstream>
#include<iostream>

#include"logger.h"
#include"parse.h"
#include"config.h"
#include"minecraftserver.h"
#include"extension.h"
#include"permissions.h"

using namespace std;
using namespace Helium;

namespace Helium {
    using namespace std;
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
#define PROJECT_VER_STR "0.6.1"
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
    HeliumLogger logger("HeliumMain");
    map<string, HeliumExtension> extensions;
    vector<MinecraftServerInstance> serverlist;

#pragma endregion

#pragma region ServerFunc
    int _stdcall StartInfoThread(MinecraftServerInstance* lpIns) {
        thread tempthread(ProcessServerOutput, lpIns, lpIns->GetServerName(), lpIns->GetRDInfo().hStdOutRead, lpIns->GetThreadHandle());
        tempthread.detach();
        this_thread::yield();

        spdlog::debug("Output processing thread create successfully at 0x{}", "awa");
        return lpIns->GerServerPid();
    }
    int  _stdcall ProcessServerOutput(MinecraftServerInstance* ptr, string servername, HANDLE stdread, HANDLE hProc) {
        HeliumEndline hendl;
        logger << HLL::LL_INFO << servername << " server started at PID : " << (long)ptr->GerServerPid() << hendl;
        char out_buffer[BUFSIZE];
        DWORD dwRead;
        bool ret = FALSE;
        DWORD dwCode = 0;
        string read;
        while (true) {
            ZeroMemory(out_buffer, BUFSIZE);
            //用WriteFile，从hStdOutRead读出子进程stdout输出的数据，数据结果在out_buffer中，长度为dwRead

            char ch;
            if (stdread == INVALID_HANDLE_VALUE || stdread == NULL)
                break;
            if (ReadFile(stdread, &ch, 1, &dwRead, NULL) == false)
                break;
            if (dwRead == 0)
                pass;
            if (ch != '\n') {
                read += ch;
                pass;
            }
            else {
                if (ptr->GetVisibility()) {
                    cout << servername << "->" << read << endl;
                }
                read = "";
            }

            MSG msg;
            DWORD dwRet = MsgWaitForMultipleObjects(1, ptr->GetThreadPHandle(), FALSE, 20, QS_ALLINPUT);
            switch (dwRet) {
            case WAIT_OBJECT_0:
                break;
            case WAIT_OBJECT_0 + 1:
                PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
                DispatchMessage(&msg);
                continue;
            default:
                break;
            }
        }

        logger << HLL::LL_INFO << "Server " << servername << " exited." << hendl;
        ptr->SetServerReturnValue(dwCode);
        ptr->SetServerStatus(1);
        return 114514;
    }
}
#pragma endregion



#pragma region Main

    int main() {
        HeliumEndline hendl;
        SetConsoleTitleA(PROJECT_NAME_STR);
        ios::sync_with_stdio(false);
        cin.tie(0);
        spdlog::set_level(spdlog::level::info);

        logger << HLL::LL_INFO << PROJECT_NAME_STR << " " << PROJECT_VER_STR << " " << PROJECT_DEVSTAT;
        logger << " Copyright(C) 2021-2022 HeliumDevTeam";
        logger << "This program comes with ABSOLUTELY NO WARRANTY; for details type \`show w\'.";
        logger << "This is free software, and you are welcome to redistribute it";
        logger <<"under certain conditions; type \`show c\' for details.";
        logger << hendl;

#ifdef NOT_STABLE
        spdlog::set_level(spdlog::level::debug);
        logger << HLL::LL_WARN << "This is a early version of Helium, don't use this in a productive environment." << hendl;
#endif

        if (auto ret = Config(); ret != 0) {
            logger << HLL::LL_CRIT << "Failed to read config,exiting..." << hendl;
            system("pause");
            return -1;
        }

        if (auto ret = ReadServerFile(); ret != 0) {
            CreateServerFile();
            logger << HLL::LL_CRIT << "Failed to read global server config,exiting..." << hendl;
            system("pause");
            return -1;
        }

        if (auto ret = ReadPermissionFile(); ret != 0) {
            CreatePermissionFile();
            logger << HLL::LL_CRIT << "Failed to read permission file,exiting..." << hendl;
            system("pause");
            return -1;
        }

#undef ins

        for (auto ins = serverlist.begin(); ins < serverlist.end(); ins++) {
            int ret;
            if (ins->GetAutoStart()) {
                logger << HLL::LL_INFO << "Starting Minecraft server : " << ins->GetServerName() << hendl;
                ret = ins->StartServer();
                logger << HLL::LL_INFO << "Started with return code : " << ret << hendl;
                StartInfoThread(&(*ins));
            }
            else {
                continue;
            }
            if (ret != 0) {
                logger << HLL::LL_ERR << "Error starting Minecraft server : " << ins->GetServerName() << hendl;
            }
        }

        for (auto ins = serverlist.begin(); ins < serverlist.end(); ins++) {
            ins->StopServer();
        }

        if (auto ret = SaveConfigFile(); ret != 0) {
            logger << HLL::LL_WARN << "Failed to save the config file, your changes may not be saved." << hendl;
        }

        if (auto ret = SaveServerFile(); ret != 0) {
            logger << HLL::LL_WARN << "Failed to save the global server config file, your changes may not be saved." << hendl;
        }

        if (auto ret = SavePermissionFile(); ret != 0) {
            logger << HLL::LL_WARN << "Failed to save the permission file, your changes may not be saved." << hendl;
        }

        spdlog::drop_all();
        system("pause");
    }
#pragma endregion
