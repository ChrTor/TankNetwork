#include "tank.h"


Tank::Tank() {

	if (!m_KillFont.loadFromFile("arial.ttf"))
	{
		printf("Error Loading font");
	}
	m_Kills = "0";
}

Tank::~Tank() {

	m_tBarrel = nullptr;
	m_tTank = nullptr;
	m_tBullet = nullptr;

}


// Main Funtions
void Tank::Init(int id, sf::Vector2f position) {

	m_ID = id;
	Speed = 100.0f;
	m_Position = position;
	m_CoolDown = 1.5f;
	m_DeathTimer = 2.0f;
	IsAlive = true;
}
void Tank::Update(InputManager &input, sf::Vector2i &mousePos, float &deltaTime) {
	if (IsAlive)
	{
		// Sense Input
		int keyPressed[4] = {};
		HandleKeyboard(input, keyPressed);
		int buttonPressed[2] = {};
		HandleMouse(input, buttonPressed);

		// Handle KeyStrokes
		MoveDirection.x = (float)(keyPressed[K_RIGHT] - keyPressed[K_LEFT]);
		MoveDirection.y = (float)(keyPressed[K_DOWN] - keyPressed[K_UP]);

		// Handle Mouse Clicks
		sf::Vector2i m_Pos = mousePos;
		if (buttonPressed[M_LEFT])
		{
			if (m_CoolDown <= 0.0f)
			{
				for (auto &B : m_bullets) {
					if (!B.GetAlive())
					{
						B.Init(m_Position, 45.0f, b_Direction);
						m_CoolDown = 1.5f;
						break;
					}
					continue;
				}
			}
		}
		m_CoolDown -= 1.5f * deltaTime;

		if (buttonPressed[M_RIGHT])
		{

		}

		// Execute Update
		Move(deltaTime, mousePos);
	}
	else
	{
		// Resolve DeathTimer
		if (RunDeathTimer(deltaTime))
		{
			Init(m_ID, sf::Vector2f(100.f, 100.f));
			m_DeathTimer = 2.0f;
		}
	}
	for (auto &B : m_bullets) {
		if (B.GetAlive())
		{
			B.Update(deltaTime);
		}
	}
}
void Tank::Update(User &user, float &deltaTime) {
	if (IsAlive)
	{
		std::vector<int> keyPressed = user.GetInput();

		MoveDirection.x = keyPressed[1] - keyPressed[0];
		MoveDirection.y = keyPressed[3] - keyPressed[2];

		// Handle Mouse Clicks
		sf::Vector2i m_Pos = sf::Vector2i(user.GetMouseX(), user.GetMouseY());
		if (keyPressed[4] == 1)
		{
			if (m_CoolDown <= 0.0f)
			{
				for (auto &B : m_bullets) {
					if (!B.GetAlive())
					{
						B.Init(m_Position, 45.0f, b_Direction);
						m_CoolDown = 1.5f;
						break;
					}
					continue;
				}
			}
		}
		m_CoolDown -= 1.5f * deltaTime;

		// Execute Update
		Move(deltaTime, m_Pos);
	}
	else
	{
		// Resolve DeathTimer
		if (RunDeathTimer(deltaTime))
		{
			Init(m_ID, sf::Vector2f(100.f, 100.f));
			m_DeathTimer = 2.0f;
		}
	}

	for (auto &B : m_bullets) {
		if (B.GetAlive())
		{
			B.Update(deltaTime);
		}
	}
}


void Tank::Draw(sf::RenderWindow* window) {

	if (IsAlive)
	{
		m_Tsprite.setPosition(m_Position);
		m_Bsprite.setPosition(m_Position);

		window->draw(m_Tsprite);
		window->draw(m_Bsprite);
		m_KillText.setFont(m_KillFont);
		m_KillText.setPosition(m_Position);
		m_KillText.setString(m_Kills);
		window->draw(m_KillText);
	}

	for (auto &B : m_bullets) {
		B.Draw(window);
	}
}


