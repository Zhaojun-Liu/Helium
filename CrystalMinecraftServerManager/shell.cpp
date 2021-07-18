#include"shell.h"

HeliumOutput out_sit;

int ShellInputThread() {
	char buf[4096];
	DWORD readbytes;
	memset(buf, '\0', sizeof(buf));

	while (true) {
		if (IsKeyPressed(VK_F10)) {
			HANDLE han_stdin;
			han_stdin = GetStdHandle(STD_INPUT_HANDLE);
			out_sit.out("Helium>", FOREGROUND_INTENSITY | WHITE);
			if (!ReadFile(
				han_stdin,
				buf,
				sizeof(buf),
				&readbytes,
				NULL
			)) {

			}

			if (readbytes < 4096) {
				buf[readbytes + 1] = '\0';
			}

			Debug(buf);
			Debug("\r\n");

			if (isCommand(buf)) {
				NewCommandFromConsole(buf);
			}
			memset(buf, '\0', sizeof(buf));
		}
	}
}

int StartShell()
{
	thread shell_thread(ShellInputThread);
	shell_thread.detach();
	return 0;
}
