#include"extension.h"

_stdcall HeliumExtension::HeliumExtension() {

}
_stdcall HeliumExtension::HeliumExtension(const HeliumExtension* ext) {

}
_stdcall HeliumExtension::~HeliumExtension() {

}

string _stdcall HeliumExtension::SetExtName(string name) {
	this->extname = name;
	return name;
}
string _stdcall HeliumExtension::GetExtName() {
	return this->extname;
}

string _stdcall HeliumExtension::SetExtFileName(string name) {
	this->extfilename = name;
	return name;
}
string _stdcall HeliumExtension::GetExtFileName() {
	return this->extfilename;
}

int    _stdcall HeliumExtension::SetExtStatus(int stat) {
	this->extstatus = stat;
	return stat;
}

void* _stdcall HeliumExtension::GetFuncPtr(const char* lpFuncName)
{
	if (this->exthandle == NULL)
	{
		return NULL;
	}
	void* ptr;
	ptr = GetProcAddress(this->exthandle, lpFuncName);
	return ptr;
}

int    _stdcall HeliumExtension::GetExtStatus() {
	return this->extstatus;
}

int   _stdcall HeliumExtension::SetExtGUID(GUID guid) {
	this->extguid = guid;
	return 0;
}

int   _stdcall HeliumExtension::GetExtGUID(LPGUID lpGuid) {
	*lpGuid = this->extguid;
}

int    _stdcall HeliumExtension::LoadExt() {
	if (this->extstatus == EXT_STATUS_EMPTY) {
		this->extstatus = EXT_STATUS_LOADING;

		char cwd[MAX_PATH] = { 0 }; 
		string extpath;
		FARPROC tempptr;

		GetCurrentDirectoryA(MAX_PATH, cwd);
		extpath.append(cwd).append("\\").append("extensions").append("\\").append(this->extfilename);

		auto dllhandle = LoadLibraryA(extpath.c_str());
		if (dllhandle == NULL)
		{
			return -2;
		}
		else
		{
			//GET_EXT_FUNCPTR("OnExtensionLoad");
			//GET_EXT_FUNCPTR("OnServerStartup");
			pair<int, void*> p;
			this->exthandle = dllhandle;
			fd(ON_LOAD, "OnLoad")
			ins
			fd(ON_INFO, "OnInfo")
			ins
			fd(ON_SERVER_LAUNCH, "OnServerLaunch")
			ins
			fd(ON_SERVER_START, "OnServerStart")
			ins
			fd(ON_SERVER_STARTUP, "OnServerStartup")
			ins
			fd(ON_SERVER_STOP, "OnServerStop")
			ins
			fd(ON_CONSOLE_INPUT, "OnConsoleInput")
			ins
			fd(ON_PLAYER_INFO, "OnPlayerInfo")
			ins
			fd(ON_UNLOAD, "OnUnload")
			ins
			fd(ON_HELIUM_STOP, "OnHeliumStop")
			ins
		}
		

		this->extstatus = EXT_STATUS_LOADED;
		return 0;
	}
	return -1;
}
int    HeliumExtension::UnloadExt(bool forceunload) {
	return 0;
}
int    HeliumExtension::Expire() {
	return 0;
}