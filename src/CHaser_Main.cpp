#include "../include/CHaser_Main.h"

#undef main

int main(int argc, char** argv) {

	int returnVal = 0;

	try {

		client.Init("www7019ug.sakura.ne.jp", "80", "www7019ug.sakura.ne.jp", "80");
		client.UserCheck("cool", "cool");
		client.RoomNumberCheck("6743");

		returnVal = CHaser_Main();
	}
	catch (const std::exception& ex) {

		std::cerr << ex.what() << std::endl;

		return 1;
	}

	return returnVal;
}