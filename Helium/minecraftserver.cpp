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

#include"minecraftserver.h"
namespace Helium {
    vector<MinecraftServerInstance> serverlist;
    vector<HeliumMinecraftServer> heliumservers;
    CRITICAL_SECTION cs;
    static bool isinit = false;
    HeliumLogger msl("HeliumServerConfig");

    MinecraftServerInstance::MinecraftServerInstance() {
        this->hProc = INVALID_HANDLE_VALUE;
        this->serverstartuptype = STARTUP_TYPE_JAR;
        this->serverstatus = SERVER_STATUS_TERMINATED;
        this->servertype = SERVER_TYPE_VANILLA;
        this->outputvisibility = true;
        this->autostart = false;
        CoCreateGuid(&this->serverguid);
    }

    MinecraftServerInstance::MinecraftServerInstance(const MinecraftServerInstance* ins) {
        this->servername = ins->servername;
        this->jvmdirectory = ins->jvmdirectory;
        this->serverfilename = ins->serverfilename;
        this->jvmoption = ins->jvmoption;
        this->serverdirectory = ins->serverdirectory;
        this->minmem = ins->minmem;
        this->maxmem = ins->maxmem;

        this->serverstartuptype = ins->serverstartuptype;
        this->servertype = ins->servertype;
        this->serverstatus = ins->serverstatus;

        this->stdoutthread = const_cast<thread&&>(move(ins->stdoutthread));
        this->hProc = ins->hProc;

        this->outputvisibility = ins->outputvisibility;
        this->autostart = ins->autostart;
        this->serverguid = ins->serverguid;
        this->dwPid = ins->dwPid;
        this->dwReturnValue = ins->dwReturnValue;
    }

    MinecraftServerInstance::MinecraftServerInstance(const MinecraftServerInstance& ins) {
        this->servername = ins.servername;
        this->jvmdirectory = ins.jvmdirectory;
        this->serverfilename = ins.serverfilename;
        this->jvmoption = ins.jvmoption;
        this->serverdirectory = ins.serverdirectory;
        this->minmem = ins.minmem;
        this->maxmem = ins.maxmem;

        this->serverstartuptype = ins.serverstartuptype;
        this->servertype = ins.servertype;
        this->serverstatus = ins.serverstatus;

        this->stdoutthread = const_cast<thread&&>(move(ins.stdoutthread));
        this->hProc = ins.hProc;

        this->outputvisibility = ins.outputvisibility;
        this->autostart = ins.autostart;
        this->serverguid = ins.serverguid;
        this->dwPid = ins.dwPid;
        this->dwReturnValue = ins.dwReturnValue;
    }

    void MinecraftServerInstance::operator=(const MinecraftServerInstance&& ins) {
        this->servername = ins.servername;
        this->jvmdirectory = ins.jvmdirectory;
        this->serverfilename = ins.serverfilename;
        this->jvmoption = ins.jvmoption;
        this->serverdirectory = ins.serverdirectory;
        this->minmem = ins.minmem;
        this->maxmem = ins.maxmem;

        this->serverstartuptype = ins.serverstartuptype;
        this->servertype = ins.servertype;
        this->serverstatus = ins.serverstatus;

        this->stdoutthread = const_cast<thread&&>(move(ins.stdoutthread));
        this->hProc = ins.hProc;

        this->outputvisibility = ins.outputvisibility;
        this->autostart = ins.autostart;
        this->serverguid = ins.serverguid;
        this->dwPid = ins.dwPid;
        this->dwReturnValue = ins.dwReturnValue;
    }

    MinecraftServerInstance::~MinecraftServerInstance() {
        TerminateProcess(this->hProc, 0);
        if (!isinit) {
            DeleteCriticalSection(&cs);
            isinit = false;
        }
    }

    string MinecraftServerInstance::SetServerName(string servername) {
        this->servername = move(servername);
        return servername;
    }
    string MinecraftServerInstance::GetServerName() {
        return this->servername;
    }

