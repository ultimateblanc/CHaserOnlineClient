#include "include/CHaser_Main.h"

int main() {

	//����9�}�X�̏��
	std::string returnCode;

	while (1) {

		//�����R�}���h
		returnCode = client.GetReadyCheck("gr");
		std::cout << returnCode << std::endl;

		//�s���R�}���h�ƏI���R�}���h
		returnCode = client.FullCommandCheck("wu");
		std::cout << returnCode << std::endl;
	}

	return 0;
}