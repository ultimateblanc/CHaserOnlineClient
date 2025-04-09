#include "include/CHaser_Main.h"

int main() {

	std::string returnCode;

	while (1) {

		returnCode = client.GetReadyCheck("gr");
		std::cout << returnCode << std::endl;

		returnCode = client.CommandCheck("wu");
		std::cout << returnCode << std::endl;

		client.EndCommandCheck();
	}

	return 0;
}