// Position
void Tank::Move(float &deltatime, sf::Vector2i &mousePos) {
	if (MoveDirection != sf::Vector2f(0.0f, 0.0f))
	{
		// New Position
		m_Position += MoveDirection * (Speed * deltatime);
		// New Rotation
		t_angle = AngleTank(MoveDirection);
	}

	b_Direction = DirectionI(m_Position, mousePos);
	b_angle = AngleBarrel(m_Position, mousePos);

	// Rotation
		//Direction
	m_Tsprite.setRotation(t_angle);
	m_Bsprite.setRotation(b_angle);
}
void Tank::SetPosition(sf::Vector2f pos) {
	m_Position = pos;
}
sf::Vector2f Tank::GetPosition() {
	return m_Position;
}

// Bullets
std::vector<Bullet> &Tank::GetBulletList() {
	return m_bullets;
}
Bullet Tank::GetBullet(int &i) {
	return m_bullets[i];
}

// Collision
void Tank::ForcePosition(sf::Vector2f offset) {
	m_Position -= offset;
}

// Kill Tanks
int Tank::GetKills() {
	return m_Kills[0] - '0';
}
void Tank::AddKill() {
	int kills = m_Kills[0] - '0';
	m_Kills = std::to_string(kills + 1);
}
void Tank::Kill() {
	IsAlive = false;
}

// States
bool Tank::RunDeathTimer(float &deltatime) {
	m_DeathTimer -= 1.0f * deltatime;
	return m_DeathTimer < 0.0f ? true : false;
}
bool Tank::GetAlive() {
	return IsAlive;
}

// Texture
void Tank::SetTexture(sf::Texture *tank, sf::Texture *barrel, sf::Texture *bullet) {

	m_tTank = tank;
	m_tBarrel = barrel;
	m_tBullet = bullet;
	sf::Vector2f t_Size(m_tTank->getSize());
	sf::Vector2f b_Size(m_tBarrel->getSize());

	m_Tsprite.setTexture(*m_tTank);
	m_Tsprite.setOrigin(m_Tsprite.getPosition() + (t_Size / 2.0f));

	m_Bsprite.setTexture(*m_tBarrel);
	m_Bsprite.setOrigin(m_Bsprite.getPosition().x + (b_Size.x / 2.0f),
		m_Bsprite.getPosition().y + ((b_Size.y / 4.0f) * 3.0f));

	m_Tsprite.setPosition(m_Position);
	m_Bsprite.setPosition(m_Position);


	for (int i = 0; i < 5; i++)
	{
		Bullet newBullet;
		newBullet.SetID(i);
		newBullet.SetParentID(m_ID);
		newBullet.SetTextures(m_tBullet);
		m_bullets.emplace_back(newBullet);
	}
}

// Handle Input  TODO:: Will move this to Player Class
int* Tank::HandleKeyboard(InputManager &input, int keyPressed[]) {

	// Controls
	if (input.IsKeyActionTriggered(K_UP))
		keyPressed[K_UP] = 1;
	else keyPressed[K_UP] = 0;

	if (input.IsKeyActionTriggered(K_DOWN))
		keyPressed[K_DOWN] = 1;
	else keyPressed[K_DOWN] = 0;

	if (input.IsKeyActionTriggered(K_LEFT))
		keyPressed[K_LEFT] = 1;
	else keyPressed[K_LEFT] = 0;

	if (input.IsKeyActionTriggered(K_RIGHT))
		keyPressed[K_RIGHT] = 1;
	else keyPressed[K_RIGHT] = 0;

	return keyPressed;
}
int* Tank::HandleMouse(InputManager &input, int keyPressed[]) {

	if (input.isMouseActionTriggered(M_LEFT))
		keyPressed[M_LEFT] = 1;
	else keyPressed[M_LEFT] = 0;
	if (input.isMouseActionTriggered(M_RIGHT))
		keyPressed[M_RIGHT] = 1;
	else keyPressed[M_RIGHT] = 0;

	return keyPressed;
}

int Tank::GetId() {
	return m_ID;
}