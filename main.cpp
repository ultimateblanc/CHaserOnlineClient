#include "include/CHaser_Main.h"

int main() {

	//周囲9マスの情報
	std::string returnCode;

	while (1) {

		//準備コマンド
		returnCode = client.GetReadyCheck("gr");
		std::cout << returnCode << std::endl;

		//行動コマンドと終了コマンド
		returnCode = client.FullCommandCheck("wu");
		std::cout << returnCode << std::endl;
	}

	return 0;
}