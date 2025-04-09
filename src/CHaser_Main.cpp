#include "../include/CHaser_Main.h"

#undef main

int main(int argc, char** argv) {

	int returnVal = 0;
	std::string proxyHost, proxyPort, targetHost, targetPort, username, password, roomNumber;
	std::string url;
	std::unordered_map<std::string, std::string> options;

	if (1 < argc) {
		url = argv[1];
		options = CHaser::Utils::GetOptions(argc, argv);
	}

	std::tie(proxyHost, proxyPort) = CHaser::Utils::SplitHostPort(options["-x"]);
	std::tie(targetHost, targetPort) = CHaser::Utils::SplitHostPort(CHaser::Utils::ExtractHost(url));
	username = options["-u"];
	password = options["-p"];
	roomNumber = options["-r"];

#ifndef PROXY_HOST
#error プロキシのホストが定義されていません
#endif
	if (proxyHost.empty()) proxyHost = PROXY_HOST;

#ifndef PROXY_PORT
#error プロキシのポートが定義されていません
#endif
	if (proxyPort.empty()) proxyPort = PROXY_PORT;

#ifndef TARGET_HOST
#error サーバーのホストが定義されていません
#endif
	if (targetHost.empty()) targetHost = TARGET_HOST;

#ifndef TARGET_PORT
#error サーバーのポートが定義されていません
#endif
	if (targetPort.empty()) targetPort = TARGET_PORT;

#ifndef USERNAME
#error ユーザー名が定義されていません
#endif
	if (username.empty()) username = USERNAME;

#ifndef PASSWORD
#error パスワードが定義されていません
#endif
	if (password.empty()) password = PASSWORD;
	
#ifndef ROOM_NUMBER
#error ルーム番号が定義されていません
#endif
	if (roomNumber.empty()) roomNumber = ROOM_NUMBER;

	std::cout << "プロキシ: " << proxyHost << ":" << proxyPort << std::endl;
	std::cout << "サーバー: " << targetHost << ":" << targetPort << std::endl;
	std::cout << "ユーザー名: " << username << std::endl;
	std::cout << "パスワード: " << password << std::endl;
	std::cout << "ルーム番号: " << roomNumber << std::endl;

	try {

		std::cout << "初期化を開始..." << std::endl;
		client.Init(proxyHost, proxyPort, targetHost, targetPort);

		std::cout << "ユーザー認証を開始..." << std::endl;
		client.UserCheck(username, password);

		std::cout << "ルーム接続を開始..." << std::endl;
		client.RoomNumberCheck(roomNumber);

		std::cout << "メインプログラムを開始..." << std::endl;
		returnVal = CHaser_Main();
	}
	catch (const std::exception& ex) {

		std::cerr << ex.what() << std::endl;

		return 1;
	}

	return returnVal;
}