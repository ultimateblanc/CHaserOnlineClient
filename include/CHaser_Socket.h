#ifndef CHASER_SOCKET_H
#define CHASER_SOCKET_H

#include <string>

#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

namespace CHaser {

	class Socket {

	public:
		bool Init(const std::string host, const std::string port);
		~Socket();
		bool Create();
		bool Next();
		bool Connect();
		bool Send(const std::string buf);
		bool Shutdown();
		void Close();
		bool Recv(std::string& buf);

	private:
		struct addrinfo* ptr, * result, hints;
		SOCKET s;
		WSAData wsaData;
	};
}

#endif