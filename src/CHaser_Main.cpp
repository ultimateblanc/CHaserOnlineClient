#include "../include/CHaser_Main.h"

#undef main

int main(int argc, char** argv) {

	int returnVal = 0;
	std::string proxyHost, proxyPort, targetHost, targetPort, username, password, roomNumber;
	std::unordered_map<std::string, std::string> options;

	if (1 < argc) {
		options = CHaser::Utils::GetOptions(argc, argv);
	}

	std::tie(proxyHost, proxyPort) = CHaser::Utils::SplitHostPort(options["-x"]);
	std::tie(targetHost, targetPort) = CHaser::Utils::SplitHostPort(CHaser::Utils::ExtractHost(options["url"]));
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

	CHaser::Utils::Log("プロキシ: " + proxyHost + ":" + proxyPort, CHaser::Utils::CLIENT);
	CHaser::Utils::Log("サーバー: " + targetHost + ":" + targetPort, CHaser::Utils::CLIENT);
	CHaser::Utils::Log("ユーザー名: " + username, CHaser::Utils::CLIENT);
	CHaser::Utils::Log("パスワード: " + password, CHaser::Utils::CLIENT);
	CHaser::Utils::Log("ルーム番号: " + roomNumber, CHaser::Utils::CLIENT);

	try {

		client.Init(proxyHost, proxyPort, targetHost, targetPort);
		CHaser::Utils::Log("初期化に成功しました", CHaser::Utils::OK);
		
		client.UserCheck(username, password);
		CHaser::Utils::Log("ユーザー認証に成功しました", CHaser::Utils::OK);

		client.RoomNumberCheck(roomNumber);
		CHaser::Utils::Log("ルーム接続に成功しました", CHaser::Utils::OK);

		CHaser::Utils::Log("メインプログラムを開始しました", CHaser::Utils::CLIENT);
		returnVal = CHaser_Main();
	}
	catch (const std::exception& ex) {

		CHaser::Utils::Log(ex.what(), CHaser::Utils::ERR);

		return 1;
	}

	return returnVal;
}