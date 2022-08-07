#include"Misc.h"
#include"semver/semver.hpp"
#include"pch.h"

using namespace semver;

namespace HeliumAPI {
	typedef version(*versionptr)(void);

	HELIUMAPI_API version GetHeliumVersion() {
		auto rawptr = HeliumAPIMap.at("GetHeliumVersion");
		versionptr ptr = versionptr(rawptr);
		return ptr();
	}
	HELIUMAPI_API version GetHeliumAPIVersion() {
		return apiver;
	}
}