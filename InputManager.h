#pragma once
#include "SFML/Window/Keyboard.hpp"
#include "SFML//Window/Mouse.hpp"
#include "SFML/Graphics.hpp"

enum InputKeyboardName
{
	K_UP,
	K_DOWN,
	K_LEFT,
	K_RIGHT,
	K_INPUT_COUNT,
};
enum InputMouseName {
	M_LEFT,
	M_RIGHT,
};


class InputManager
{
public:
	static InputManager* GetInstance() {
		static InputManager instance;
		return &instance;
	}

	void CleanUp();
	~InputManager();

	void AddAction(InputKeyboardName id, sf::Keyboard::Key key);
	void AddMouseAction(InputMouseName id, sf::Mouse::Button button);

	bool IsKeyActionTriggered(InputKeyboardName id);
	bool isMouseActionTriggered(InputMouseName id);

	sf::Vector2i GetMousePosition(sf::RenderWindow *window);

	sf::Vector2i UpdateMousePos(sf::RenderWindow &window);

	std::map<int, sf::Keyboard::Key> GetKeyInput() {
		return m_Actions;
	}
	std::map<int, sf::Mouse::Button> GetMouseInput() {
		return m_MActions;
	}

private:
	InputManager();

	std::map<int, sf::Keyboard::Key> m_Actions;
	std::map<int, sf::Mouse::Button> m_MActions;

	sf::Vector2i MousePosition;

};