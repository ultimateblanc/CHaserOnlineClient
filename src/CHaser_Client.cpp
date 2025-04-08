#include "../include/CHaser_Client.h"

void CHaser::Client::Init(const std::string _proxyHost, const std::string _proxyPort, const std::string _targetHost, const std::string _targetPort) {

	proxyHost = _proxyHost;
	proxyPort = _proxyPort;
	targetHost = _targetHost;
	targetPort = _targetPort;

	if (!Socket::Init(_proxyHost, _proxyPort)) {

		throw std::runtime_error("�������Ɏ��s");
	}
}

std::string CHaser::Client::Command(const std::string command, const std::string params) {

	int count = 0;
	std::string sendBuf, recvBuf, sessionIDParam;

	while (!(Socket::Create() && Socket::Connect())) {
		
		if (!Socket::Next()) {

			throw std::runtime_error("�ڑ��Ɏ��s");
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

			throw std::runtime_error("���M�Ɏ��s");
		}
	}

	/*count = 0;

	while (!Socket::Shutdown()) {

		count++;

		if (10 < count) {

			throw std::runtime_error("�V���b�g�_�E���Ɏ��s");
		}
	}*/

	count = 0;

	while (!Socket::Recv(recvBuf)) {

		count++;

		recvBuf.clear();

		if (10 < count) {

			throw std::runtime_error("��M�Ɏ��s");
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

			throw std::runtime_error("���[�U�[�F�؂Ɏ��s");
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

			throw std::runtime_error("���[���ڑ��Ɏ��s");
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

			throw std::runtime_error("�����R�}���h�̑��M�Ɏ��s");
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

			throw std::runtime_error("�s���R�}���h�̑��M�Ɏ��s");
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

			throw std::runtime_error("�I���R�}���h�̑��M�Ɏ��s");
		}

		recvBuf = Command("EndCommandCheck", "command3=%23");

		if (recvBuf.find("200 OK") != std::string::npos && recvBuf.find("command1=") != std::string::npos) {

			break;
		}
	}
}

CHaser::Client client;