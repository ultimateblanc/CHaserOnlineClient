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

		const std::string arg = argv[i];
		
		if (arg[0] == '-' && i + 1 < argc) {
			
			std::string option = arg;
			options[option] = argv[++i];
		}
		else if (arg.find("http") != std::string::npos) {

			options["url"] = arg;
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

int CHaser::Utils::ExtractStatusCode(const std::string buf) {

	std::smatch m;
	std::regex r(R"(HTTP/1.1 (\d{3}) )");
	int status;

	std::regex_search(buf, m, r);

	try {

		status = std::stoi(m[1].str());
	}
	catch (const std::invalid_argument&) {

		status = -1;
	}
	catch (const std::out_of_range&) {

		status = -2;
	}

	return status;
}

void CHaser::Utils::Log(const std::string log, LogType type) {

	switch (type) {

	case OK:

		std::cout << "[OK] " << log << std::endl;

		break;

	case ERR:

		std::cerr << "[ERROR] " << log << std::endl;

		break;

	case DEBUG:

		std::cout << "[DEBUG] " << log << std::endl;

		break;

	case CLIENT:

		std::cout << "[CLIENT] " << log << std::endl;

		break;

	default:

		std::cout << "[CLIENT] " << log << std::endl;

		break;
	}
}