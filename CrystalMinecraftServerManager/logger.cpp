#include"logger.h"



int HeliumOutput::write(string outstr)
{
	
		time_t t = time(0);
		char time[64];
		strftime(time, sizeof(time), "%Y-%m-%d", localtime(&t));
		ostringstream s;
		char path[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, path);
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

void HeliumOutput::setTimeStamp(bool stat)
{
	this->enableTimeStamp = stat;
}

HeliumOutput::HeliumOutput()
{
	this->enableTimeStamp = true;
}

int HeliumOutput::info(const char* content)
{
	string content_;
	time_t t = time(0);
	char time[64];
	strftime(time, sizeof(time), "%Y-%m-%d-%H-%M-%S", localtime(&t));
	if(enableTimeStamp) content_ += time;
	content_ += " [INFO] ";
	content_ += content;
	this->write(content_);
	int iWrote = 0;
	if (enableTimeStamp)iWrote += this->out(time, WHITE);
	iWrote += this->out(" [INFO] ", GREEN_FOREGROUND);
	iWrote += this->out(content, WHITE);
	return iWrote;
}

int HeliumOutput::warn(const char* content)
{
	string content_;
	time_t t = time(0);
	char time[64];
	strftime(time, sizeof(time), "%Y-%m-%d-%H-%M-%S", localtime(&t));
	if (enableTimeStamp) content_ += time;
	content_ += " [WARN] ";
	content_ += content;
	this->write(content_);
	int iWrote = 0;
	if (enableTimeStamp) iWrote += this->out(time, WHITE);
	iWrote += this->out(" [WARN] ", YELLOW_FOREGEOUND);
	iWrote += this->out(content, WHITE);
	return iWrote;
}

int HeliumOutput::error(const char* content)
{
	string content_;
	time_t t = time(0);
	char time[64];
	strftime(time, sizeof(time), "%Y-%m-%d-%H-%M-%S", localtime(&t));
	if (enableTimeStamp) content_ += time;
	content_ += " [ERROR] ";
	content_ += content;
	this->write(content_);
	int iWrote = 0;
	if (enableTimeStamp) iWrote += this->out(time, WHITE);
	iWrote += this->out(" [ERROR] ", RED_FOREGROUND);
	iWrote += this->out(content, WHITE);
	return iWrote;
}

int HeliumOutput::fatal(const char* content)
{
	string content_;
	time_t t = time(0);
	char time[64];
	strftime(time, sizeof(time), "%Y-%m-%d-%H-%M-%S", localtime(&t));
	if (enableTimeStamp) content_ += time;
	content_ += " [FATAL] ";
	content_ += content;
	this->write(content_);
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

int HeliumOutput::out(LPSTR sOut, WCHAR wTextAttribute)
{
	HANDLE hOutput;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	WORD wOldAttribute;
	DWORD dwWritten, temp;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOutput, &csbiInfo);
	wOldAttribute = csbiInfo.wAttributes;
	SetConsoleTextAttribute(hOutput, wTextAttribute);
	WriteFile(hOutput, sOut, lstrlen(sOut), &dwWritten, NULL);
	SetConsoleTextAttribute(hOutput, wOldAttribute);
	return dwWritten;
}

int HeliumOutput::out(LPCSTR sOut, WCHAR wTextAttribute)
{
	HANDLE hOutput;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	WORD wOldAttribute;
	DWORD dwWritten, temp;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOutput, &csbiInfo);
	wOldAttribute = csbiInfo.wAttributes;
	SetConsoleTextAttribute(hOutput, wTextAttribute);
	WriteFile(hOutput, sOut, lstrlen(sOut), &dwWritten, NULL);
	SetConsoleTextAttribute(hOutput, wOldAttribute);
	return dwWritten;
}