    string MinecraftServerInstance::SetJVMDirectory(string dir) {
        this->jvmdirectory = move(dir);
        return dir;
    }
    string MinecraftServerInstance::GetJVMDirectory() {
        return this->jvmdirectory;
    }

    string MinecraftServerInstance::SetServerFileName(string name) {
        this->serverfilename = move(name);
        return name;
    }
    string MinecraftServerInstance::GetServerFileName() {
        return this->serverfilename;
    }

    string MinecraftServerInstance::SetJVMOption(string option) {
        this->jvmoption = move(option);
        return option;
    }
    string MinecraftServerInstance::GetJVMOption() {
        return this->jvmoption;
    }

    string MinecraftServerInstance::SetServerDirectory(string dir) {
        this->serverdirectory = move(dir);
        return dir;
    }
    string MinecraftServerInstance::GetServerDirectory() {
        return this->serverdirectory;
    }

    int    MinecraftServerInstance::SetStartupType(int type) {
        this->serverstartuptype = type;
        return type;
    }
    int    MinecraftServerInstance::GetStartupType() {
        return this->serverstartuptype;
    }

    int    MinecraftServerInstance::SetServerType(int type) {
        this->servertype = type;
        return type;
    }
    int    MinecraftServerInstance::GetServerType() {
        return this->servertype;
    }

    int    MinecraftServerInstance::SetServerStatus(int stat) {
        this->serverstatus = stat;
        return stat;
    }
    int    MinecraftServerInstance::GetServerStatus() {
        return this->serverstatus;
    }

    string MinecraftServerInstance::SetMaxmem(string mem) {
        this->maxmem = move(mem);
        return mem;
    }
    string MinecraftServerInstance::SetMinmem(string mem) {
        this->minmem = move(mem);
        return mem;
    }
    string MinecraftServerInstance::GetMaxmem() {
        return this->maxmem;
    }
    string MinecraftServerInstance::GetMinmem() {
        return this->minmem;
    }

    bool   MinecraftServerInstance::SetVisibility(bool vis) {
        this->outputvisibility = vis;
        return vis;
    }
    bool   MinecraftServerInstance::GetVisibility() {
        return this->outputvisibility;
    }

    bool   MinecraftServerInstance::SetAutoStart(bool start) {
        this->autostart = start;
        return start;
    }
    bool   MinecraftServerInstance::GetAutoStart() {
        return this->autostart;
    }

