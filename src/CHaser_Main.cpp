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

	CHaser::Utils::Log("�v���L�V: " + proxyHost + ":" + proxyPort, CHaser::Utils::CLIENT);
	CHaser::Utils::Log("�T�[�o�[: " + targetHost + ":" + targetPort, CHaser::Utils::CLIENT);
	CHaser::Utils::Log("���[�U�[��: " + username, CHaser::Utils::CLIENT);
	CHaser::Utils::Log("�p�X���[�h: " + password, CHaser::Utils::CLIENT);
	CHaser::Utils::Log("���[���ԍ�: " + roomNumber, CHaser::Utils::CLIENT);

	try {

		client.Init(proxyHost, proxyPort, targetHost, targetPort);
		CHaser::Utils::Log("�������ɐ������܂���", CHaser::Utils::OK);
		
		client.UserCheck(username, password);
		CHaser::Utils::Log("���[�U�[�F�؂ɐ������܂���", CHaser::Utils::OK);

		client.RoomNumberCheck(roomNumber);
		CHaser::Utils::Log("���[���ڑ��ɐ������܂���", CHaser::Utils::OK);

		CHaser::Utils::Log("���C���v���O�������J�n���܂���", CHaser::Utils::CLIENT);
		returnVal = CHaser_Main();
	}
	catch (const std::exception& ex) {

		CHaser::Utils::Log(ex.what(), CHaser::Utils::ERR);

		return 1;
	}

	return returnVal;
}