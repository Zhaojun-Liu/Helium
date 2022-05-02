/*
* Helium is a customizable extension system for Minecraft server.
* You can get the lastest source code and releases of Helium at :
* https://github.com/Minecraft1248/Helium
* ----------------------------------------------------------------------------------------
* Helium Copyright (C) 2021-2022 HeliumDevTeam
*
* This file is a part of Helium
*
* Helium is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Helium is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Helium.  If not, see <https://www.gnu.org/licenses/>.
* ----------------------------------------------------------------------------------------
*/

module;

#include<string>
#include<vector>

export module Helium.CommandQueue;

using namespace std;

export{
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

		_BasicHeliumCommandQueue* _BasicHeliumCommandQueue::GetCommandQueueClassType() {
			return this;
		}
		ShellCommandQueue* ShellCommandQueue::GetCommandQueueClassType() {
			return this;
		}
		RuntimeCommandQueue* RuntimeCommandQueue::GetCommandQueueClassType() {
			return this;
		}
		SaveableCommandQueue* SaveableCommandQueue::GetCommandQueueClassType() {
			return this;
		}
	}
}