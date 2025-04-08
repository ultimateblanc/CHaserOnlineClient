#ifndef CHASER_UTILS_H
#define CHASER_UTILS_H

#include <string>
#include <regex>

namespace CHaser {

	namespace Utils {

		std::string ExtractSessionID(const std::string buf);
		std::string ExtractReturnCode(const std::string buf);
	}
}

#endif