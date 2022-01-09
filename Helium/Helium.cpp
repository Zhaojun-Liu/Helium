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

#include"Helium.h"

using namespace Helium;

namespace Helium {
    using namespace std;

    HeliumLogger logger("HeliumMain");
    map<string, HeliumExtension> extensions;
    vector<MinecraftServerInstance> serverlist;

    int StartInfoThread(MinecraftServerInstance* lpIns) {
        thread tempthread(ProcessServerOutput, lpIns, lpIns->GetServerName(), lpIns->GetRDInfo().hStdOutRead, lpIns->GetThreadHandle());
        tempthread.detach();
        this_thread::yield();

        return lpIns->GerServerPid();
    }
    int ProcessServerOutput(MinecraftServerInstance* ptr, string servername, HANDLE stdread, HANDLE hProc) {
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

    void HeliumInitOutput() {
        HeliumEndline hendl;
        logger << HLL::LL_INFO << PROJECT_NAME_STR << " " << PROJECT_VER_STR << " " << PROJECT_DEVSTAT << hendl;
        logger << "Copyright(C) 2021-2022 HeliumDevTeam" << hendl;
        logger << "This program comes with ABSOLUTELY NO WARRANTY;" << hendl;
        logger << "for details type \'!!hel show w\'." << hendl;
        logger << "This is free software, and you are welcome to redistribute it";
        logger << "under certain conditions; type \'!!hel show c\' for details." << hendl;

        return;
    }
    int HeliumEnvInit() {
        SetConsoleTitleA(PROJECT_NAME_STR);
        ios::sync_with_stdio(false);
        cin.tie(0);
#ifdef NOT_STABLE
        spdlog::set_level(spdlog::level::debug);
#else
        spdlog::set_level(spdlog::level::info);
#endif
        spdlog::flush_every(chrono::seconds(5));
        return 0;
    }
    int HeliumInit() {
        HeliumEndline hendl;

        logger << HLL::LL_INFO << "Start Helium initialization." << hendl;
        //logger << HLL::LL_DBG << "Start adding dirs" << hendl;
        //AddHeliumDirectory("./extensions", "The \"extension\" folder doesn't exists, creating...", HDIP::HDIP_CREATE_WARING);
        //AddHeliumDirectory("./extensions/extconfigs", "The \"extensions/extconfigs\" folder doesn't exists, creating...", HDIP::HDIP_CREATE_WARING);
        //AddHeliumDirectory("./logs", "The \"logs\" folder doesn't exists, creating...", HDIP::HDIP_CREATE_WARING);
        //AddHeliumDirectory("./scripts", "The \"scripts\" folder doesn't exists, creating...", HDIP::HDIP_CREATE_WARING);
        //AddHeliumDirectory("./scripts/initscripts", "The \"scripts/initscripts\" folder doesn't exists, creating...", HDIP::HDIP_CREATE_WARING);
        //logger << HLL::LL_DBG << "End adding dirs" << hendl;

        //if (auto ret = InitHeliumDirectory(); ret != 0) {
        //HeliumErrorExit(true, true, "Failed to initialize directory,exiting...");
        //}

        if (auto ret = Config(); ret != 0) {
            HeliumErrorExit(true, true, "Failed to read config,exiting...");
        }

        if (auto ret = ReadServerFile(); ret != 0) {
            CreateServerFile();
            HeliumErrorExit(true, true, "Failed to read global server config,exiting...");
        }

        if (auto ret = ReadPermissionFile(); ret != 0) {
            CreatePermissionFile();
            HeliumErrorExit(true, true, "Failed to read permission file,exiting...");
        }

        logger << HLL::LL_INFO << "Finished Helium initialization." << hendl;
        return 0;
    }
    int HeliumStartServer() {
        HeliumEndline hendl;
        for (auto ins = serverlist.begin(); ins < serverlist.end(); ins++) {
            int ret;
            if (ins->GetAutoStart()) {
                logger << HLL::LL_INFO << "Starting Minecraft server : " << ins->GetServerName() << hendl;
                ret = ins->StartServer();
                logger << HLL::LL_INFO << "Minecraft Server started with return code : " << ret << hendl;
                StartInfoThread(&(*ins));
            }
            else {
                continue;
            }
            if (ret != 0) {
                logger << HLL::LL_ERR << "Error starting Minecraft server : " << ins->GetServerName() << hendl;
            }
        }
        return 0;
    }
    int HeliumFin() {
        HeliumEndline hendl;
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
        return 0;
    }
    int HeliumMain(int argc, char* argv[]) {
        HeliumEndline hendl;
        int ret;

        HeliumEnvInit();

        HeliumInitOutput();

        try {
            ret = HeliumInit();
        }
        catch (...) {
            logger << HLL::LL_CRIT << "Helium initialization failed with a exception." << hendl;
            logger << HLL::LL_CRIT << "THIS IS A CRASH, report it to us by : helium_devteam@outlook.com" << hendl;
            ret = -1;
        }

        if (ret == 0) {
            HeliumStartServer();
        }
        else {
            logger << HLL::LL_WARN << "Helium initialization failed, skip starting server." << hendl;
        }

        InitBuiltinCommandTree();
        InitShellEnv();
        InitShell("Helium");
        FinShell();

        HeliumFin();

        return 0;
    }
}

int main(int argc, char* argv[]) {
    return HeliumMain(argc, argv);
}
