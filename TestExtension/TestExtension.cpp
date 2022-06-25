// TestExtension.cpp : 定义 DLL 的导出函数。
//

#include "pch.h"
#include "framework.h"
#include "TestExtension.h"

using namespace std;
using namespace HeliumAPI;

namespace TestExtension {
	extern "C" TESTEXTENSION_API int ExtensionLoad() {
		cout << "Hello World from TestExtension's ExtensionLoad()!" << endl;
		HeliumExtensionDebugPrint("Hello World!");
		return 0;
	}
}
