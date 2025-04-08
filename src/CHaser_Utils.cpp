#include "../include/CHaser_Utils.h"

std::string CHaser::Utils::ExtractSessionID(const std::string buf) {

	std::smatch m;
	std::regex r(R"(JSESSIONID=([^;]+))");

	std::regex_search(buf, m, r);

	return m[1].str();
}

std::string CHaser::Utils::ExtractReturnCode(const std::string buf) {

	std::smatch m;
	std::regex r(R"(ReturnCode=([^\n]+))");

	std::regex_search(buf, m, r);

	return m[1].str();
}