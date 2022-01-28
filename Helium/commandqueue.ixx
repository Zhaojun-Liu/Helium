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
	}
}