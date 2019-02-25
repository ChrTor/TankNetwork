#include "user.h"


User::User() {
}

User::~User() {

}

void User::Init(int &id){
	m_ID = id;
}
void User::Update(float &deltatime, std::vector<int> &input, sf::Vector2i &mousePos) {


	SetInput(input, mousePos);



	m_Tank.Update(deltatime, m_Input, m_MouseX, m_MouseY);

}

void User::SetInput(std::vector<int> &input, sf::Vector2i &mousepos) {
	// Keys
	m_Input.clear();
	m_Input.resize(input.size());
	for (int i = 0; i < input.size(); i++)
	{
		m_Input[i] = input[i];
	}

	// Mouse
	m_MouseX = mousepos.x;
	m_MouseY = mousepos.y;
}
std::vector<int> User::GetInput() {
	return m_Input;
}

std::vector<sf::Vector2i> User::GetBulletPos() {

}

std::vector<sf::Vector2i> User::GetBulletDir() {

}

void User::Reset() {
	m_MoveDirX = 0;
	m_MoveDirY = 0;
	m_PosX = 0;
	m_PosY = 0;
	m_MouseX = 0;
	m_MouseY = 0;

	for (auto BP : m_BulletPos) {
		BP.x = 0;
		BP.y = 0;
	}
	for (auto BD : m_BulletDir) {
		BD.x = 0;
		BD.y = 0;
	}
}

void User::SetID(int &id) {
	m_ID = id;
}
int User::GetID() {
	return m_ID;
}
void User::SetPLayer(bool &IsPlayer) {
	m_IsPlayer = IsPlayer;
}
bool User::GetIsPlayer() {
	return m_IsPlayer;
}

void User::SetConnected(int &con) {
	m_Connected = con;
}
int User::GetConnected() {
	return m_Connected;
}
void User::SetAlive(int &alive) {
	m_Alive = alive;
}
int User::GetAlive() {
	return m_Alive;
}

void User::SetPosX(int &x) {
	m_PosX = x;
}
int User::GetPosX() {
	return m_PosX;
}

void User::SetPosY(int &y) {
	m_PosY = y;
}
int User::GetPosY() {
	return m_PosY;
}

void User::SetDirX(int &dir) {
	m_MoveDirX = dir;
}
int User::GetMoveDirX() {
	return m_MoveDirX;
}

void User::SetDirY(int &y) {
	m_MoveDirY = y;
}
int User::GetMoveDirY() {
	return m_MoveDirY;
}

int User::GetMouseX() {
	return m_MouseX;
}
int User::GetMouseY() {
	return m_MouseY;
}
