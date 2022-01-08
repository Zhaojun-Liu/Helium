/*
* Helium Pre-Alpha 0.6.1
*
* Helium is a customizable extension system for Minecraft server which is written in C++.
* This project is inspired by the [Fallen-Breath/MCDReforged](https://github.com/Fallen-Breath/MCDReforged).
* We target to provide a liter, faster, and more customizable choice.
* As a trade-off, we sacrifice its portability and the simplicity of writing extensions.
* (we r sry that we haven't finish the first alpha version yet, if u r interested in our project, we recommend u to use mcdr as a temporary alternative)
* This project is licensed by the GPL-3.0-or-later license.
*
* Very very special thank to contributors of the following projects:
* [Fallen-Breath/MCDReforged](https://github.com/Fallen-Breath/MCDReforged)
* [kpeeters/tree.hh](https://github.com/kpeeters/tree.hh)
* [leethomason/tinyxml2](https://github.com/leethomason/tinyxml2/)
* [jcwangxp/Crossline](https://github.com/jcwangxp/Crossline/)
*
* You can get the lastest source code and releases of Helium at :
* https://github.com/Minecraft1248/Helium
*
* -------------------------------------------------------------------------------------------------------------------------------------------------------
* Helium Pre-Alpha 0.6.1
* Copyright (C) 2021-2022 HeliumDevTeam
* This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
* This is free software, and you are welcome to redistribute it
* under certain conditions; type `show c' for details.
* -------------------------------------------------------------------------------------------------------------------------------------------------------
*/

#pragma once

#ifndef _H_COMMANDQUEUE
#define _H_COMMANDQUEUE

#include<string>
#include<vector>

using namespace std;

namespace Helium {
	class _BasicHeliumCommandQueue;

	class ShellCommandQueue;
	class RuntimeCommandQueue;
	class SaveableCommandQueue;

	class _BasicHeliumCommandQueue {
	protected:
		int queuetype;
		int queuestate;
		vector<string>::iterator execit;

		vector<string> originalcommands;
	public:
		virtual _BasicHeliumCommandQueue* GetCommandQueueClassType();
	};
	class ShellCommandQueue : virtual public _BasicHeliumCommandQueue {
	public:
		virtual ShellCommandQueue* GetCommandQueueClassType();
	};
	class RuntimeCommandQueue : virtual public _BasicHeliumCommandQueue {
	public:
		virtual RuntimeCommandQueue* GetCommandQueueClassType();
	};
	class SaveableCommandQueue : virtual public _BasicHeliumCommandQueue {
	public:
		virtual SaveableCommandQueue* GetCommandQueueClassType();
	};
}

#endif // !_H_COMMANDQUEUE

