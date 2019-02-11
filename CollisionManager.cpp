#include "CollisionManager.h"


CollisionManager::CollisionManager() {

}
CollisionManager::~CollisionManager() {


}

void CollisionManager::Init(int widht, int height, float tankRadius, float bulletRadius) {
	m_MapWidth = widht;
	m_MapHeight = height;
	m_TankRadius = tankRadius;
	m_BulletRadius = bulletRadius;
}

void CollisionManager::Update(std::vector<Tank> &tanks, Map &map) {
	// Iterate Through Tanks (T1)
	for (auto &T1 : tanks) {
		if (T1.GetAlive())
		{
			sf::CircleShape box1 = GetCircle(T1.GetPosition(), 35.0f);

			// Calculate Collision with Tanks (T2)
			for (auto &T2 : tanks) {
				if (T2.GetAlive())
				{
					if (T1.GetId() != T2.GetId())
					{
						sf::CircleShape box2 = GetCircle(T2.GetPosition(), 35.0f);

						sf::Vector2f offset = CircleVCircle(box1, box2);
						// Forcibly move the colliding tanks
						T1.ForcePosition(offset);
						T2.ForcePosition(-offset);
					}
				}
			}

			// Collision With Bullets
				// Iterate bullets
			for (auto &B : T1.GetBulletList()) {
				if (B.GetAlive())
				{		// Iterate Tanks
					for (auto &T2 : tanks) {
						if (B.GetParentID() != T2.GetId())
						{
							// Current Bullet (B)
							sf::CircleShape Bbox = GetCircle(B.GetPosition(), 10.0f);
							// Current Tank (T2)
							sf::CircleShape Tbox = GetCircle(T2.GetPosition(), 35.0f);

							// Check Collision
							sf::Vector2f collision = CircleVCircle(Bbox, Tbox);
							if (collision != sf::Vector2f(0.0f, 0.0f))
							{
								// Resolve Killshot
								T1.AddKill();
								T2.Kill();
								B.Kill(T1.GetPosition());
							}
						}
					}
				}
				// Binding Bullet to screen width & height
				if (IsBulletOutsideOfMap(B))
					B.Kill(T1.GetPosition());
			}

			// Collision With Walls
			for (auto &W : map.GetWalls()) {
				sf::RectangleShape wallbox = GetBox(W.GetPosition(), W.GetSize());

				// Bullet Collision with walls
				for (auto &B : T1.GetBulletList()) {
					sf::CircleShape Bbox = GetCircle(B.GetPosition(), 10.0f);
					if (CircleVBox(Bbox, wallbox) != sf::Vector2f(0.0f, 0.0f))
					{
						B.Kill(T1.GetPosition());
					}
				}

				sf::Vector2f Offset(CircleVBox(box1, wallbox));
				if (Offset != sf::Vector2f(0.0f, 0.0f))
				{
					T1.ForcePosition(Offset);
				}
			}

			// Tank (T1) Collision With Game World
			sf::Vector2f Offset(CircleVMap(box1));
			if (Offset != sf::Vector2f(0.0f, 0.0f))
			{
				T1.ForcePosition(Offset);
			}
		}
	}
}

