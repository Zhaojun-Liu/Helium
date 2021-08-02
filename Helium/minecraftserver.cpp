#include"minecraftserver.h"

MinecraftServerInstance::MinecraftServerInstance() {
    this->serverproc = INVALID_HANDLE_VALUE;
    this->serverstartuptype = STARTUP_TYPE_JAR;
    this->serverstatus = SERVER_STATUS_TERMINATED;
    this->servertype = SERVER_TYPE_VANILLA;
    this->outputvisibility = true;
    this->autostart = false;
}

MinecraftServerInstance::MinecraftServerInstance(const MinecraftServerInstance const* ins) {
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
}

MinecraftServerInstance::~MinecraftServerInstance() {
    TerminateProcess(this->serverproc, 0);
}

string MinecraftServerInstance::SetServerName(string servername) {
	this->servername = servername;
	return servername;
}
string MinecraftServerInstance::GetServerName() {
	return this->servername;
}

string MinecraftServerInstance::SetJVMDirectory(string dir) {
	this->jvmdirectory = dir;
	return dir;
}
string MinecraftServerInstance::GetJVMDirectory() {
	return this->jvmdirectory;
}

string MinecraftServerInstance::SetServerFileName(string name) {
	this->serverfilename = name;
	return name;
}
string MinecraftServerInstance::GetServerFileName() {
	return this->serverfilename;
}

string MinecraftServerInstance::SetJVMOption(string option) {
	this->jvmoption = option;
	return option;
}
string MinecraftServerInstance::GetJVMOption() {
	return this->jvmoption;
}

string MinecraftServerInstance::SetServerDirectory(string dir) {
	this->serverdirectory = dir;
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
    this->maxmem = mem;
    return mem;
}
string MinecraftServerInstance::SetMinmem(string mem) {
    this->minmem = mem;
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
    char cwd[MAX_PATH];
    string startupcmdline, servercwd;
    stringstream sstr;

    GetCurrentDirectoryA(sizeof(cwd), cwd);

    startupcmdline.append(this->jvmdirectory).append(" ").append(this->jvmoption);
    startupcmdline.append(" ").append("-Xmx").append(this->maxmem).append(" ").append("-Xms").append(this->minmem);
    startupcmdline.append(" ").append(cwd).append("\\").append(this->serverdirectory).append("\\").append(this->serverfilename);

    servercwd.append(cwd).append("\\").append(this->serverdirectory);

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

    cout << "Minecraft server launched successfully" << endl;

    this->redir.hStdErrWrite = hStdOutWrite;
    this->redir.hStdInRead = hStdInRead;
    this->redir.hStdInWrite = hStdInWrite;
    this->redir.hStdOutRead = hStdOutRead;
    this->redir.hStdOutWrite = hStdOutWrite;

    thread tempthread(&MinecraftServerInstance::ProcessServerOutput, this);
    this->stdoutthread = std::move(tempthread);

    cout << "Output processing thread create successfully" << endl;

    if (ResumeThread(pi.hThread) == -1) {
        TerminateProcess(pi.hProcess, serverexitcode);
        return -1;
    }

    cout << "Minecraft server process resumed successfully" << endl;

    c_scl = NULL;
    return 0;
}
[[nodiscard("")]]
int    MinecraftServerInstance::StopServer() {
    return 0;
}
[[nodiscard("")]]
int    MinecraftServerInstance::RestartServer() {
    if(this->serverstatus)
    return 0;
}

int    MinecraftServerInstance::ProcessServerOutput() {
    return 0;
}