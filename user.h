#include <vector>
#include <map>
#include "SFML/Graphics.hpp"
#include "InputManager.h"
#include "tank.h"
#pragma once

class User
{
public:
	User();
	~User();
	void Init(int &id);
	void Update(float &deltaTime, std::vector<int> &input, sf::Vector2i &mousePos);
	void Reset();


	void SetID(int &id);
	int GetID();

	void SetPLayer(bool &IsPlayer);
	bool GetIsPlayer();

	void SetConnected(int &con);
	int GetConnected();

	void SetAlive(int &alive);
	int GetAlive();

	void SetPosX(int &x);
	int GetPosX();

	void SetPosY(int &y);
	int GetPosY();
	
	void SetDirX(int &x);
	int GetMoveDirX();
	
	void SetDirY(int &y);
	int GetMoveDirY();

	std::vector<int> GetInput();
	int GetMouseX();
	int GetMouseY();

	std::vector<sf::Vector2i> GetBulletPos();
	std::vector<sf::Vector2i> GetBulletDir();
private:

	void SetInput(std::vector<int> &input, sf::Vector2i &mousePos);


private:

	int m_ID;
	int m_Connected;
	int m_Alive;

	int m_MoveDirX;
	int m_MoveDirY;
	int m_PosX;
	int m_PosY;

	int m_MouseX;
	int m_MouseY;

	std::vector<int> m_Input;

	Tank m_Tank;
	bool m_IsPlayer;
	
	std::vector<sf::Vector2i> m_BulletPos;
	std::vector<sf::Vector2i> m_BulletDir;
};