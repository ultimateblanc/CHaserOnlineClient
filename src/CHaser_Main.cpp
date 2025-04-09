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
#error �v���L�V�̃z�X�g����`����Ă��܂���
#endif
	if (proxyHost.empty()) proxyHost = PROXY_HOST;

#ifndef PROXY_PORT
#error �v���L�V�̃|�[�g����`����Ă��܂���
#endif
	if (proxyPort.empty()) proxyPort = PROXY_PORT;

#ifndef TARGET_HOST
#error �T�[�o�[�̃z�X�g����`����Ă��܂���
#endif
	if (targetHost.empty()) targetHost = TARGET_HOST;

#ifndef TARGET_PORT
#error �T�[�o�[�̃|�[�g����`����Ă��܂���
#endif
	if (targetPort.empty()) targetPort = TARGET_PORT;

#ifndef USERNAME
#error ���[�U�[������`����Ă��܂���
#endif
	if (username.empty()) username = USERNAME;

#ifndef PASSWORD
#error �p�X���[�h����`����Ă��܂���
#endif
	if (password.empty()) password = PASSWORD;
	
#ifndef ROOM_NUMBER
#error ���[���ԍ�����`����Ă��܂���
#endif
	if (roomNumber.empty()) roomNumber = ROOM_NUMBER;

	std::cout << "�v���L�V: " << proxyHost << ":" << proxyPort << std::endl;
	std::cout << "�T�[�o�[: " << targetHost << ":" << targetPort << std::endl;
	std::cout << "���[�U�[��: " << username << std::endl;
	std::cout << "�p�X���[�h: " << password << std::endl;
	std::cout << "���[���ԍ�: " << roomNumber << std::endl;

	try {

		std::cout << "���������J�n..." << std::endl;
		client.Init(proxyHost, proxyPort, targetHost, targetPort);

		std::cout << "���[�U�[�F�؂��J�n..." << std::endl;
		client.UserCheck(username, password);

		std::cout << "���[���ڑ����J�n..." << std::endl;
		client.RoomNumberCheck(roomNumber);

		std::cout << "���C���v���O�������J�n..." << std::endl;
		returnVal = CHaser_Main();
	}
	catch (const std::exception& ex) {

		std::cerr << ex.what() << std::endl;

		return 1;
	}

	return returnVal;
}