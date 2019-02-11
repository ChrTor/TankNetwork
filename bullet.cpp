#include "bullet.h"

sf::Texture texture;

Bullet::Bullet()
{
	m_isAlive = false;

}

Bullet::~Bullet()
{
	m_texture = nullptr;
	
}

void Bullet::Init(sf::Vector2f position, float offset, sf::Vector2f direction)
{
	m_Position = position - (abs(offset) * direction);
	m_direction = direction;
	m_Speed = 100.0f;
	m_isAlive = true;
}
void Bullet::Kill(sf::Vector2f position) {
	m_Position = position;
	m_sprite.setPosition(m_Position);
	m_isAlive = false;
}

void Bullet::Update(float &deltatime)
{
	m_angle = AngleBullet(m_direction);

	m_sprite.setRotation(-m_angle);

	m_Position -= m_direction * (m_Speed * deltatime);
}

void Bullet::Draw(sf::RenderWindow* window)
{
	if (m_isAlive)
	{
		m_sprite.setPosition(m_Position);
		window->draw(m_sprite);
	}
}

void Bullet::SetTextures(sf::Texture *text)
{
	m_texture = text;

	m_sprite.setTexture(*m_texture);
	sf::Vector2f t_Size(m_texture->getSize());

	m_sprite.setOrigin(m_sprite.getPosition() + (t_Size / 2.0f));
}

void Bullet::SetAlive(bool alive) {
	m_isAlive = alive;
}
bool Bullet::GetAlive() {
	return m_isAlive;
}

void Bullet::SetPosition(sf::Vector2f pos) {
	m_Position = pos;
}
sf::Vector2f Bullet::GetPosition() {
	return m_Position;
}

void Bullet::SetID(int &id) {
	m_ID = id;
}
int Bullet::GetID() {
	return m_ID;
}

void Bullet::SetParentID(int id) {
	m_parentID = id;
}
int Bullet::GetParentID() {
	return m_parentID;
}
