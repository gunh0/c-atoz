#include "stdafx.h"

struct ST_WSA_INITIALIZE
{
	WSADATA wsaData;
	ST_WSA_INITIALIZE(void)
	{
		::WSAStartup(MAKEWORD(2, 2), &wsaData);
	}

	~ST_WSA_INITIALIZE(void)
	{
		::WSACleanup();
	}
};
static ST_WSA_INITIALIZE g_InitWSA;
  

int main()
{
	int nRet = 0;
	SOCKET sockListen = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sockListen)
		return -1;

	sockaddr_in addr = { 0, };
	addr.sin_family			= AF_INET;
	addr.sin_addr.s_addr	= INADDR_ANY;
	addr.sin_port			= htons(1004);
	nRet = ::bind(sockListen, (sockaddr*)&addr, sizeof(addr));
	if (SOCKET_ERROR == nRet)
		return -1;

	nRet = ::listen(sockListen, 5);

	while (true)
	{
		sockaddr addrRemote;
		int nReadSize = sizeof(addrRemote);
		SOCKET sockConnection = ::accept(sockListen, &addrRemote, &nReadSize);
		printf("connected.\n");

		std::string strSend = "Hello?\n";
		int nSent = ::send(sockConnection, strSend.c_str(), strSend.length(), 0);

		char szBuff[256] = { 0, };
		int nRead = ::recv(sockConnection, szBuff, 256, 0);

		printf("RECVED: %s", szBuff);

		::closesocket(sockConnection);
		printf("disconnected.\n");
	}
    return 0;
}

