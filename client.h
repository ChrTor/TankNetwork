#pragma once
#include <stdio.h>
#include <string.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>
#include <Windows.h>
#include <vector>
#include <stdint.h>
#include <stdbool.h>

#pragma comment (lib, "ws2_32.lib")
#pragma comment (lib, "iphlpapi.lib")

struct WinSockStart
{
	WinSockStart() {
		WSAData data = {};
		WSAStartup(MAKEWORD(2, 2), &data);
	}
	~WinSockStart() {
		WSACleanup();
	}
};

struct Connected_Server_Info
{
	char serverName[50];
	uint8_t activePlayers;
	uint8_t timeRemaining;
};


int ping_server(Connected_Server_Info &ServerInfo);
int run_client();
