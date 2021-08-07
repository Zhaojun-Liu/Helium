#include"minecraftserver.h"

CRITICAL_SECTION cs;
static bool isinit = false;

MinecraftServerInstance::MinecraftServerInstance() {
    this->serverproc = INVALID_HANDLE_VALUE;
    this->serverstartuptype = STARTUP_TYPE_JAR;
    this->serverstatus = SERVER_STATUS_TERMINATED;
    this->servertype = SERVER_TYPE_VANILLA;
    this->outputvisibility = true;
    this->autostart = false;

    if (!isinit) { 
        InitializeCriticalSection(&cs); 
        isinit = true;
    }
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
    this->serverproc = ins->serverproc;

    this->outputvisibility = ins->outputvisibility;
    this->autostart = ins->autostart;

    if (!isinit) {
        InitializeCriticalSection(&cs);
        isinit = true;
    }
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
    this->serverproc = ins.serverproc;
    
    this->outputvisibility = ins.outputvisibility;
    this->autostart = ins.autostart;

    if (!isinit) {
        InitializeCriticalSection(&cs);
        isinit = true;
    }
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
    this->serverproc = ins.serverproc;

    this->outputvisibility = ins.outputvisibility;
    this->autostart = ins.autostart;
}

MinecraftServerInstance::~MinecraftServerInstance() {
    TerminateProcess(this->serverproc, 0);
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

        startupcmdline.append(this->jvmdirectory).append(" ").append("-jar").append(" ").append(this->jvmoption);
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

        if (bSuc == FALSE) {
            cout << "CreateProcess() failed!" << endl;
            return -1;
        }

        this->serverstatus = SERVER_STATUS_RUNNING;
        cout << "Minecraft server launched successfully" << endl;

        this->redir.hStdErrWrite = hStdOutWrite;
        this->redir.hStdInRead = hStdInRead;
        this->redir.hStdInWrite = hStdInWrite;
        this->redir.hStdOutRead = hStdOutRead;
        this->redir.hStdOutWrite = hStdOutWrite;
        this->serverpid = pi.dwProcessId;

        thread tempthread(ProcessServerOutput, this, this->servername, hStdOutRead);
        this->stdoutthread = std::move(tempthread);
        this->stdoutthread.detach();
        this_thread::yield();

        cout << "Output processing thread create successfully" << endl;

        if (ResumeThread(pi.hThread) == -1) {
            TerminateProcess(pi.hProcess, serverexitcode);
            return -1;
        }

        cout << "Minecraft server process resumed successfully" << endl;

        c_scl = NULL;
    }
    else if (this->serverstartuptype == STARTUP_TYPE_BAT) {
        if (this->serverstartuptype == STARTUP_TYPE_JAR) {
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

            this->redir.hStdErrWrite = hStdOutWrite;
            this->redir.hStdInRead = hStdInRead;
            this->redir.hStdInWrite = hStdInWrite;
            this->redir.hStdOutRead = hStdOutRead;
            this->redir.hStdOutWrite = hStdOutWrite;
            this->serverpid = pi.dwProcessId;

            thread tempthread(ProcessServerOutput, (MinecraftServerInstance*)this, this->servername, hStdOutRead);
            this->stdoutthread = std::move(tempthread);
            this->stdoutthread.detach();
            this_thread::yield();

            cout << "Output processing thread create successfully" << endl;

            if (ResumeThread(pi.hThread) == -1) {
                TerminateProcess(pi.hProcess, serverexitcode);
                return -1;
            }

            cout << "Minecraft server process resumed successfully" << endl;

            c_scl = NULL;
        }
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

int    ProcessServerOutput(MinecraftServerInstance* ptr, string servername, HANDLE stdread) {
    cout << "Server started at PID : " << ptr->serverpid << endl;
    char out_buffer[BUFSIZE];
    DWORD dwRead;
    bool ret = FALSE;
    DWORD process_exit_code;

    while (ptr->serverstatus != SERVER_STATUS_TERMINATED)
    {
        ZeroMemory(out_buffer, BUFSIZE);
        //用WriteFile，从hStdOutRead读出子进程stdout输出的数据，数据结果在out_buffer中，长度为dwRead  
        EnterCriticalSection(&cs);
        ret = ReadFile(stdread, out_buffer, BUFSIZE - 1, &dwRead, NULL);
        LeaveCriticalSection(&cs);
        if ((ret) && (dwRead != 0))  //如果成功了，且长度>0  
        {
            out_buffer[dwRead] = '\0';
            if (ptr->outputvisibility) {
                string temp(out_buffer);
                string pat("\r\n");
                auto outputs = split(temp, pat);
                for (auto it = outputs.begin(); it < outputs.end(); it++) {
                    string outputstr;
                    if (!it->empty() && *it != "\n")
                        outputstr.append(servername).append(">").append(*it).append("\r\n");
                    EnterCriticalSection(&cs);
                    cout << outputstr;
                    LeaveCriticalSection(&cs);
                }
                Sleep(20);
            }
        }
        //如果子进程结束，退出循环  
    }
    GetExitCodeProcess(ptr->serverproc, &process_exit_code);
    cout << "Exiting ProcessServerOutput()" << endl;
    return process_exit_code;
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