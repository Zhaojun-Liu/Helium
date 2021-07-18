#include"logger.h"

LogFile::LogFile()
{
	if (!isInitalized) {
		time_t t = time(0);
		char time[64], curdir[MAX_PATH];
		strftime(time, sizeof(time), "%Y-%m-%d-%H-%M-%S", localtime(&t));
		string _logfilename;
		_logfilename.append(time).append(".log");
		logfilename = _logfilename;

		GetCurrentDirectory(sizeof(curdir), curdir);
		strcat(curdir, LOG_DIR);
		if (!PathIsDirectory(curdir)) {
			CreateDirectory(curdir, NULL);
		}

		logfilehandle = CreateFile(
			_logfilename.c_str(),
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_WRITE,
			NULL,
			CREATE_NEW,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
		    NULL
			);
		if (logfilehandle == NULL) {
			isInitalized = false;
			return;
		}
		else {
			isInitalized = true;
			return;
		}
	}
	else {
		return ;
	}
}

int LogFile::operator<<(string outstr)
{
	DWORD writedbytes;

	return WriteFile(
		logfilehandle,
		outstr.c_str(),
		outstr.size(),
		&writedbytes,
		NULL
		);
}

HeliumOutput::HeliumOutput()
{
}

int HeliumOutput::out(LPSTR sOut, WCHAR wTextAttribute)
{
	HANDLE hOutput;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	WORD wOldAttribute;
	DWORD dbWritten;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOutput, &csbiInfo);
	wOldAttribute = csbiInfo.wAttributes;
	SetConsoleTextAttribute(hOutput, wTextAttribute);
	WriteFile(hOutput, sOut, lstrlen(sOut), &dbWritten, NULL);
	SetConsoleTextAttribute(hOutput, wOldAttribute);

	log << sOut;

	return dbWritten;
}

int HeliumOutput::out(LPCSTR sOut, WCHAR wTextAttribute)
{
	HANDLE hOutput;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	WORD wOldAttribute;
	DWORD dbWritten;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOutput, &csbiInfo);
	wOldAttribute = csbiInfo.wAttributes;
	SetConsoleTextAttribute(hOutput, wTextAttribute);
	WriteFile(hOutput, sOut, lstrlen(sOut), &dbWritten, NULL);
	SetConsoleTextAttribute(hOutput, wOldAttribute);

	log << sOut;

	return dbWritten;
}
