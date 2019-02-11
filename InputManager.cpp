#include "InputManager.h"

InputManager::InputManager() {

}
InputManager::~InputManager() {

}
void InputManager::CleanUp() {

	for (auto item : m_MActions) {
		m_MActions.erase(item.second);
	}
	m_MActions.clear();
	for (auto item : m_Actions) {
		m_Actions.erase(item.second);
	}
	m_MActions.clear();
}

void InputManager::AddAction(InputKeyboardName id, sf::Keyboard::Key key) {
	m_Actions.insert_or_assign(id, key);
}
void InputManager::AddMouseAction(InputMouseName id, sf::Mouse::Button button) {
	m_MActions.insert_or_assign(id, button);
}


bool InputManager::IsKeyActionTriggered(InputKeyboardName id) {
	return sf::Keyboard::isKeyPressed(m_Actions.at(id));
}
bool InputManager::isMouseActionTriggered(InputMouseName id) {
	return sf::Mouse::isButtonPressed(m_MActions.at(id));
}

sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow *window)
{
	return sf::Vector2i(sf::Mouse::getPosition(*window));
}

sf::Vector2i InputManager::UpdateMousePos(sf::RenderWindow &window) {
	return sf::Mouse::getPosition(window);
}