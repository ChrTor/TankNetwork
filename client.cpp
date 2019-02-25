#include "client.h"
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

Client::Client() {

	pingTimer = 3.0f;
	m_MyId = -1;
	for (int i = 0; i < 4; i++)
	{
		int id = 0;
		m_Ids.emplace_back(id);
	}
}

Client::~Client() {

}

void Client::PingServer() {

	WinSockStart winsock;

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		on_socket_error();
	}

	sockaddr_in m_server_addr;
	m_server_addr.sin_family = AF_INET;
	m_server_addr.sin_port = htons(4444);
	m_server_addr.sin_addr.S_un.S_un_b.s_b1 = 127;
	m_server_addr.sin_addr.S_un.S_un_b.s_b2 = 0;
	m_server_addr.sin_addr.S_un.S_un_b.s_b3 = 0;
	m_server_addr.sin_addr.S_un.S_un_b.s_b4 = 1;

	if (connect(sock, (const sockaddr *)&m_server_addr, sizeof(struct sockaddr_in)) != 0)
		close_and_socket_error(sock);

	char request[] = "Ping,";
	int result = send(sock, request, sizeof(request), 0);
	if (result == SOCKET_ERROR)
	{
		on_socket_error();

		shutdown(sock, SD_BOTH);
		closesocket(sock);
	}

	printf("<- %s\n", request);

	char response[128] = {};
	result = recv(sock, response, sizeof(response) - 1, 0);
	if (result == SOCKET_ERROR)
	{
		on_socket_error();

		shutdown(sock, SD_BOTH);
		closesocket(sock);
	}
	else if (result == 0) // half-closed
	{
		on_socket_error();

		shutdown(sock, SD_BOTH);
		closesocket(sock);
	}
	else
	{
		// Area Ending
		shutdown(sock, SD_BOTH);
		closesocket(sock);


		response[result] = '\0';
		printf("-> %s\n", response);

		// Problem Area
		std::vector<char *> components = splitString(response);
		m_ServerName[0] = '\0';
		strcat_s(m_ServerName, components[0]);
		m_ActivePlayers = components[1][0] - '0';

		std::string sum(components[2]);
		std::stringstream str_sum(sum);
		int int_sum;
		str_sum >> int_sum;
		m_TimeRemaining = int_sum;
	}
}

