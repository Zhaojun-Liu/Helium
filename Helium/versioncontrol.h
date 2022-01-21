#pragma once

#ifndef _H_VERSIONCONTROL
#define _H_VERSIONCONTROL

#include<string>
#include<strstream>

#define HELIUM_MAJORVER 0
#define HELIUM_MINORVER 6
#define HELIUM_FIX 2
#define HELIUM_DEVSTAT "Pre-Alpha"

namespace Helium {
	using namespace std;

	struct HeliumVersion {
		unsigned int major;
		unsigned int minor;
		unsigned int fix;

		string GetStringVersion() {
			strstream sstr;
			string temp, ret;
			sstr << this->major;
			sstr >> temp;
			ret.append(temp).append(".");
			sstr.clear();

			sstr << this->minor;
			sstr >> temp;
			ret.append(temp).append(".");
			sstr.clear();

			sstr << this->fix;
			sstr >> temp;
			ret.append(temp);
			sstr.clear();

			return ret;
		}

		bool operator==(HeliumVersion h) {
			if (this->major == h.major
				&& this->minor == h.minor
				&& this->fix == h.fix) return true;
			return false;
		}

		bool operator<(HeliumVersion h) {
			if (this->major == h.major
				&& this->minor == h.minor
				&& this->fix == h.fix) {
				return false;
			}
			else {
				if (this->major < h.major) {
					return true;
				}
				else if (this->major == h.major) {
					if (this->minor < h.minor) {
						return true;
					}
					else if (this->minor == h.minor) {
						if (this->fix < h.fix) {
							return true;
						}
						else {
							return false;
						}
					}
					else {
						return false;
					}
				}
				else {
					return false;
				}
			}
		}

		bool operator>(HeliumVersion h) {
			if (this->major == h.major
				&& this->minor == h.minor
				&& this->fix == h.fix) {
				return false;
			}
			else {
				if (this->major > h.major) {
					return true;
				}
				else if (this->major == h.major) {
					if (this->minor > h.minor) {
						return true;
					}
					else if (this->minor == h.minor) {
						if (this->fix > h.fix) {
							return true;
						}
						else {
							return false;
						}
					}
					else {
						return false;
					}
				}
				else {
					return false;
				}
			}
		}

		bool operator>=(HeliumVersion h) {

		}

		bool operator<=(HeliumVersion h) {

		}
	};
}

#endif // !_H_VERSIONCONTROL
