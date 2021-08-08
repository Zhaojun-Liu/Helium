#include"logger.h"
#define _CRT_SECURE_NO_WARNINGS

[[nodiscard("Ignoring return value of this function may cause log file create incorrectly.")]]
int _stdcall HeliumOutput::write(string outstr)
{
	time_t t = time(0);
	char time[64];
	strftime(time, sizeof(time), "%Y-%m-%d", localtime(&t));
	ostringstream s;
	char path[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, path);
	s << path << "\\logs";
	_mkdir(s.str().c_str());
	s << "\\" << time << ".log";
	fstream file(s.str(), fstream::app);
	if (file.is_open()) {
		file.write(outstr.c_str(), outstr.length());
		file.flush();
		file.close();
	}
	
	return 0;
}

void _stdcall HeliumOutput::setTimeStamp(bool stat)
{
	this->enableTimeStamp = stat;
}

_stdcall HeliumOutput::HeliumOutput()
{
	this->enableTimeStamp = true;
}

int _stdcall HeliumOutput::info(const char* content)
{
	string content_;
	time_t t = time(0);
	char time[64];
	strftime(time, sizeof(time), "%Y-%m-%d-%H-%M-%S", localtime(&t));
	if(enableTimeStamp) content_ += time;
	content_ += " [INFO] ";
	content_ += content;
	auto ret = this->write(content_);
	int iWrote = 0;
	if (enableTimeStamp)iWrote += this->out(time, _WHITE);
	iWrote += this->out(" [INFO] ", GREEN_FOREGROUND);
	iWrote += this->out(content, _WHITE);
	return iWrote;
}

int _stdcall HeliumOutput::warn(const char* content)
{
	string content_;
	time_t t = time(0);
	char time[64];
	strftime(time, sizeof(time), "%Y-%m-%d-%H-%M-%S", localtime(&t));
	if (enableTimeStamp) content_ += time;
	content_ += " [WARN] ";
	content_ += content;
	auto ret = this->write(content_);
	if (ret != 0) return -1;
	int iWrote = 0;
	if (enableTimeStamp) iWrote += this->out(time, _WHITE);
	iWrote += this->out(" [WARN] ", YELLOW_FOREGEOUND);
	iWrote += this->out(content, _WHITE);
	return iWrote;
}

int _stdcall HeliumOutput::error(const char* content)
{
	string content_;
	time_t t = time(0);
	char time[64];
	strftime(time, sizeof(time), "%Y-%m-%d-%H-%M-%S", localtime(&t));
	if (enableTimeStamp) content_ += time;
	content_ += " [ERROR] ";
	content_ += content;
	auto ret = this->write(content_);
	if (ret != 0) return -1;
	int iWrote = 0;
	if (enableTimeStamp) iWrote += this->out(time, _WHITE);
	iWrote += this->out(" [ERROR] ", RED_FOREGROUND);
	iWrote += this->out(content, _WHITE);
	return iWrote;
}

int _stdcall HeliumOutput::fatal(const char* content)
{
	string content_;
	time_t t = time(0);
	char time[64];
	strftime(time, sizeof(time), "%Y-%m-%d-%H-%M-%S", localtime(&t));
	if (enableTimeStamp) content_ += time;
	content_ += " [FATAL] ";
	content_ += content;
	auto ret = this->write(content_);
	if (ret != 0) return -1;
	int iWrote = 0;
	if (enableTimeStamp == true) {
		iWrote += this->out(content_.c_str(), RED_FOREGROUND);
	}
	else {
		iWrote += this->out(" [FATAL] ", RED_FOREGROUND);
		iWrote += this->out(content, RED_FOREGROUND);
	}
	return iWrote;
}

int _stdcall HeliumOutput::out(LPSTR sOut, WCHAR wTextAttribute)
{
	HANDLE hOutput;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	WORD wOldAttribute;
	DWORD dwWritten, temp;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOutput, &csbiInfo);
	wOldAttribute = csbiInfo.wAttributes;
	SetConsoleTextAttribute(hOutput, wTextAttribute);
	WriteFile(hOutput, sOut, lstrlenA(sOut), &dwWritten, NULL);
	SetConsoleTextAttribute(hOutput, wOldAttribute);
	return dwWritten;
}

int _stdcall HeliumOutput::out(LPCSTR sOut, WCHAR wTextAttribute)
{
	HANDLE hOutput;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	WORD wOldAttribute;
	DWORD dwWritten, temp;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOutput, &csbiInfo);
	wOldAttribute = csbiInfo.wAttributes;
	SetConsoleTextAttribute(hOutput, wTextAttribute);
	WriteFile(hOutput, sOut, lstrlenA(sOut), &dwWritten, NULL);
	SetConsoleTextAttribute(hOutput, wOldAttribute);
	return dwWritten;
}
