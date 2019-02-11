#include "game.h"

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>


int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	std::vector<Message> messageList;


	Game game;
	//std::vector<User> users(4);
	int currentState = MENU;

	//Client client;

	sf::Clock clock;
	float deltaTime;
	bool isRunning = true;

	// This is going to happen once, after connection with server but before game is starting
	game.CreateUsers();
	 while (isRunning)
	 {
		 deltaTime = clock.restart().asSeconds();

		 //client.Run(currentState, deltaTime);
		 //currentState = client.GetState();
		 game.SetState(currentState);
		 isRunning = game.Run(deltaTime);
		 currentState = game.GetState();
	 }

	 game.~Game();
	 //client.~Client();

	 _CrtDumpMemoryLeaks();
	return 0;
}