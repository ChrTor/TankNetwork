#pragma once
#include <SFML/Graphics.hpp>


class Wall
{
public:
	Wall();
	~Wall();

	void Init(sf::Vector2f pos, int type, float angle);
	void Update(float &deltatime);
	void Draw(sf::RenderWindow *window);
	sf::Vector2f GetPosition();
	sf::Vector2f GetSize();
	void SetSprite(sf::Texture *texture);

	sf::RectangleShape GetColBox();
private:

	sf::Vector2f m_size;
	sf::Vector2f m_Position;
	sf::RectangleShape m_Box;

	sf::Sprite m_Sprite;
	sf::Texture *m_Texture;
	float m_Angle;

};

