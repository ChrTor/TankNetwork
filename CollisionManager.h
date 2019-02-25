#pragma once
#include <vector>
#include "tank.h"
#include "bullet.h"
#include "map.h"
#include "wall.h"
class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void Init(int widht, int height, float tankRadius, float bulletRadius);
	void Update(std::vector<Tank> &tanks, Map &map);


private:

	sf::CircleShape GetCircle(sf::Vector2f position, float radius);
	sf::RectangleShape GetBox(sf::Vector2f position, sf::Vector2f size);

	sf::Vector2f CircleVBox(sf::CircleShape &box, sf::RectangleShape &wallbox);
	sf::Vector2f CircleVCircle(sf::CircleShape &T1, sf::CircleShape &T2);
	sf::Vector2f CircleVMap(sf::CircleShape &box);
	bool IsBulletOutsideOfMap(Bullet &bullet);

	int m_MapHeight, m_MapWidth;
	float m_TankRadius, m_BulletRadius;

};