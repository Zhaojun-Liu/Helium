#include"parse.h"

ServerStartedEvent ParseServerStarted(const char* content) {
	ServerStartedEvent e(0);
	string c = content;
	map<size_t, string> m;
	Split(c, m, " ");
	char* str;
	e.itime = strtol(m.at(6).c_str(), &str, 10);
	return e;
}
ServerStartEvent ParseServerStart(const char* content) {
	ServerStartEvent e(0);
	string c = content;
	map<size_t, string> m;
	Split(c, m, ":");
	char* str;
	e.port = strtol(m.at(5).c_str(), &str, 10);
	return e;
 }

