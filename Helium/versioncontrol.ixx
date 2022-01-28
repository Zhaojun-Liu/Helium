module;

#include"semver/semver.hpp"

export module Helium.VersionControl;

#define HELIUM_MAJORVER 0
#define HELIUM_MINORVER 6
#define HELIUM_PATCHVER 2
#define HELIUM_DEVSTAT prerelease::alpha

using namespace semver;

export{
	namespace Helium {
		constexpr version HeliumVersion{ HELIUM_MAJORVER, HELIUM_MINORVER, HELIUM_PATCHVER, HELIUM_DEVSTAT, 1 };
		constexpr version MiniumAPIVersion{ 0, 1, 0, prerelease::alpha };
	}
}