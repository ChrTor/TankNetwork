#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Main.hpp"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include <vector>
#include "client.h"
#include "user.h"
#include "tank.h"

enum TankData {
	// Tank Data
	TANK_POSX,
	TANK_POSY,
	TANK_DIRX,
	TANK_DIRY,
	TANK_MOUSEX,
	TANK_MOUSEY,
	TANK_DATA_COUNT,
};
enum BulletData {
	ONE_POSX,
	ONE_POSY,
	ONE_DIRX,
	ONE_DIRY,
	TWO_POSX,
	TWO_POSY,
	TWO_DIRX,
	TWO_DIRY,
	THREE_POSX,
	THREE_POSY,
	THREE_DIRX,
	THREE_DIRY,
	FOUR_POSX,
	FOUR_POSY,
	FOUR_DIRX,
	FOUR_DIRY,
	FIVE_POSX,
	FIVE_POSY,
	FIVE_DIRX,
	FIVE_DIRY,
	BULLET_DATA_COUNT,
};

struct Message
{
	std::string Msg;

};

enum states
{
	MENU,
	CONNECTING,
	DISSCONNECTING,
	PLAYING,
	SCOREBOARD,
};

class Game
{
public:
	Game();
	~Game();

	bool Run(float &deltaTime);
	void IncomingPlayerData();
	void SetState(int state);
	int GetState();
	void CreateUsers();
	void SyncReadyPlayers();
private:
	bool ProcessEvents();
	void Update(int _currentState, float deltatime);
	void Draw(int _currentState);

	// Input
	void ResolveInput(InputManager &intput);
	void HandleKeyBoard(InputManager &intput);
	void HandleMouse(InputManager &intput);

	// Create
	void Init(int x, int y, float tankRadius, float bulletRadius);
	void CreateUsers();
	void CreateTanks();
	void CreateMap();
	void CreateCollisionManager(int x, int y, float rankRadius, float bulletRadius);
	void CreateInputContext();




private:
	int m_GameState;
	float m_ServerTimer;
	Client m_Client;

	sf::RenderWindow* m_pWindow = nullptr;
	CollisionManager m_ColManager;
	Map m_Map;

	std::vector<int> m_KeyBoard;
	std::vector<int> m_Mouse;

	int m_MyUser;
	std::vector<User> m_Users;
	std::vector<int> m_UserInfo[4];

	std::vector<Tank> m_tanks;
	std::map<int, Bullet> m_bullets;
};