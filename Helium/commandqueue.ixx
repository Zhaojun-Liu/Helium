/*
* Helium is a customizable extension system for Minecraft server.
* You can get the lastest source code and releases of Helium at :
* https://github.com/Helium-DevTeam/Helium
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

export module Helium.CommandQueue;

import <string>;
import <vector>;
import <list>;
import <any>;
import <memory>;

using namespace std;

export{
	namespace Helium {
		enum HeliumCommandQueueStat {
			EMPTY_QUEUE,
			RUNNING,
			PAUSED,
			DELETED
		};

		class HeliumCommandQueue {
		public:
			~HeliumCommandQueue() {
				this->stat = HeliumCommandQueueStat::DELETED;
			}
			void AddCommandToQueue(const string& cmd);
			int GetCommandQueueStatus() const noexcept;
			void Run();
			void Pause();
			void Delete();
			bool IsQueueEmpty() const noexcept;
			string GetName() const noexcept;
			void SetName(const string& n) noexcept;
		private:
			list<string> cmd_queue;
			HeliumCommandQueueStat stat;
			string name;
		};

		list<shared_ptr<HeliumCommandQueue>> command_queue_list;

		typedef int (*executor_funcptr)(shared_ptr<HeliumCommandQueue> queue_ptr);
		list<shared_ptr<HeliumCommandQueue>>::iterator
			CreateCommandQueue(const string& name, executor_funcptr executor);
		void
			DeleteCommandQueue(list<shared_ptr<HeliumCommandQueue>>::iterator iter);
	}
}

namespace Helium {
	void HeliumCommandQueue::AddCommandToQueue(const string& cmd) {
		this->cmd_queue.push_back(cmd);
	}
	int HeliumCommandQueue::GetCommandQueueStatus() const noexcept {
		return this->stat;
	}
	void HeliumCommandQueue::Run() {
		this->stat = HeliumCommandQueueStat::RUNNING;
	}
	void HeliumCommandQueue::Pause() {
		this->stat = HeliumCommandQueueStat::PAUSED;
	}
	void HeliumCommandQueue::Delete() {
		this->stat = HeliumCommandQueueStat::DELETED;
	}
	bool HeliumCommandQueue::IsQueueEmpty() const noexcept {
		return this->cmd_queue.empty();
	}
	string HeliumCommandQueue::GetName() const noexcept {
		return this->name;
	}
	void HeliumCommandQueue::SetName(const string& n) noexcept {
		this->name = n;
	}

	list<shared_ptr<HeliumCommandQueue>>::iterator CreateCommandQueue(const string& name, executor_funcptr executor) {
		command_queue_list.push_back(make_shared<HeliumCommandQueue>());
		command_queue_list.back()->SetName(name);
		return command_queue_list.end()--;
	}
	void DeleteCommandQueue(list<shared_ptr<HeliumCommandQueue>>::iterator iter) {
		(*iter)->Delete();
	}
}