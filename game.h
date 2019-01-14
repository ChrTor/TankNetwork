#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Main.hpp"
#include <vector>

enum Entity_Type {
	WALL,
	TANK,
	BULLET,
};

enum Entity_State
{
	ALIVE,
	DEAD,
};
enum Entity_Property
{
	DESTRUCTABLE,
	NON_DESTRUCTABLE,
};

enum game_state
{
	IN_GAME,
	MENU,
	SCOREBOARD,
};

struct client_input
{
	uint8_t ID;
	uint8_t myKeys[5];
};

struct key_struct
{
	uint8_t input[5];
	uint8_t rotation;
};

struct Bullet {
	uint8_t ID;
	int PosX, PosY;
	uint8_t DirX, DirY;
	int Width, Height;
	int Speed;

	Entity_Property prop;
	Entity_State state;
	Entity_Type type;

	sf::Sprite s_Bullet;
};
struct Player
{
	uint8_t ID;
	int PosX, PosY;
	uint8_t DirX, DirY;
	int Width, Height;
	int Speed;

	Entity_State state;
	Entity_Type type;

	float deadTimer;

	sf::Sprite s_Barrel;
	sf::Sprite s_Tank;
	std::vector<Bullet> vecBullets;

	key_struct Keys;
};
struct Wall {
	int PosX, PosY;
	uint8_t ID;

	Entity_State state;
	Entity_Type type;

	sf::Sprite s_Wall;
};


struct game_
{
	game_state state_;

	std::vector<Player> vecPlayers;
	std::vector<Wall> vecWalls;

	std::vector<sf::Sprite> s_vecTanks;
	std::vector<sf::Sprite> s_vecTurrets;
	std::vector<sf::Sprite> s_vecBullets;
	std::vector<sf::Sprite> s_vecWalls;
	std::vector<sf::Sprite> s_vecGround;
};

void game_Draw(sf::RenderWindow &window, game_ &game);
void game_Init(game_ &game);
void game_Update(game_ &game, client_input &input);

void game_collision(game_ &game);
