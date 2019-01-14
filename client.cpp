#include "client.h"
#include <WS2tcpip.h>
#include <iphlpapi.h>
#include <Windows.h>
#include <vector>
#include <iostream>
#include <sstream>

#pragma comment (lib, "ws2_32.lib")
#pragma comment (lib, "iphlpapi.lib")

static int
on_socket_error() {
	int error_code = WSAGetLastError();
	printf("socket error: %d\n", error_code);
	return -1;
}
static int
close_and_socket_error(SOCKET sock) {
	on_socket_error();
	closesocket(sock);
	return -1;
}

std::vector<char *> splitString(char in[]) {

	std::vector<char *> parts(0);
	char delim[] = " ,\t\n";
	char *next_token1 = NULL;
	char *token1 = NULL;
	token1 = strtok_s(in, delim, &next_token1);
	while ((token1 != NULL))
	{
		if (token1 != NULL)
		{
			parts.emplace_back(token1);
			printf(" %s\n", token1);
			token1 = strtok_s(NULL, delim, &next_token1);
		}
	}
	return parts;
}



int
ping_server(Connected_Server_Info &serverInfo) {
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
		return on_socket_error();

	struct sockaddr_in server_addr = {};
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(4444);
	server_addr.sin_addr.S_un.S_un_b.s_b1 = 127;
	server_addr.sin_addr.S_un.S_un_b.s_b2 = 0;
	server_addr.sin_addr.S_un.S_un_b.s_b3 = 0;
	server_addr.sin_addr.S_un.S_un_b.s_b4 = 1;

	if (connect(sock, (const sockaddr *)&server_addr, sizeof(struct sockaddr_in)) != 0)
		return close_and_socket_error(sock);

	char request[] = "Ping,";
	int result = send(sock, request, sizeof(request), 0);
	if (result == SOCKET_ERROR)
	{
		on_socket_error();

		shutdown(sock, SD_BOTH);
		closesocket(sock);

		return -1;
	}

	printf("<- %s\n", request);

	char response[128] = {};
	result = recv(sock, response, sizeof(response) - 1, 0);
	if (result == SOCKET_ERROR)
	{
		on_socket_error();

		shutdown(sock, SD_BOTH);
		closesocket(sock);

		return -1;
	}
	else if (result == 0) // half-closed
	{
		on_socket_error();

		shutdown(sock, SD_BOTH);
		closesocket(sock);

		return -1;
	}

	response[result] = '\0';
	printf("-> %s\n", response);

	std::vector<char *> components = splitString(response);

	strcat_s(serverInfo.serverName, components[0]);
	int players = components[1][0] - '0';
	serverInfo.activePlayers = (uint8_t)components[1][0] - '0';
	int sum = atoi(components[2]);
	serverInfo.timeRemaining = sum;

	shutdown(sock, SD_BOTH);
	closesocket(sock);

	return 0;
}

int
run_client() {

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
		return on_socket_error();

	struct sockaddr_in server_addr = {};
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(4444);
	server_addr.sin_addr.S_un.S_un_b.s_b1 = 127;
	server_addr.sin_addr.S_un.S_un_b.s_b2 = 0;
	server_addr.sin_addr.S_un.S_un_b.s_b3 = 0;
	server_addr.sin_addr.S_un.S_un_b.s_b4 = 1;

	if (connect(sock, (const sockaddr *)&server_addr, sizeof(struct sockaddr_in)) != 0)
		return close_and_socket_error(sock);

	char request[] = "Are You There?";
	int result = send(sock, request, sizeof(request), 0);
	if (result == SOCKET_ERROR)
	{
		on_socket_error();

		shutdown(sock, SD_BOTH);
		closesocket(sock);

		return -1;
	}

	printf("<- %s\n", request);

	char response[128] = {};
	result = recv(sock, response, sizeof(response) - 1, 0);
	if (result == SOCKET_ERROR)
	{
		on_socket_error();

		shutdown(sock, SD_BOTH);
		closesocket(sock);

		return -1;
	}
	else if (result == 0) // half-closed
	{
		on_socket_error();

		shutdown(sock, SD_BOTH);
		closesocket(sock);

		return -1;
	}

	response[result] = '\0';
	printf("-> %s\n", response);

	shutdown(sock, SD_BOTH);
	closesocket(sock);

	return 0;
}