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
int    _stdcall HeliumExtension::GetExtStatus() {
	return this->extstatus;
}

int   _stdcall HeliumExtension::SetExtGUID(GUID guid) {
	this->extguid = guid;
	return 0;
}
int   _stdcall HeliumExtension::GetExtGUID(LPGUID guid) {
	*guid = this->extguid;
	return 0;
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

		GET_EXT_FUNCPTR("OnExtensionLoad");
		GET_EXT_FUNCPTR("OnServerStartup");

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