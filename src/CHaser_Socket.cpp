#include "../include/CHaser_Socket.h"

bool CHaser::Socket::Init(const std::string host, const std::string port) {

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {

		return false;
	}

	if (getaddrinfo(host.c_str(), port.c_str(), &hints, &result) != 0) {

		return false;
	}

	ptr = result;

	return true;
}

CHaser::Socket::~Socket() {

	Close();

	freeaddrinfo(result);

	WSACleanup();
}

bool CHaser::Socket::Next() {

	if (ptr->ai_next != NULL) {

		ptr = ptr->ai_next;

		return true;
	}

	return false;
}

bool CHaser::Socket::Create() {

	s = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

	if (s == INVALID_SOCKET) {

		return false;
	}

	return true;
}

bool CHaser::Socket::Connect() {

	if (connect(s, ptr->ai_addr, (int)ptr->ai_addrlen) == SOCKET_ERROR) {

		Close();

		return false;
	}

	return true;
}

bool CHaser::Socket::Send(const std::string buf) {

	if (send(s, buf.c_str(), (int)buf.length(), 0) == SOCKET_ERROR) {

		return false;
	}

	return true;
}

bool CHaser::Socket::Shutdown() {

	if (shutdown(s, SD_SEND) == SOCKET_ERROR) {

		return false;
	}

	return true;
}

void CHaser::Socket::Close() {

	if (s != INVALID_SOCKET) {

		closesocket(s);
		s = INVALID_SOCKET;
	}
}

bool CHaser::Socket::Recv(std::string& buf) {

	char tmpBuf[256];
	int recvLen;

	do {
		recvLen = recv(s, tmpBuf, sizeof(tmpBuf), 0);

		if (recvLen > 0) {

			buf.append(tmpBuf, recvLen);
		}
		else if (recvLen < 0) {

			return false;
		}
	} while (recvLen > 0);

	return true;
}