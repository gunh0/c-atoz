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
	SOCKET sockClient = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sockClient)
		return -1;

	sockaddr_in addr		= { 0, };
	addr.sin_family			= AF_INET;
	addr.sin_addr.s_addr	= inet_addr("127.0.0.1");
	addr.sin_port			= ::htons(1004);
	int nRet = ::connect(sockClient, (sockaddr*)&addr, sizeof(addr));
	if (SOCKET_ERROR == nRet)
		return -1;

	char szBuff[256] = { 0, };
	int nRead = ::recv(sockClient, szBuff, 256, 0);
	printf("RECVED: %s", szBuff);

	std::string strSend = "I'am a client\n";
	int nSent = ::send(sockClient, strSend.c_str(), strSend.length(), 0);

	::closesocket(sockClient);
    return 0;
}

