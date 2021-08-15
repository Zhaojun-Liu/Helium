#include"minecraftserver.h"

CRITICAL_SECTION cs;
static bool isinit = false;
vector<MinecraftServerInstance> serverlist;

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

int    MinecraftServerInstance::SetServerType(int type){
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

        cout << startupcmdline << endl;
        cout << servercwd << endl;

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
        cout << c_scl << endl;

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
        spdlog::debug("bSuc:{}", bSuc);
        if (bSuc == FALSE) {
            cout << "CreateProcess() failed!" << endl;
            return -1;
        }

        this->serverstatus = SERVER_STATUS_RUNNING;
        cout << "Minecraft server launched successfully" << endl;
        this->hProc = pi.hProcess;
        this->redir.hStdErrWrite = hStdOutWrite;
        this->redir.hStdInRead = hStdInRead;
        this->redir.hStdInWrite = hStdInWrite;
        this->redir.hStdOutRead = hStdOutRead;
        this->redir.hStdOutWrite = hStdOutWrite;
        this->dwPid = pi.dwProcessId;

        DWORD dwRet = ResumeThread(pi.hThread);
        spdlog::debug("dwRet:{}", dwRet);
        if (dwRet == -1) {
            TerminateProcess(pi.hProcess, serverexitcode);
            return -1;
        }

        cout << "Minecraft server process resumed successfully" << endl;

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

            cout << startupcmdline << endl;
            cout << servercwd << endl;

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
            cout << c_scl << endl;
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
                cout << "CreateProcess() failed!" << endl;
                return -1;
            }
            
            this->serverstatus = SERVER_STATUS_RUNNING;
            cout << "Minecraft server launched successfully" << endl;
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

            cout << "Minecraft server process resumed successfully" << endl;

            c_scl = NULL;
        
    }
    return 0;
}
[[nodiscard("")]]
int    MinecraftServerInstance::StopServer() {
    return 0;
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
    cout << endl << "Minecraft Server Instance Debug Print" << endl;
    cout << "Server Name : " << this->servername << endl;
    cout << "Server Directory :" << this->serverdirectory << endl;
    cout << "Server File Name : " << this->serverfilename << endl;
    cout << "JVM Directory : " << this->jvmdirectory << endl;
    cout << "JVM Option : " << this->jvmoption << endl;
    cout << "Max Memory : " << this->maxmem << endl;
    cout << "Min Memory : " << this->minmem << endl << endl;
    cout << "Startup Type : " << this->serverstartuptype << endl;
    cout << "Server Type : " << this->servertype << endl;
    cout << "Server Status : " << this->serverstatus << endl << endl;
    cout << "Output Visibility : " << this->outputvisibility << endl;
    cout << "Auto Start : " << this->autostart << endl << endl;
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
    return 0;
}