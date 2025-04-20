#include "../include/CHaser_Client.h"

void CHaser::Client::Init(const std::string _proxyHost, const std::string _proxyPort, const std::string _targetHost, const std::string _targetPort) {

	proxyHost = _proxyHost;
	proxyPort = _proxyPort;
	targetHost = _targetHost;
	targetPort = _targetPort;

	if (!Socket::Init(_proxyHost, _proxyPort)) {

		throw std::runtime_error("�N���C�A���g�������Ɏ��s");
	}
}

std::string CHaser::Client::Command(const std::string command, const std::string params) {

	int count = 0;
	std::string sendBuf, recvBuf, sessionIDParam;

	while (!(Socket::Create() && Socket::Connect())) {
		
		if (!Socket::Next()) {

			throw std::runtime_error("�T�[�o�[�ڑ��Ɏ��s");
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

			throw std::runtime_error("�f�[�^���M�Ɏ��s");
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

		if (ATTEMPT_LIMIT < count) {

			throw std::runtime_error("�f�[�^��M�Ɏ��s");
		}	
	}

	return recvBuf;
}

void CHaser::Client::UserCheck(const std::string username, const std::string password) {

	int count = 0, status;
	std::string recvBuf;

	while (1) {

		if (_kbhit() && _getch() == (int)'q') {

			throw std::runtime_error("�����I�����܂���");
		}

		recvBuf = Command("UserCheck", "user=" + username + "&pass=" + password);
		
		status = Utils::ExtractStatusCode(recvBuf);

		if (200 <= status && status < 300) {

			if (recvBuf.find("roomNumber=") != std::string::npos) {

				sessionID = Utils::ExtractSessionID(recvBuf);

				if (!sessionID.empty()) {

					break;
				}
			}
		}
		else {

			Utils::Log("�����ȃ��X�|���X����M���܂��� �X�e�[�^�X�R�[�h: " + std::to_string(status), Utils::ERR);

			count++;
		}

		if (ATTEMPT_LIMIT <= count) {

			throw std::runtime_error("���[�U�[�F�؂Ɏ��s���܂���");
		}
	}
}

void CHaser::Client::RoomNumberCheck(const std::string roomNumber) {

	int count = 0, status;
	std::string recvBuf;

	while (1) {

		if (_kbhit() && _getch() == (int)'q') {

			throw std::runtime_error("�����I�����܂���");
		}

		recvBuf = Command("RoomNumberCheck", "roomNumber=" + roomNumber);

		status = Utils::ExtractStatusCode(recvBuf);

		if (200 <= status && status < 300) {

			if (recvBuf.find("command1=") != std::string::npos) {

				break;
			}
		}
		else {

			Utils::Log("�����ȃ��X�|���X����M���܂��� �X�e�[�^�X�R�[�h: " + std::to_string(status), Utils::ERR);

			count++;
		}

		if (ATTEMPT_LIMIT <= count) {

			throw std::runtime_error("���[���ڑ��Ɏ��s���܂���");
		}
	}
}

std::string CHaser::Client::GetReadyCheck(const std::string getReady) {

	int count = 0, status;
	std::string recvBuf, returnCode;

	while (1) {

		if (_kbhit() && _getch() == (int)'q') {

			throw std::runtime_error("�����I�����܂���");
		}

		recvBuf = Command("GetReadyCheck", "command1=" + getReady);

		status = Utils::ExtractStatusCode(recvBuf);

		if (200 <= status && status < 300) {

			if (recvBuf.find("GetReady ReturnCode=") != std::string::npos) {

				returnCode = Utils::ExtractReturnCode(recvBuf);

				if (!returnCode.empty()) {

					break;
				}
			}
		}
		else {

			Utils::Log("�����ȃ��X�|���X����M���܂��� �X�e�[�^�X�R�[�h: " + std::to_string(status), Utils::ERR);

			count++;
		}

		if (ATTEMPT_LIMIT <= count) {

			throw std::runtime_error("�����R�}���h�̑��M�Ɏ��s���܂���");
		}
	}

	return returnCode;
}

std::string CHaser::Client::CommandCheck(const std::string command) {

	int count = 0, status;
	std::string recvBuf, returnCode;

	while (1) {

		if (_kbhit() && _getch() == (int)'q') {

			throw std::runtime_error("�����I�����܂���");
		}

		recvBuf = Command("CommandCheck", "command2=" + command);

		status = Utils::ExtractStatusCode(recvBuf);

		if (200 <= status && status < 300) {

			if (recvBuf.find("Action ReturnCode=") != std::string::npos) {

				returnCode = Utils::ExtractReturnCode(recvBuf);

				if (!returnCode.empty()) {

					break;
				}
			}
		}
		else {

			Utils::Log("�����ȃ��X�|���X����M���܂��� �X�e�[�^�X�R�[�h: " + std::to_string(status), Utils::ERR);

			count++;
		}

		if (ATTEMPT_LIMIT <= count) {

			throw std::runtime_error("�s���R�}���h�̑��M�Ɏ��s���܂���");
		}
	}

	return returnCode;
}

void CHaser::Client::EndCommandCheck() {

	int count = 0, status;
	std::string recvBuf;

	while (1) {

		if (_kbhit() && _getch() == (int)'q') {

			throw std::runtime_error("�����I�����܂���");
		}

		recvBuf = Command("EndCommandCheck", "command3=%23");

		status = Utils::ExtractStatusCode(recvBuf);

		if (200 <= status && status < 300) {

			if (recvBuf.find("command1=") != std::string::npos) {

				break;
			}
		}
		else {

			Utils::Log("�����ȃ��X�|���X����M���܂��� �X�e�[�^�X�R�[�h: " + std::to_string(status), Utils::ERR);

			count++;
		}
		
		if (ATTEMPT_LIMIT <= count) {

			throw std::runtime_error("�I���R�}���h�̑��M�Ɏ��s���܂���");
		}
	}
}

std::string CHaser::Client::FullCommandCheck(const std::string command) {

	std::string returnCode = CommandCheck(command);
	EndCommandCheck();

	return returnCode;
}

CHaser::Client client;