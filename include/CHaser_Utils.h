#ifndef CHASER_UTILS_H
#define CHASER_UTILS_H

#include <string>
#include <regex>
#include <unordered_map>
#include <iostream>
#include <tuple>

namespace CHaser {

	namespace Utils {

		std::string ExtractSessionID(const std::string buf);
		std::string ExtractReturnCode(const std::string buf);
		std::string ExtractHost(const std::string buf);
		std::unordered_map<std::string, std::string> GetOptions(int argc, char** argv);
		std::tuple<std::string, std::string> SplitHostPort(const std::string buf);
	}
}

#endif