sf::Vector2f CollisionManager::CircleVBox(sf::CircleShape &box, sf::RectangleShape &wallbox) {

	std::vector<sf::Vector2f> vecVector = {};
	float radius = box.getRadius();

	sf::Vector2f origin(wallbox.getPosition().x - (wallbox.getSize().x / 2), wallbox.getPosition().y - (wallbox.getSize().y / 2));
	sf::Vector2f dotAmount(wallbox.getGlobalBounds().width, wallbox.getGlobalBounds().height);

	int countX = dotAmount.x + 1;
	int countY = dotAmount.y + 1;

	for (int i = 0; i <= countX; i++)
	{
		for (int j = 0; j <= countY; j++)
		{
			if (i == 0)
			{
				sf::Vector2f newDot(origin.x + i, origin.y + j);
				vecVector.emplace_back(newDot);
			}
			else if (i == countX)
			{
				sf::Vector2f newDot(origin.x + i, origin.y + j);
				vecVector.emplace_back(newDot);
			}
			else if (i > 0 && i < countX)
			{
				if (j == 0 || j == countY)
				{
					sf::Vector2f newDot(origin.x + i, origin.y + j);
					vecVector.emplace_back(newDot);
				}
			}
		}
	}
	// Objects distance
	sf::Vector2f offset(0.0f, 0.0f);

	for (auto &P : vecVector) {
		float dist = Distance(box.getPosition(), P);
		if (dist < radius)
		{
			float overLap = 1.0f * (dist - radius);

			offset.x = overLap * (box.getPosition().x - wallbox.getPosition().x) / dist;
			offset.y = overLap * (box.getPosition().y - wallbox.getPosition().y) / dist;
			break;
		}
	}
	return offset;
}
sf::Vector2f CollisionManager::CircleVCircle(sf::CircleShape &box1, sf::CircleShape &box2) {

	sf::Vector2f offset(0.0f, 0.0f);

	// Check Distance between them
	float dist = Distance(box1.getPosition(), box2.getPosition());
	float rad2 = box1.getRadius() + box2.getRadius();

	// Collision 
	if (dist < rad2)
	{
		// Get overlap
		float overLap = 0.5f * (dist - rad2);
		offset.x = overLap * (box1.getPosition().x - box2.getPosition().x) / dist;
		offset.y = overLap * (box1.getPosition().y - box2.getPosition().y) / dist;

	}
	return offset;
}
sf::Vector2f CollisionManager::CircleVMap(sf::CircleShape &box) {
	float rad = box.getRadius();
	float posX = box.getPosition().x;
	float posY = box.getPosition().y;

	if (posX + rad > (float)m_MapWidth)
	{
		// Right Side Collision

		float distance = Distance(box.getPosition(), sf::Vector2f(m_MapWidth, box.getPosition().y));
		float overlap = distance - rad;
		float offsetX = overlap * (box.getPosition().x - (float)m_MapWidth) / distance;

		return sf::Vector2f(offsetX, 0.0f);
	}
	else if (posX - rad < 0.0f)
	{
		// Left Side Collision
		float distance = Distance(box.getPosition(), sf::Vector2f(0.0f, box.getPosition().y));
		float overlap = distance - rad;
		float offsetX = overlap * (box.getPosition().x - 0.0f) / distance;
		return sf::Vector2f(offsetX, 0.0f);
	}
	else if (posY + rad > (float)m_MapHeight)
	{
		// Bottom Side Collision
		float distance = Distance(box.getPosition(), sf::Vector2f(box.getPosition().x, m_MapHeight));
		float overlap = distance + rad;
		float offsetY = overlap * (box.getPosition().y - (float)m_MapHeight) / distance;
		return sf::Vector2f(0.0f, offsetY);
	}
	else if (posY - rad < 0.0f)
	{
		// Top Side Collision
		float distance = Distance(box.getPosition(), sf::Vector2f(box.getPosition().x, 0.0f));
		float overlap = distance - rad;
		float offsetY = overlap * (box.getPosition().y - 0.0f) / distance;
		return sf::Vector2f(0.0f, offsetY);
	}
	else
	{
		return sf::Vector2f(0.0f, 0.0f);
	}
}
bool CollisionManager::IsBulletOutsideOfMap(Bullet &bullet) {

	if (bullet.GetPosition().x > (float)m_MapWidth || bullet.GetPosition().x < 0.0f)
	{
		return true;
	}
	else if (bullet.GetPosition().y > (float)m_MapHeight || bullet.GetPosition().y < 0.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

sf::CircleShape CollisionManager::GetCircle(sf::Vector2f position, float radius) {
	sf::CircleShape newShape;
	newShape.setPosition(position);
	newShape.setRadius(radius);

	return newShape;
}
sf::RectangleShape CollisionManager::GetBox(sf::Vector2f position, sf::Vector2f size) {
	sf::RectangleShape newRect;
	newRect.setPosition(position);
	newRect.setOrigin(newRect.getPosition());
	newRect.setSize(size);
	return newRect;
}