void Client::Connect() {
	WinSockStart winsock;

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		on_socket_error();
	}
	sockaddr_in m_server_addr;
	m_server_addr.sin_family = AF_INET;
	m_server_addr.sin_port = htons(4444);
	m_server_addr.sin_addr.S_un.S_un_b.s_b1 = 127;
	m_server_addr.sin_addr.S_un.S_un_b.s_b2 = 0;
	m_server_addr.sin_addr.S_un.S_un_b.s_b3 = 0;
	m_server_addr.sin_addr.S_un.S_un_b.s_b4 = 1;

	if (connect(sock, (const sockaddr *)&m_server_addr, sizeof(struct sockaddr_in)) != 0)
		close_and_socket_error(sock);

	char request[] = "C,";
	int result = send(sock, request, sizeof(request), 0);
	if (result == SOCKET_ERROR)
	{
		on_socket_error();

		shutdown(sock, SD_BOTH);
		closesocket(sock);
	}

	printf("<- %s\n", request);

	char response[128] = {};
	result = recv(sock, response, sizeof(response) - 1, 0);
	if (result == SOCKET_ERROR)
	{
		on_socket_error();

		shutdown(sock, SD_BOTH);
		closesocket(sock);
	}
	else if (result == 0) // half-closed
	{
		on_socket_error();

		shutdown(sock, SD_BOTH);
		closesocket(sock);
	}
	else
	{
		 //Area Ending
		shutdown(sock, SD_BOTH);
		closesocket(sock);

		response[result] = '\0';
		printf("-> %s\n", response);

		 //Problem Area
		std::vector<char *> components = splitString(response);

		if (components[0][0] != m_MyId)
		{
			int newId = components[0][0] - '0';
			SetPersonalID(newId);
		}

		for (int player = 0; player < 4; player++)
		{
			int ready = 0;
			ready = components[player + 1][0] - '0';
			if (ready == 1)
			{
				if (GetReadyPlayers(player) == 0)
				{
					SetReadyPlayers(player, ready);
				}
			}
		}
	}
}
void Client::Connect_Ping() {
	WinSockStart winsock;

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		on_socket_error();
	}
	sockaddr_in m_server_addr;
	m_server_addr.sin_family = AF_INET;
	m_server_addr.sin_port = htons(4444);
	m_server_addr.sin_addr.S_un.S_un_b.s_b1 = 127;
	m_server_addr.sin_addr.S_un.S_un_b.s_b2 = 0;
	m_server_addr.sin_addr.S_un.S_un_b.s_b3 = 0;
	m_server_addr.sin_addr.S_un.S_un_b.s_b4 = 1;

	if (connect(sock, (const sockaddr *)&m_server_addr, sizeof(struct sockaddr_in)) != 0)
		close_and_socket_error(sock);

	char request[128];
	char delim = ',';
	std::string code;
	code = 'p';
	code += delim;
	code += (char)m_MyId;
	code += delim;
	for (int i = 0; i < 4; i++)
	{
		code += (char)m_Ids[i] + '0';
		code += delim;
	}
	strcpy_s(request, sizeof(request), code.c_str());


	int result = send(sock, request, sizeof(request), 0);
	if (result == SOCKET_ERROR)
	{
		on_socket_error();

		shutdown(sock, SD_BOTH);
		closesocket(sock);
	}

	printf("<- %s\n", request);

	char response[128] = {};
	result = recv(sock, response, sizeof(response) - 1, 0);
	if (result == SOCKET_ERROR)
	{
		on_socket_error();

		shutdown(sock, SD_BOTH);
		closesocket(sock);
	}
	else if (result == 0) // half-closed
	{
		on_socket_error();

		shutdown(sock, SD_BOTH);
		closesocket(sock);
	}
	else
	{
		//Area Ending
		shutdown(sock, SD_BOTH);
		closesocket(sock);

		response[result] = '\0';
		printf("-> %s\n", response);

		//Problem Area
		std::vector<char *> components = splitString(response);

		for (int player = 0; player < 4; player++)
		{
			int ready = 0;
			ready = components[player][0] - '0';
			if (GetReadyPlayers(player) != ready)
			{
				SetReadyPlayers(player, ready);
			}
		}
	}
}

void Client::Running(std::vector<User> &users) {
	WinSockStart winsock;

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		on_socket_error();
	}
	sockaddr_in m_server_addr;
	m_server_addr.sin_family = AF_INET;
	m_server_addr.sin_port = htons(4444);
	m_server_addr.sin_addr.S_un.S_un_b.s_b1 = 127;
	m_server_addr.sin_addr.S_un.S_un_b.s_b2 = 0;
	m_server_addr.sin_addr.S_un.S_un_b.s_b3 = 0;
	m_server_addr.sin_addr.S_un.S_un_b.s_b4 = 1;

	char request[128];
	int currentNumber;
	
	char delim[2] = { ',', '\0' };

	// Here it is!
	for (auto &P : users) {
		 char count[3];
		 // Pos
		 sprintf_s(count, "%d", P.GetPosX());
		 strcat_s(request, sizeof(request), count);
		 strcat_s(request, sizeof(request), delim);

		 sprintf_s(count, "%d", P.GetPosY());
		 strcat_s(request, sizeof(request), count);
		 strcat_s(request, sizeof(request), delim);

		 // Dir
		 sprintf_s(count, "%d", P.GetMoveDirX());
		 strcat_s(request, sizeof(request), count);
		 strcat_s(request, sizeof(request), delim);

		 sprintf_s(count, "%d", P.GetMoveDirY());
		 strcat_s(request, sizeof(request), count);
		 strcat_s(request, sizeof(request), delim);

		 for (auto &I : P.GetInput()) {
			 sprintf_s(count, "%d", I);
			 strcat_s(request, sizeof(request), count);
			 strcat_s(request, sizeof(request), delim);
		 }

		 sprintf_s(count, "%d", P.GetMouseX());
		 strcat_s(request, sizeof(request), count);
		 strcat_s(request, sizeof(request), delim);

		 sprintf_s(count, "%d", P.GetMouseY());
		 strcat_s(request, sizeof(request), count);
		 strcat_s(request, sizeof(request), delim);

		 for (auto &BP : P.GetBulletPos()) {
			 sprintf_s(count, "%d", BP.x);
			 strcat_s(request, sizeof(request), count);
			 strcat_s(request, sizeof(request), delim);

			 sprintf_s(count, "%d", BP.y);
			 strcat_s(request, sizeof(request), count);
			 strcat_s(request, sizeof(request), delim);
		 }

		 for (auto &BD : P.GetBulletDir()) {
			 sprintf_s(count, "%d", BD.x);
			 strcat_s(request, sizeof(request), count);
			 strcat_s(request, sizeof(request), delim);

			 sprintf_s(count, "%d", BD.y);
			 strcat_s(request, sizeof(request), count);
			 strcat_s(request, sizeof(request), delim);
		 }
	}

	if (connect(sock, (const sockaddr *)&m_server_addr, sizeof(struct sockaddr_in)) != 0)
		close_and_socket_error(sock);

	int result = send(sock, request, sizeof(request), 0);
	if (result == SOCKET_ERROR)
	{
		on_socket_error();

		shutdown(sock, SD_BOTH);
		closesocket(sock);
	}

	printf("<- %s\n", request);

	char response[128] = {};
	result = recv(sock, response, sizeof(response) - 1, 0);
	if (result == SOCKET_ERROR)
	{
		on_socket_error();

		shutdown(sock, SD_BOTH);
		closesocket(sock);
	}
	else if (result == 0) // half-closed
	{
		on_socket_error();

		shutdown(sock, SD_BOTH);
		closesocket(sock);
	}
	else
	{
		//Area Ending
		shutdown(sock, SD_BOTH);
		closesocket(sock);

		response[result] = '\0';
		printf("-> %s\n", response);

		//Problem Area
		std::vector<char *> components = splitString(response);
		for (int i = 0; i < PLAYER_COUNT; i++)
		{
			for (int j = 0; j < DATA_COUNT; j++)
			{
				m_PlayerData[i][j] = components[i][j];
			}
		}

	}
}

