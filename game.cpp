#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Main.hpp"
#include "SFML/OpenGL.hpp"
#include <iostream>
#include <sstream>
#include <math.h>
#include <vector>
#include "game.h"

std::vector<sf::Texture> t_tanks = {};
std::vector<sf::Texture> t_barrels = {};
std::vector<sf::Texture> t_bullets = {};

static void 
LoadSprites() {
	// Red Textures
	sf::Texture t_tankRed = {};
	t_tankRed.loadFromFile("../PNG/Tanks/tankRed_outline.png");
	t_tanks.emplace_back(t_tankRed);

	sf::Texture t_BarrelRed = {};
	t_BarrelRed.loadFromFile("../PNG/Tanks/barrelRed_outline.png");
	t_barrels.emplace_back(t_BarrelRed);

	sf::Texture t_BulletRed = {};
	t_BulletRed.loadFromFile("../PNG/Bullets/bulletRed_outline.png");
	t_bullets.emplace_back(t_BulletRed);


	// Blue Textures
	sf::Texture t_tankBlue = {};
	t_tankBlue.loadFromFile("../PNG/Tanks/tankBlue_outline.png");
	t_tanks.emplace_back(t_tankBlue);

	sf::Texture t_BarrelBlue = {};
	t_BarrelBlue.loadFromFile("../PNG/Tanks/barrelBlue_outline.png");
	t_barrels.emplace_back(t_BarrelBlue);

	sf::Texture t_BulletBlue = {};
	t_BulletBlue.loadFromFile("../PNG/Bullets/bulletBlue_outline.png");
	t_bullets.emplace_back(t_BulletBlue);

	// Green Textures
	sf::Texture t_tankGreen = {};
	t_tankGreen.loadFromFile("../PNG/Tanks/tankGreen_outline.png");
	t_tanks.emplace_back(t_tankGreen);

	sf::Texture t_BarrelGreen = {};
	t_BarrelGreen.loadFromFile("../PNG/Tanks/barrelGreen_outline.png");
	t_barrels.emplace_back(t_BarrelGreen);

	sf::Texture t_BulletGreen = {};
	t_BulletGreen.loadFromFile("../PNG/Bullets/bulletGreen_outline.png");
	t_bullets.emplace_back(t_BulletGreen);

	// Beige Textures
	sf::Texture t_tankBeige = {};
	t_tankBeige.loadFromFile("../PNG/Tanks/tankBeige_outline.png");
	t_tanks.emplace_back(t_tankBeige);

	sf::Texture t_BarrelBeige = {};
	t_BarrelBeige.loadFromFile("../PNG/Tanks/barrelBeige_outline.png");
	t_barrels.emplace_back(t_BarrelBeige);

	sf::Texture t_BulletBeige = {};
	t_BulletBeige.loadFromFile("../PNG/Bullets/bulletBeige_outline.png");
	t_bullets.emplace_back(t_BulletBeige);
}
static void 
AddPlayer(std::vector<Player> &vecPlayers, uint8_t ID, 
	int &posx, int &posy, int &speed) {
	// Assign Id
	int newID = 0;
	for (auto &P : vecPlayers) {
		if (P.ID < 0)
		{
			newID++;
		}
	}
	// Create Players
	Player newPlayer = {};

	newPlayer.ID = newID;
	newPlayer.PosX = posx;
	newPlayer.PosY = posy;
	newPlayer.DirX = 0;
	newPlayer.DirY = 0;
	newPlayer.Speed = speed;
	newPlayer.deadTimer = 2.0f;
	newPlayer.state = DEAD;

	// Set Textures
	newPlayer.s_Barrel.setTexture(t_barrels[newPlayer.ID]);
	newPlayer.s_Tank.setTexture(t_tanks[newPlayer.ID]);

	// Set Sprites
	newPlayer.s_Tank.setOrigin(newPlayer.s_Tank.getPosition().x + (newPlayer.s_Tank.getLocalBounds().width / 2), 
		newPlayer.s_Tank.getPosition().y + (newPlayer.s_Tank.getLocalBounds().height / 2));
	newPlayer.s_Barrel.setOrigin(newPlayer.s_Barrel.getPosition().x + (newPlayer.s_Barrel.getLocalBounds().width / 2),
		newPlayer.s_Barrel.getPosition().y + ((newPlayer.s_Barrel.getLocalBounds().height / 4) * 3));

	// Give players Bullets
	newPlayer.vecBullets = {};
	for (int i = 0; i < 5; i++)
	{
		Bullet newBullet = {};
		newBullet.ID = i;
		newBullet.state = DEAD;
		newBullet.s_Bullet.setTexture(t_bullets[newPlayer.ID]);
		newBullet.PosX = newPlayer.PosX;
		newBullet.PosY = newPlayer.PosY;
		newBullet.DirX = 0;
		newBullet.DirY = 0;
		newBullet.s_Bullet.setOrigin(((float)newBullet.PosX + newBullet.s_Bullet.getLocalBounds().width / 2), 
			((float)newBullet.PosY - newBullet.s_Bullet.getLocalBounds().height / 4));

		// Place bullet in vector
		newPlayer.vecBullets.emplace_back(newBullet);
	}
	// Place Player in vector
	newPlayer.Keys = {};
	vecPlayers.emplace_back(newPlayer);
}
static void
AddWall(std::vector<Wall> &vecWalls, sf::Sprite &wall, int &id, int &posx, int &posy) {
	Wall newWall = {};
	newWall.ID = id;
	newWall.PosX = posx;
	newWall.PosY = posy;
	newWall.s_Wall = wall;
	newWall.state = DEAD;

	vecWalls.emplace_back(newWall);
}

