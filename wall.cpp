#include "wall.h"
#include "ResourceManager.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
Wall::Wall() {


}

Wall::~Wall() {
	m_Texture = nullptr;

}

void Wall::Init(sf::Vector2f pos, int type, float angle) {
	m_Position = pos;
	m_Angle = angle;
	m_size = sf::Vector2f(44.0f, 62.0f);
}
void Wall::Update(float &deltatime) {

}

sf::Vector2f Wall::GetPosition() {
	return m_Position;
}
sf::Vector2f Wall::GetSize() {
	return m_size;
}

void Wall::Draw(sf::RenderWindow *window) {
	window->draw(m_Sprite);
}

void Wall::SetSprite(sf::Texture *texture) {
	m_Texture = texture;
	sf::Vector2f size(m_Texture->getSize());
	m_Sprite.setTexture(*m_Texture);


	m_Sprite.setOrigin(m_Sprite.getPosition() + (size * 0.5f));
	m_Sprite.setPosition(m_Position);
	m_Sprite.setRotation(m_Angle);

	m_Box.setSize(size);
	m_Box.setPosition(m_Position);
}

sf::RectangleShape Wall::GetColBox() {
	return m_Box;
}