#include "include/CHaser_Main.h"

int main() {

	while (1) {

		client.GetReadyCheck("gr");
		client.CommandCheck("wu");
		client.EndCommandCheck();
	}

	return 0;
}