static void
ResolveInput(Player &P) {

	for (int i = 0; i < 4; i++)
	{
		if (P.Keys.input[i] > 0)
		{
			printf("%u%u%u%u%u", P.Keys.input[0], P.Keys.input[1], P.Keys.input[2], P.Keys.input[3], P.Keys.input[4]);
		}
	}
	printf("\n");

	P.DirX = (P.Keys.input[1] - P.Keys.input[2]);
	P.DirY = (P.Keys.input[3] - P.Keys.input[4]);
}
static void
UpdateInput(key_struct &keys, client_input &input) {

	
}

static void 
UpdatePlayers(std::vector<Player> &vecPlayers, client_input &input) {
	for (auto &P : vecPlayers) {

		UpdateInput(P.Keys, input);
		ResolveInput(P);

		for (auto &B : P.vecBullets) {
			if (B.state == ALIVE)
			{
				B.PosX += B.DirX * B.Speed;
				B.PosY += B.DirY * B.Speed;
			}
		}

		if (P.state == DEAD)
		{
			P.deadTimer = P.deadTimer - 0.01f;
			if (P.deadTimer <= 0.0f)
			{
				P.deadTimer = 5.0f;
				P.state = ALIVE;
			}
		}
		else
		{
			P.PosX += P.DirX * P.Speed;
			P.PosY += P.DirY * P.Speed;
		}
	}
}

// Game Loop
void 
game_Init(game_ &game) {

	game.state_ = MENU;
	game.vecPlayers = {};
	game.vecWalls = {};
	LoadSprites();

	int startPosx = 100;
	int startPosy = 100;
	int speed = 100;
	uint8_t ID = 1;
	AddPlayer(game.vecPlayers, ID, startPosx, startPosy, speed);
	
	
}


void 
game_Update(game_ &game, client_input &input) {
	
	client_input inpt = input;
	for (int i = 0; i < 5; i++)
	{

	}

	UpdatePlayers(game.vecPlayers, input);

	game_collision(game);
}

void
game_Draw(sf::RenderWindow &window, game_ &game) {
	
	switch (game.state_)
	{
	case IN_GAME:

		for (auto &P : game.vecPlayers) {
			if (P.state == ALIVE)
			{
				P.s_Tank.setPosition(sf::Vector2f((float)P.PosX, (float)P.PosY));
				P.s_Barrel.setPosition(sf::Vector2f((float)P.PosX, (float)P.PosY));
				window.draw(P.s_Tank);
				window.draw(P.s_Barrel);
			}

			for (auto &B : P.vecBullets) {
				if (B.state == ALIVE)
				{
					window.draw(B.s_Bullet);
					window.draw(B.s_Bullet);
				}
			}
		}
		for (auto &W : game.vecWalls) {
			if (W.state == ALIVE)
			{
				window.draw(W.s_Wall);
			}
		}

		break;
	case MENU:


		break;
	case SCOREBOARD:


		break;
	default:
		break;
	}

}

// Collision stuffs
void 
game_collision(game_ &game) {
	
	// Player V Player Col
	for (auto &P1 : game.vecPlayers) {
		//for (auto &P2 : ents.vecPlayers) {
		//	if (P1.PosX + P1.s_Tank.get)
		//	{

		//	}
		//}
	}

	// Player V Wall Col
	for (auto &P : game.vecPlayers) {

	}
	
	// Player V Rocket Col
	for (auto &P : game.vecPlayers) {

	}

	// Rocket V Wall Col

}
