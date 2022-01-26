#pragma once

#ifndef _H_VERSIONCONTROL
#define _H_VERSIONCONTROL

#include"semver/semver.hpp"

#define HELIUM_MAJORVER 0
#define HELIUM_MINORVER 6
#define HELIUM_PATCHVER 2
#define HELIUM_DEVSTAT prerelease::alpha

namespace Helium {
	using namespace semver;
	constexpr version HeliumVersion{ HELIUM_MAJORVER, HELIUM_MINORVER, HELIUM_PATCHVER, HELIUM_DEVSTAT, 1};
	constexpr version MiniumAPIVersion{ 0, 1, 0, prerelease::alpha };
}
#endif // !_H_VERSIONCONTROL
