#include <SFML/Graphics.hpp>
#include <string>
#include "game.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "tank.h"
#include "map.h"

enum Players
{
	PLAYER_ONE,
	PLAYER_TWO,
	PLAYER_THREE,
	PLAYER_FOUR,
	PLAYER_COUNT,
};

std::string colors[4] = { "Red", "Blue", "Green", "Beige" };

Game::Game() {

	m_pWindow = new sf::RenderWindow({ 1080, 720 }, "Tanks");

	float tankRadius = 35.0f;
	float bulletRadius = 10.0f;

	Init(m_pWindow->getSize().x, m_pWindow->getSize().y, tankRadius, bulletRadius);

	m_ServerTimer = 1.5f;
}
Game::~Game() {
	delete m_pWindow;
	m_pWindow = nullptr;
	m_ColManager.~CollisionManager();
	for (auto &T : m_tanks) {
		for (auto &B : T.GetBulletList()) {
			B.~Bullet();
		}
		T.~Tank();
	}
	m_bullets.clear();
	m_tanks.clear();
	m_Map.~Map();
	ResourceManager::GetInstance()->CleanUp();
	InputManager::GetInstance()->CleanUp();
}

bool Game::Run(float &deltaTime) {

	// Check Events
 	bool isRunning = ProcessEvents();

	// Update
	Update(m_GameState, deltaTime);

	// Draw
	Draw(m_GameState);

	return isRunning;
}

bool Game::ProcessEvents()
{
	sf::Event event;
	while (m_pWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_pWindow->close();
			return false;
		}
		if (event.type == sf::Event::Resized)
		{

		}
	}
	return true;
}

void Game::Update(int _currentState, float deltatime) {

	auto input = InputManager::GetInstance();
	TranslateInput(deltatime);
	sf::Vector2i mousePos = input->GetMousePosition(m_pWindow);

	switch (_currentState)
	{
	case MENU:

		if (input->IsKeyActionTriggered(K_LEFT))
		{
			SetState(CONNECTING);
		}

		if (m_ServerTimer <= 0.0f)
		{
			m_Client.PingServer();			
			m_ServerTimer = 3.0f;
		}
		else
		{
			m_ServerTimer -= 1.0f * deltatime;
		}
		break;
	case CONNECTING:
		if (input->IsKeyActionTriggered(K_RIGHT))
		{
			SetState(DISSCONNECTING);
		}
		if (m_ServerTimer <= 0.0f)
		{
			if (m_MyUser > -1)
			{
				m_Client.Connect_Ping();
				SyncReadyPlayers();

				m_ServerTimer = 3.0f;
			}
			else
			{
				m_Client.Connect();
				int myID = m_Client.GetPersonalID();
				m_MyUser = myID;

				SyncReadyPlayers();

				m_ServerTimer = 3.0f;
			}
		}
		else
		{
			m_ServerTimer -= 1.0f *deltatime;
		}
			break;
	case DISSCONNECTING:
		if (m_Client.GetPersonalID() == -1)
		{
			m_MyUser = -1;
			for (auto u : m_Users) {
				u.Reset();
			}
			SetState(WAITING);
		}
		else
		{
			m_Client.Disconnect();

		}


		break;
	case PLAYING:

		for (auto &T : m_tanks) {
			if (T.GetId() == m_MyUser)
			{
				T.Update(*input, mousePos, deltatime);
			}
			else
			{
				for (auto &U : m_Users) {
					if (T.GetId() == U.GetID())
					{
						T.Update(U, deltatime);
						break;
					}
				}
			}

			if (T.GetKills() == 5)
			{

			}
		}

		m_ColManager.Update(m_tanks, m_Map);

		break;
	case SCOREBOARD:


		break;
	default:
		break;
	}
}

void Game::Draw(int _currentState) {
	m_pWindow->clear();

	switch (_currentState)
	{
	case MENU:


		break;
	case CONNECTING:

		break;
	case DISSCONNECTING:

		break;
	case PLAYING:

		for (auto &T : m_tanks) {
			T.Draw(m_pWindow);
		}
		m_Map.Draw(m_pWindow);

		break;
	case SCOREBOARD:


		break;
	default:
		break;
	}

	m_pWindow->display();
}

void Game::TranslateInput(float deltatime) {

	auto input = InputManager::GetInstance();

	if (input->IsKeyActionTriggered(K_UP)) {

	}
	if (input->IsKeyActionTriggered(K_DOWN)) {

	}
	if (input->IsKeyActionTriggered(K_LEFT)) {

	}
	if (input->IsKeyActionTriggered(K_RIGHT)) {

	}
	if (input->isMouseActionTriggered(M_LEFT))
	{

	}
	if (input->isMouseActionTriggered(M_RIGHT))
	{

	}

}

// Create
void Game::Init(int x, int y, float tankRadius, float bulletRadius) {
	m_GameState = MENU;
	CreateCollisionManager(x, y, tankRadius, bulletRadius);
	CreateMap();
	CreateTanks();
	CreateInputContext();
}

void Game::CreateUsers() {
	m_MyUser = -1;
	for (int i = 0; i < PLAYER_COUNT; i++)
	{
		User newUser;
		newUser.SetID(i);
		m_Users.emplace_back(newUser);
	}
}
void Game::CreateTanks() {
	m_tanks = {};
	m_bullets = {};

	for (int playerId = 0; playerId < PLAYER_COUNT; playerId++)
	{
		Tank newTank;
		sf::Vector2f origin(100.0f + (playerId * 100.0f), 100.0f + (playerId * 100.0f));
		newTank.Init(playerId, origin);
		newTank.SetTexture(ResourceManager::GetInstance()->RequestTexture("Tank_", colors[playerId]),
			ResourceManager::GetInstance()->RequestTexture("Barrel_", colors[playerId]), ResourceManager::GetInstance()->RequestTexture("Bullet_", colors[playerId]));
		m_tanks.emplace_back(newTank);
	}
}
void Game::CreateMap() {
	m_Map = {};
	m_Map.Init(ResourceManager::GetInstance()->RequestTexture("Wall", "Green"), ResourceManager::GetInstance()->RequestTexture("Wall", "Grey"), 1);

}
void Game::CreateCollisionManager(int x, int y, float tankRadius, float bulletRadius) {
	m_ColManager = {};
	m_ColManager.Init(x, y, tankRadius, bulletRadius);

}
void Game::CreateInputContext() {
	InputManager::GetInstance()->AddAction(K_UP, sf::Keyboard::Key::W);
	InputManager::GetInstance()->AddAction(K_DOWN, sf::Keyboard::Key::S);
	InputManager::GetInstance()->AddAction(K_LEFT, sf::Keyboard::Key::A);
	InputManager::GetInstance()->AddAction(K_RIGHT, sf::Keyboard::Key::D);

	InputManager::GetInstance()->AddMouseAction(M_LEFT, sf::Mouse::Button::Left);
	InputManager::GetInstance()->AddMouseAction(M_RIGHT, sf::Mouse::Button::Right);

}

void Game::SetState(int state) {
	m_GameState = state;
}
int Game::GetState() {
	return m_GameState;
}

void Game::SyncReadyPlayers() {
	for (int i = 0; i < PLAYER_COUNT; i++)
	{
		int rdy = m_Client.GetReadyPlayers(i);
		if (rdy == 1)
		{
			int connected = 1;
			m_Users[i].SetConnected(connected);
			m_Users[i].SetAlive(connected);
		}
	}
}
void Game::IncomingPlayerData() {

}