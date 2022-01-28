/*
* Helium is a customizable extension system for Minecraft server.
* You can get the lastest source code and releases of Helium at :
* https://github.com/Minecraft1248/Helium
* ----------------------------------------------------------------------------------------
* Helium Copyright (C) 2021-2022 HeliumDevTeam
*
* This file is a part of Helium
*
* Helium is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Helium is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Helium.  If not, see <https://www.gnu.org/licenses/>.
* ----------------------------------------------------------------------------------------
*/

module Helium;

namespace Helium {
    HeliumLogger logger("HeliumMain");
    map<string, HeliumExtension> extensions;
    extern vector<HeliumMinecraftServer> heliumservers;

    int StartInfoThread(HeliumMinecraftServer* lpIns) {
        thread tempthread(ProcessServerOutput, lpIns, lpIns->GetServerName(), lpIns->GetServerRedir().hStdOutRead, lpIns->GetServerHandle());
        tempthread.detach();
        this_thread::yield();

        return lpIns->GetServerPID();
    }
    int ProcessServerOutput(HeliumMinecraftServer* ptr, string servername, HANDLE stdread, HANDLE hProc) {
        HeliumEndline hendl;
        logger << HLL::LL_INFO << servername << " server started at PID : " << (long)ptr->GetServerPID() << hendl;
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
                if (ptr->IsOutputVisible()) {
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
        logger << HLL::LL_INFO << "  _   _      _ _"\
            " | | | | ___| (_)_   _ _ __ ___"\
            " | |_| |/ _ \\ | | | | | '_ ` _ \\"\
            " |  _  |  __/ | | |_| | | | | | |"\
            " |_| |_|\\___|_|_|\\__,_|_| |_| |_|";
        logger << hendl << hendl;
        logger << HeliumVersion.to_string() << hendl;
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

        if (auto ret = ReadHeliumConfig(); ret != XMLError::XML_SUCCESS) {
            if (auto iret = CreateHeliumConfig(); ret != XMLError::XML_SUCCESS) {
                HeliumErrorExit(true, true, "Failed to create the helium config file.");
            }
            HeliumErrorExit(true, true, "Failed to read helium config file, the file is created automatically.");
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

        FinShell();
        for (auto ins = serverlist.begin(); ins < serverlist.end(); ins++) {
            ins->StopServer();
        }

        return 0;
    }
    int HeliumMain(int argc, char* argv[]) {
        HeliumEndline hendl;
        int ret;

        HeliumEnvInit();

        HeliumInitOutput();

        InitBuiltinCommandTree();
        InitShellEnv();

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

        InitShell("Helium");

        HeliumFin();

        return 0;
    }
}

int main(int argc, char* argv[]) {
    return HeliumMain(argc, argv);
}
