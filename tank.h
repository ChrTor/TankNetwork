#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#include "bullet.h"
#include "InputManager.h"
#pragma once


class Tank
{
public:
	Tank();

	~Tank();
	void Init(int ID, sf::Vector2f position);
	void Update(float &deltaTime, std::vector<int> &input, int &mousex, int &mousey);
	void Draw(sf::RenderWindow* window);


	void SetPosition(sf::Vector2f position);
	sf::Vector2f GetPosition();

	// Collision
	void ForcePosition(sf::Vector2f offset);
	int GetKills();
	void AddKill();
	void Kill();

	// Bullets
	std::vector<Bullet> &GetBulletList();
	Bullet GetBullet(int &bullet);

	void SetTexture(sf::Texture *tank, sf::Texture *barrel, sf::Texture *bullet);
	// 
	bool GetAlive();
	int GetId();

private:
	void Move(float &deltatime, std::vector<int> &input, sf::Vector2i &mousePos);
	bool RunDeathTimer(float &deltatime);

private:

	int m_ID;
	sf::Vector2f m_Position;
	sf::Vector2f MoveDirection;
	sf::Vector2f t_Direction;
	sf::Vector2f b_Direction;

	float Speed;
	bool IsAlive;
	float m_DeathTimer;

	sf::Sprite m_Tsprite;
	sf::Vector2i t_origin;
	float t_angle;

	sf::Sprite m_Bsprite;
	sf::Vector2i b_origin;
	float b_angle;

	float m_CoolDown;
	sf::Texture *m_tTank;
	sf::Texture *m_tBarrel;
	sf::Texture *m_tBullet;

	std::vector<Bullet> m_bullets;

	sf::Text m_KillText;
	sf::Font m_KillFont;
	std::string m_Kills;

};



