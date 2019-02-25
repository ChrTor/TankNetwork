#pragma once
#include "wall.h"

class Map
{
public:
	Map();
	~Map();

	void Init(sf::Texture* text, sf::Texture* tex2, int type);
	void Update(float &deltatime);
	void Draw(sf::RenderWindow *window);

	std::vector<Wall>& GetWalls();

private:
	void FillPositionBank(sf::Vector2f &position);
	void AddWall(Wall &wall);

	std::vector<sf::Vector2f> PositionBank;
	std::vector<Wall> vecWalls;


};

