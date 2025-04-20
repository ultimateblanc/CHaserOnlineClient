#ifndef CHASER_CLIENT_H
#define CHASER_CLIENT_H

#include "../include/CHaser_Socket.h"
#include "../include/CHaser_Utils.h"
#include "../include/CHaser_Defines.h"

#include <iostream>
#include <string>
#include <conio.h>

namespace CHaser {

	class Client : private Socket {

	public:
		void Init(const std::string proxyHost, const std::string proxyPort, const std::string targetHost, const std::string targetPort);
		std::string Command(const std::string command, const std::string params);
		void UserCheck(const std::string username, const std::string password);
		void RoomNumberCheck(const std::string roomNumber);
		std::string GetReadyCheck(const std::string getReady);
		std::string CommandCheck(const std::string command);
		void EndCommandCheck();
		std::string FullCommandCheck(const std::string command);

	private:
		std::string proxyHost, proxyPort, targetHost, targetPort, sessionID;
	};
}

extern CHaser::Client client;

#endif