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
#include <string>
#include <sstream>
#include "user.h"
#pragma comment (lib, "ws2_32.lib")
#pragma comment (lib, "iphlpapi.lib")

enum ClientStates
{
	WAITING,
	CONN,
	DISCONN,
	PLAY,
	SCORE,
};
enum ClientData {
	// Tank Data
	TANK_POSX,
	TANK_POSY,
	TANK_DIRX,
	TANK_DIRY,
	INPUT_KEY_UP,
	INPUT_KEY_DOWN,
	INPUT_KEY_RIGHT,
	INPUT_KEY_LEFT,
	INPUT_MOUSEX,
	INPUT_MOUSEY, 
	B_ONE_POSX,
	B_ONE_POSY,
	B_ONE_DIRX,
	B_ONE_DIRY,
	B_TWO_POSX,
	B_TWO_POSY,
	B_TWO_DIRX,
	B_TWO_DIRY,
	B_THREE_POSX,
	B_THREE_POSY,
	B_THREE_DIRX,
	B_THREE_DIRY,
	B_FOUR_POSX,
	B_FOUR_POSY,
	B_FOUR_DIRX,
	B_FOUR_DIRY,
	B_FIVE_POSX,
	B_FIVE_POSY,
	B_FIVE_DIRX,
	B_FIVE_DIRY,
	DATA_COUNT,
};
enum Players {
	PLAYER_ONE,
	PLAYER_TWO,
	PLAYER_THREE,
	PLAYER_FOUR,
	PLAYER_COUNT,
};


class Client
{
public:
	Client();
	~Client();

	void PingServer();
	void Connect();
	void Connect_Ping();

	void Running(std::vector<User> &users);

	void Disconnect();

	void SetPersonalID(int &id);
	int GetPersonalID();
	void SetReadyPlayers(int num, int &ready);
	int GetReadyPlayers(int num);

private:
	SOCKET m_sock;
	struct sockaddr_in m_server_addr;

	float pingTimer;
	int m_CurrentState;

	char m_ServerName[50];
	int m_ActivePlayers;
	int m_TimeRemaining;

	int m_MyId;
	std::vector<int> m_Ids;

	std::vector<int> m_PlayerData[4];
};
