#include"errorexit.h"

namespace Helium {
	void HeliumErrorExit(bool ispause, bool uselogger, string str, ...) {
		va_list arglist;

		if (uselogger) {
			HeliumLogger logger("HeliumErrorExit");
			HeliumEndline hendl;
			va_start(arglist, str);
			logger << HLL::LL_CRIT << arglist << hendl;
			va_end(arglist);
		}
		else {
			va_start(arglist, str);
			cout << arglist << endl;
			va_end(arglist);
		}

		spdlog::drop_all();
		_flushall();
		if (ispause) system("pause");
		exit(EXIT_FAILURE);
	}
	void HeliumError_exit(bool ispause, bool uselogger, string str, ...) {
		va_list arglist;

		if (uselogger) {
			HeliumLogger logger("HeliumErrorExit");
			HeliumEndline hendl;
			va_start(arglist, str);
			logger << HLL::LL_CRIT << arglist << hendl;
			va_end(arglist);
		}
		else {
			va_start(arglist, str);
			cout << arglist << endl;
			va_end(arglist);
		}

		spdlog::drop_all();
		if (ispause) system("pause");
		_exit(EXIT_FAILURE);
	}
}