    [[nodiscard("")]]
    int    MinecraftServerInstance::StartServer() {
        HeliumEndline hendl;

        if (this->serverstartuptype == STARTUP_TYPE_JAR) {
            char cwd[MAX_PATH];
            string startupcmdline, servercwd;
            stringstream sstr;

            GetCurrentDirectoryA(sizeof(cwd), cwd);

            startupcmdline.append(this->jvmdirectory).append(" ").append(this->jvmoption).append(" ").append("-jar");
            startupcmdline.append(" ").append("-Xmx").append(this->maxmem).append(" ").append("-Xms").append(this->minmem);
            if (this->serverdirectory.find(':') == string::npos) {
                startupcmdline.append(" ").append(cwd).append("\\").append(this->serverdirectory).append("\\").append(this->serverfilename);
                servercwd.append(cwd).append("\\").append(this->serverdirectory);
            }
            else {
                startupcmdline.append(" ").append(this->serverdirectory).append("\\").append(this->serverfilename);
                servercwd = this->serverdirectory;
            }

            msl << startupcmdline << hendl;
            msl << servercwd << hendl;

            HANDLE hStdInRead = NULL;   //子进程用的stdin的读入端  
            HANDLE hStdInWrite = NULL;  //主程序用的stdin的读入端 
            HANDLE hStdOutRead = NULL;  //主程序用的stdout的读入端  
            HANDLE hStdOutWrite = NULL; //子进程用的stdout的写入端  

            PROCESS_INFORMATION pi;
            STARTUPINFOA si;
            SECURITY_ATTRIBUTES sa;
            RedirectInformation inf;

            sa.bInheritHandle = TRUE;
            sa.lpSecurityDescriptor = NULL;
            sa.nLength = sizeof(SECURITY_ATTRIBUTES);

            //产生一个用于stdin的管道，得到两个HANDLE:  hStdInRead用于子进程读出数据，hStdInWrite用于主程序写入数据  
            //其中saAttr是一个STARTUPINFO结构体，定义见CreatePipe函数说明  
            if (!CreatePipe(&hStdInRead, &hStdInWrite, &sa, 0))
                return -1;
            //产生一个用于stdout的管道，得到两个HANDLE:  hStdOutRead用于主程序读出数据，hStdOutWrite用于子程序写入数据  
            if (!CreatePipe(&hStdOutRead, &hStdOutWrite, &sa, 0))
                return -1;

            if (hStdInRead == NULL || hStdInWrite == NULL) return -1;
            if (hStdOutRead == NULL || hStdOutWrite == NULL) return -1;

            ZeroMemory(&si, sizeof(STARTUPINFO));
            GetStartupInfoA(&si);
            si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
            si.hStdOutput = hStdOutWrite;   //意思是：子进程的stdout输出到hStdOutWrite  
            si.hStdError = hStdOutWrite;    //意思是：子进程的stderr输出到hStdErrWrite  
            si.hStdInput = hStdInRead;
            si.wShowWindow = SW_SHOW;
            si.cb = sizeof(STARTUPINFOA);

            unsigned int serverexitcode = 0;

            char* c_scl = const_cast<char*>(startupcmdline.c_str());

            BOOL bSuc = CreateProcessA(NULL
                , c_scl
                , NULL
                , NULL
                , true
                , CREATE_SUSPENDED
                , NULL
                , servercwd.c_str()
                , &si
                , &pi);
            if (bSuc == FALSE) {
                msl << HLL::LL_CRIT << "CreateProcess() failed!" << hendl;
                return -1;
            }

            this->serverstatus = SERVER_STATUS_RUNNING;
            msl << HLL::LL_INFO << "Minecraft server launched successfully" << hendl;
            this->hProc = pi.hProcess;
            this->redir.hStdErrWrite = hStdOutWrite;
            this->redir.hStdInRead = hStdInRead;
            this->redir.hStdInWrite = hStdInWrite;
            this->redir.hStdOutRead = hStdOutRead;
            this->redir.hStdOutWrite = hStdOutWrite;
            this->dwPid = pi.dwProcessId;

            DWORD dwRet = ResumeThread(pi.hThread);
            if (dwRet == -1) {
                TerminateProcess(pi.hProcess, serverexitcode);
                return -1;
            }

            msl << HLL::LL_INFO << "Minecraft server process resumed successfully" << hendl;

            c_scl = NULL;
        }
        else if (this->serverstartuptype == STARTUP_TYPE_BAT) {
            char cwd[MAX_PATH];
            string startupcmdline, servercwd;
            stringstream sstr;

            GetCurrentDirectoryA(sizeof(cwd), cwd);

            startupcmdline.append(cwd).append(this->serverfilename);
            if (this->serverdirectory.find(':') == string::npos) {
                servercwd.append(cwd).append("\\").append(this->serverdirectory);
            }
            else {
                servercwd = this->serverdirectory;
            }

            HANDLE hStdInRead = NULL;   //子进程用的stdin的读入端  
            HANDLE hStdInWrite = NULL;  //主程序用的stdin的读入端 
            HANDLE hStdOutRead = NULL;  //主程序用的stdout的读入端  
            HANDLE hStdOutWrite = NULL; //子进程用的stdout的写入端  

            PROCESS_INFORMATION pi;
            STARTUPINFOA si;
            SECURITY_ATTRIBUTES sa;
            RedirectInformation inf;

            sa.bInheritHandle = TRUE;
            sa.lpSecurityDescriptor = NULL;
            sa.nLength = sizeof(SECURITY_ATTRIBUTES);

            //产生一个用于stdin的管道，得到两个HANDLE:  hStdInRead用于子进程读出数据，hStdInWrite用于主程序写入数据  
            //其中saAttr是一个STARTUPINFO结构体，定义见CreatePipe函数说明  
            if (!CreatePipe(&hStdInRead, &hStdInWrite, &sa, 0))
                return -1;
            //产生一个用于stdout的管道，得到两个HANDLE:  hStdOutRead用于主程序读出数据，hStdOutWrite用于子程序写入数据  
            if (!CreatePipe(&hStdOutRead, &hStdOutWrite, &sa, 0))
                return -1;

            if (hStdInRead == NULL || hStdInWrite == NULL) return -1;
            if (hStdOutRead == NULL || hStdOutWrite == NULL) return -1;

            ZeroMemory(&si, sizeof(STARTUPINFO));
            GetStartupInfoA(&si);
            si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
            si.hStdOutput = hStdOutWrite;   //意思是：子进程的stdout输出到hStdOutWrite  
            si.hStdError = hStdOutWrite;    //意思是：子进程的stderr输出到hStdErrWrite  
            si.hStdInput = hStdInRead;
            si.wShowWindow = SW_SHOW;
            si.cb = sizeof(STARTUPINFOA);

            unsigned int serverexitcode = 0;

            char* c_scl = const_cast<char*>(startupcmdline.c_str());
            msl << c_scl << hendl;
            BOOL bSuc = CreateProcessA(NULL
                , c_scl
                , NULL
                , NULL
                , true
                , CREATE_SUSPENDED
                , NULL
                , servercwd.c_str()
                , &si
                , &pi);

            if (bSuc == FALSE) {
                msl << HLL::LL_CRIT << "CreateProcess() failed!" << hendl;
                return -1;
            }

            this->serverstatus = SERVER_STATUS_RUNNING;
            msl << HLL::LL_INFO << "Minecraft server launched successfully" << hendl;
            this->hProc = pi.hProcess;
            this->redir.hStdErrWrite = hStdOutWrite;
            this->redir.hStdInRead = hStdInRead;
            this->redir.hStdInWrite = hStdInWrite;
            this->redir.hStdOutRead = hStdOutRead;
            this->redir.hStdOutWrite = hStdOutWrite;
            this->dwPid = pi.dwProcessId;

            if (!isinit) {
                InitializeCriticalSection(&cs);
                isinit = true;
            }



            if (ResumeThread(pi.hThread) == -1) {
                TerminateProcess(pi.hProcess, serverexitcode);
                return -1;
            }

            msl << HLL::LL_INFO << "Minecraft server process resumed successfully" << hendl;

            c_scl = NULL;

        }
        return 0;
    }
    [[nodiscard("")]]
    int    MinecraftServerInstance::StopServer() {
        UINT retv = 0;
        return TerminateProcess(this->hProc, retv);
    }
    [[nodiscard("")]]
    int    MinecraftServerInstance::RestartServer() {
        return 0;
    }

