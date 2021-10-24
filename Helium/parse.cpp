#include"parse.h"
namespace Helium {

	VanillaParser::VanillaParser()
	{
	}

	VanillaParser::~VanillaParser()
	{
	}

	void* __stdcall VanillaParser::parse(const char* content)
	{
		return nullptr;
	}

	ServerStarted _stdcall VanillaParser::parseServerStarted(const char* content) {
		ServerStarted e;
		string c = content;
		map<size_t, string> m;
		Split(c, m, " ");
		char* str;
		e.itime = strtol(m.at(6).c_str(), &str, 10);
		return e;
	}
	ServerStart _stdcall VanillaParser::parseServerStart(const char* content) {
		ServerStart e;
		string c = content;
		map<size_t, string> m;
		Split(c, m, ":");
		char* str;
		e.port = strtol(m.at(5).c_str(), &str, 10);
		return e;
	}

}