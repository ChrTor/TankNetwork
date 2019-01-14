#include <iostream>
#include <math.h>
#include <vector>
#include "game.h"
#include "client.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Main.hpp"

struct Server
{
	int height, width;
	int posX, posY;

	sf::RectangleShape rect;
	sf::Text nameText;
	sf::Text activeplayerText;
	sf::Text timeremainingText;

	Connected_Server_Info ServerInfo = {};
	
	std::string name = "name";
	std::string activePlayers = "players";
	std::string timeRemaining = "time";

	void SetPos(int x, int y) {
		posX = x;
		posY = y;
		rect.setPosition(posX, posY);

		nameText.setPosition(posX + 5, posY);
		activeplayerText.setPosition(posX + 150, posY);
		timeremainingText.setPosition(posX + 300, posY);
	}
	void SetSize(int x, int y) {
		width = x;
		height = y;
		rect.setSize(sf::Vector2f((float)width, (float)height));
		rect.setOutlineThickness(5.0f);
		rect.setOutlineColor(sf::Color::Red);

		rect.setFillColor(sf::Color::Green);
		
		nameText.setFillColor(sf::Color::White);
		nameText.setCharacterSize(20);
		activeplayerText.setFillColor(sf::Color::White);
		activeplayerText.setCharacterSize(nameText.getCharacterSize());
		timeremainingText.setFillColor(sf::Color::White);
		timeremainingText.setCharacterSize(nameText.getCharacterSize());
	}
	void SetServer() {
		//name = ServerInfo.serverName;
		//activePlayers = (char)ServerInfo.activePlayers;
		//timeRemaining = (char)ServerInfo.timeRemaining;

		nameText.setString(name);
		activeplayerText.setString(activePlayers);
		timeremainingText.setString(timeRemaining);
	}
	void Draw(sf::RenderWindow &window) {
		window.draw(rect);
		window.draw(nameText);
		window.draw(activeplayerText);
		window.draw(timeremainingText);
	}
};

int
main(int argc, char *argv[]) {
	sf::RenderWindow window(sf::VideoMode(1080, 720), "TankGame");
	window.setFramerateLimit(60);

	game_ newGame = {};
	game_Init(newGame);

	client_input clientInput = {};
	clientInput.myKeys[5] = {};
	clientInput.ID = 1;

	// TODO:
	// CreateTime
	// Loop time
	WinSockStart winsock;
	Server server = {};
	server.SetPos(10, 10);
	server.SetSize(window.getSize().x - 50, 50);
	server.ServerInfo = {};
	server.SetServer();
	float pingTimer = 0.0f;
	// Open Window and render
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (sf::Mouse::Left)
				{
					clientInput.myKeys[0] = 1;
				}
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (sf::Mouse::Left)
				{
					clientInput.myKeys[0] = 0;
				}
			}

			switch (event.type)
			{
			case sf::Event::KeyPressed: {
				switch (event.key.code)
				{
				case sf::Keyboard::W: {
					clientInput.myKeys[1] = 1;
					break;
				}
				case sf::Keyboard::S: {
					clientInput.myKeys[2] = 1;
					break;
				}
				case sf::Keyboard::A: {
					clientInput.myKeys[3] = 1;
					break;
				}
				case sf::Keyboard::D: {
					clientInput.myKeys[4] = 1;
					break;
				}
				default:
					break;
				}
			}

			case sf::Event::KeyReleased: {
				switch (event.key.code)
				{
				case sf::Keyboard::W: {
					clientInput.myKeys[1] = 0;
					break;
				}
				case sf::Keyboard::S: {
					clientInput.myKeys[2] = 0;
					break;
				}
				case sf::Keyboard::A: {
					clientInput.myKeys[3] = 0;
					break;
				}
				case sf::Keyboard::D: {
					clientInput.myKeys[4] = 0;
					break;
				}
				default:
					break;
				}
			}
			}
		}

		window.clear();

		switch (newGame.state_)
		{
		case IN_GAME:
			if (newGame.vecPlayers.size())
			{

			}
			game_Update(newGame, clientInput);
			game_Draw(window, newGame);
			break;
		case MENU:
			if (pingTimer <= 0.0f)
			{
				ping_server(server.ServerInfo);
				
				pingTimer = 3.0f;
			}
			else
			{
				pingTimer = pingTimer - 0.01f;
			}

			server.Draw(window);
			break;
		case SCOREBOARD:


			break;
		default:
			break;
		}


		window.display();
	}

	
	system("Pause");
	return 0;
}