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

std::string CHaser::Utils::ExtractHost(const std::string buf) {

	std::smatch m;
	std::regex r(R"(https?://([^/]+))");

	std::regex_search(buf, m, r);

	return m[1].str();
}

std::unordered_map<std::string, std::string> CHaser::Utils::GetOptions(int argc, char** argv) {

	std::unordered_map<std::string, std::string> options;

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-' && i + 1 < argc) {
			std::string option = argv[i];
			options[option] = argv[++i];
		}
	}

	return options;
}

std::tuple<std::string, std::string> CHaser::Utils::SplitHostPort(const std::string buf) {

	std::smatch m;
	std::regex r(R"((.+):(.+))");

	std::regex_search(buf, m, r);

	return std::forward_as_tuple(m[1].str(), m[2].str());
}