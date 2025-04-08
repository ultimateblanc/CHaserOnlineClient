#include "../include/CHaser_Client.h"

void CHaser::Client::Init(const std::string _proxyHost, const std::string _proxyPort, const std::string _targetHost, const std::string _targetPort) {

	proxyHost = _proxyHost;
	proxyPort = _proxyPort;
	targetHost = _targetHost;
	targetPort = _targetPort;

	if (!Socket::Init(_proxyHost, _proxyPort)) {

		throw std::runtime_error("初期化に失敗");
	}
}

std::string CHaser::Client::Command(const std::string command, const std::string params) {

	int count = 0;
	std::string sendBuf, recvBuf, sessionIDParam;

	while (!(Socket::Create() && Socket::Connect())) {
		
		if (!Socket::Next()) {

			throw std::runtime_error("接続に失敗");
		}
	}

	if (!sessionID.empty()) {

		sessionIDParam = ";jsessionid=" + sessionID;
	}

	sendBuf =  "GET http://" + targetHost + ":" + targetPort + "/CHaserOnline003/user/" + command + sessionIDParam + "?" + params + " HTTP/1.1\r\n";
	sendBuf += "Host: " + targetHost + ":" + targetPort + "\r\n";
	sendBuf += "Cookie: jsession=" + sessionID + "\r\n";
	sendBuf += "User-Agent: CHaserOnlineClient/2024\r\n";
	sendBuf += "Connection: close\r\n";
	sendBuf += "\r\n";

	while (!Socket::Send(sendBuf)) {

		count++;

		if (10 < count) {

			throw std::runtime_error("送信に失敗");
		}
	}

	/*count = 0;

	while (!Socket::Shutdown()) {

		count++;

		if (10 < count) {

			throw std::runtime_error("シャットダウンに失敗");
		}
	}*/

	count = 0;

	while (!Socket::Recv(recvBuf)) {

		count++;

		recvBuf.clear();

		if (10 < count) {

			throw std::runtime_error("受信に失敗");
		}	
	}

	return recvBuf;
}

void CHaser::Client::UserCheck(const std::string username, const std::string password) {

	int count = 0;
	std::string recvBuf;

	while (1) {

		count++;

		if (10 < count) {

			throw std::runtime_error("ユーザー認証に失敗");
		}

		recvBuf = Command("UserCheck", "user=" + username + "&pass=" + password);

		if (recvBuf.find("200 OK") == std::string::npos || recvBuf.find("roomNumber=") == std::string::npos) {

			continue;
		}

		sessionID = Utils::ExtractSessionID(recvBuf);

		if (!sessionID.empty()) {

			break;
		}
	}
}

void CHaser::Client::RoomNumberCheck(const std::string roomNumber) {

	int count = 0;
	std::string recvBuf;

	while (1) {

		count++;

		if (10 < count) {

			throw std::runtime_error("ルーム接続に失敗");
		}

		recvBuf = Command("RoomNumberCheck", "roomNumber=" + roomNumber);

		if (recvBuf.find("200 OK") != std::string::npos && recvBuf.find("command1=") != std::string::npos) {

			break;
		}
	}
}

std::string CHaser::Client::GetReadyCheck(const std::string getReady) {

	int count = 0;
	std::string recvBuf, returnCode;

	while (1) {

		count++;

		if (10 < count) {

			throw std::runtime_error("準備コマンドの送信に失敗");
		}

		recvBuf = Command("GetReadyCheck", "command1=" + getReady);

		if (recvBuf.find("200 OK") == std::string::npos || recvBuf.find("GetReady ReturnCode=") == std::string::npos) {

			continue;
		}

		returnCode = Utils::ExtractReturnCode(recvBuf);

		if (!returnCode.empty()) {

			break;
		}
	}

	return returnCode;
}

std::string CHaser::Client::CommandCheck(const std::string command) {

	int count = 0;
	std::string recvBuf, returnCode;

	while (1) {

		count++;

		if (10 < count) {

			throw std::runtime_error("行動コマンドの送信に失敗");
		}

		recvBuf = Command("CommandCheck", "command2=" + command);

		if (recvBuf.find("200 OK") == std::string::npos || recvBuf.find("Action ReturnCode=") == std::string::npos) {

			continue;
		}

		returnCode = Utils::ExtractReturnCode(recvBuf);

		if (!returnCode.empty()) {

			break;
		}
	}

	return returnCode;
}

void CHaser::Client::EndCommandCheck() {

	int count = 0;
	std::string recvBuf;

	while (1) {

		count++;

		if (10 < count) {

			throw std::runtime_error("終了コマンドの送信に失敗");
		}

		recvBuf = Command("EndCommandCheck", "command3=%23");

		if (recvBuf.find("200 OK") != std::string::npos && recvBuf.find("command1=") != std::string::npos) {

			break;
		}
	}
}

CHaser::Client client;