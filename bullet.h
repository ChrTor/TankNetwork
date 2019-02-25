#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "InputManager.h"
#include "Calculations.h"
#include <vector>

#pragma once

class Bullet
{
public:
	Bullet();
	~Bullet();

	void Init(sf::Vector2f position, float offset, sf::Vector2f direction);
	void Kill(sf::Vector2f position);
	void Update(float &deltatime);
	void Draw(sf::RenderWindow* window);
	void SetTextures(sf::Texture *text);

	void SetAlive(bool alive);
	bool GetAlive();

	void SetPosition(sf::Vector2f pos);
	sf::Vector2f GetPosition();

	void SetID(int &id);
	int GetID();

	void SetParentID(int id);
	int GetParentID();
private:

private:
	int m_ID;
	int m_parentID;

	sf::Vector2f m_Position;
	sf::Sprite m_sprite;
	sf::Texture* m_texture;

	bool m_isAlive;

	float m_Speed;

	float m_angle;
	sf::Vector2f m_direction;

};
