#pragma once

#ifndef _H_SHELL
#define _H_SHELL

#include<conio.h>
#include<iostream>
#include<Windows.h>
#include<thread>

#include"logger.h"
#include"commands.h"

#define IsKeyPressed(nVirtKey) ((GetKeyState(nVirtKey) & (1<<(sizeof(SHORT)*8-1))) != 0)

using namespace std;

int ShellInputThread();
int StartShell();

#endif // !_H_SHELL