    int _stdcall MinecraftServerInstance::SetServerReturnValue(DWORD dwValue)
    {
        this->dwReturnValue = dwValue;
        return 0;
    }

    int _stdcall MinecraftServerInstance::GetServerReturnValue(LPDWORD lpValue)
    {
        *lpValue = this->dwReturnValue;
        return 0;
    }


    void   MinecraftServerInstance::Print() {
        HeliumEndline hendl;
        msl << HLL::LL_DBG << hendl << "Minecraft Server Instance Debug Print" << hendl;
        msl << "Server Name : " << this->servername << hendl;
        msl << "Server Directory :" << this->serverdirectory << hendl;
        msl << "Server File Name : " << this->serverfilename << hendl;
        msl << "JVM Directory : " << this->jvmdirectory << hendl;
        msl << "JVM Option : " << this->jvmoption << hendl;
        msl << "Max Memory : " << this->maxmem << hendl;
        msl << "Min Memory : " << this->minmem << hendl << hendl;
        msl << "Startup Type : " << this->serverstartuptype << hendl;
        msl << "Server Type : " << this->servertype << hendl;
        msl << "Server Status : " << this->serverstatus << hendl << hendl;
        msl << "Output Visibility : " << this->outputvisibility << hendl;
        msl << "Auto Start : " << this->autostart << hendl << hendl;
        return;
    }