void Client::Disconnect() {
	WinSockStart winsock;

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		on_socket_error();
	}
	sockaddr_in m_server_addr;
	m_server_addr.sin_family = AF_INET;
	m_server_addr.sin_port = htons(4444);
	m_server_addr.sin_addr.S_un.S_un_b.s_b1 = 127;
	m_server_addr.sin_addr.S_un.S_un_b.s_b2 = 0;
	m_server_addr.sin_addr.S_un.S_un_b.s_b3 = 0;
	m_server_addr.sin_addr.S_un.S_un_b.s_b4 = 1;

	if (connect(sock, (const sockaddr *)&m_server_addr, sizeof(struct sockaddr_in)) != 0)
		close_and_socket_error(sock);

	char one = (char)m_MyId + '0';
	char delim = ',';
	char sdf = 'D';
	std::string code;
	code = sdf;
	code += delim;
	code += one;
	code += delim;


	char request[128] = {};

	strcpy_s(request, sizeof(request), code.c_str());

	int result = send(sock, request, sizeof(request), 0);
	if (result == SOCKET_ERROR)
	{
		on_socket_error();

		shutdown(sock, SD_BOTH);
		closesocket(sock);
	}

	printf("<- %s\n", request);

	char response[128] = {};
	result = recv(sock, response, sizeof(response) - 1, 0);
	if (result == SOCKET_ERROR)
	{
		on_socket_error();

		shutdown(sock, SD_BOTH);
		closesocket(sock);
	}
	else if (result == 0) // half-closed
	{
		on_socket_error();

		shutdown(sock, SD_BOTH);
		closesocket(sock);
	}
	else
	{
		//Area Ending
		shutdown(sock, SD_BOTH);
		closesocket(sock);

		response[result] = '\0';
		printf("-> %s\n", response);

		//Problem Area
		std::vector<char *> components = splitString(response);

		if (components[0][0] - '0' == 1)
		{
			int reset = -1;
			SetPersonalID(reset);
			for (auto I : m_Ids) {
				I = 0;
			}
		}
	}
}

void Client::SetPersonalID(int &id) {
	m_MyId = id;
}
int Client::GetPersonalID() {
	return m_MyId;
}
void Client::SetReadyPlayers(int id, int &ready) {
	if (m_Ids[id] != ready)
	{
		m_Ids[id] = ready;
	}
}
int Client::GetReadyPlayers(int id) {
	return m_Ids[id];
}