    int    _stdcall MinecraftServerInstance::SetServerGUID(LPCGUID guid) {
        this->serverguid = *guid;
        return 0;
    }
    int    _stdcall MinecraftServerInstance::GetServerGUID(LPGUID guid) {
        *guid = this->serverguid;
        return 0;
    }

    DWORD _stdcall MinecraftServerInstance::GerServerPid()
    {
        return this->dwPid;
    }

    bool _stdcall MinecraftServerInstance::GetOutputVis()
    {
        return this->outputvisibility;
    }

    HANDLE _stdcall MinecraftServerInstance::GetThreadHandle()
    {
        return this->hProc;
    }

    int _stdcall ReadServerFile() {
        HeliumEndline hendl;
        msl << HLL::LL_INFO << "Reading global server config file..." << hendl;
        tinyxml2::XMLDocument doc;
        auto error = doc.LoadFile(SERVER_FILENAME);
        if (error != tinyxml2::XMLError::XML_SUCCESS) {
            msl << HLL::LL_CRIT << "Cannot read global server config file" << hendl;
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
            msl << HLL::LL_CRIT << "Failed to get the root element of the global server config file." << hendl;
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

        msl << HLL::LL_INFO << "Done." << hendl;

        return 0;
    }
    int _stdcall SaveServerFile() {
        HeliumEndline hendl;
        msl << HLL::LL_INFO << "Saving global server config file..." << hendl;
        tinyxml2::XMLDocument doc;
        auto dec = doc.NewDeclaration("<?xml version=\"1.0\"?>");
        doc.InsertEndChild(dec);
        
        auto root = doc.NewElement("HeliumServerConfig");

        if (root == NULL) {
            msl << HLL::LL_ERR << "Failed to create root element for global server config file." << hendl;
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
            msl << HLL::LL_ERR << "Failed to save global server config file, your changes may not be saved." << hendl;
            return -1;
        }

        msl << HLL::LL_INFO << "Done." << hendl;

        return 0;
    }
    int _stdcall CreateServerFile() {
        HeliumEndline hendl;
        msl << HLL::LL_INFO << "Creating global server config file..." << hendl;
        tinyxml2::XMLDocument doc;
        auto dec = doc.NewDeclaration("xml version=\"1.0\"");
        doc.InsertEndChild(dec);

        auto root = doc.NewElement("HeliumServerConfig");

        if (root == NULL) {
            msl << HLL::LL_ERR << "Failed to create root element for global server config file." << hendl;
            return -1;
        }

        tinyxml2::XMLElement* newelem = doc.NewElement("MinecraftServer");

        newelem->SetAttribute("type", "vanilla");
        newelem->SetAttribute("startuptype", "jar");
        newelem->SetAttribute("autostart", "false");
        newelem->SetAttribute("outputvisibility", "false");

        tinyxml2::XMLElement* newchild = newelem->InsertNewChildElement("ServerName");
        newchild = newelem->InsertNewChildElement("ServerDirectory");
        newchild = newelem->InsertNewChildElement("JVMDirectory");
        newchild = newelem->InsertNewChildElement("JVMOption");
        newchild = newelem->InsertNewChildElement("ServerFileName");
        newchild = newelem->InsertNewChildElement("MaxMemory");
        newchild = newelem->InsertNewChildElement("MinMemory");

        root->InsertEndChild(newelem);

        auto error = doc.SaveFile(SERVER_FILENAME);
        if (error != tinyxml2::XMLError::XML_SUCCESS) {
            msl << HLL::LL_ERR << "Failed to save global server config file, your changes may not be saved." << hendl;
            return -1;
        }

        msl << HLL::LL_INFO << "Done." << hendl;

        return 0;
    }
}