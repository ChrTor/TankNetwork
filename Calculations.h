#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

const float PI = 3.14159265359;
const float Rad = 180.0000;

static float AngleTank(sf::Vector2f &direction) {
	float M = sqrtf((direction.x * direction.x) + (direction.y * direction.y));
	sf::Vector2f norm = direction / M;

	return atan2f(norm.x, -norm.y) * Rad / PI;
}
static float AngleBullet(sf::Vector2f &direction) {

	float M = sqrtf((direction.x * direction.x) + (direction.y * direction.y));
	sf::Vector2f norm = direction / M;

	return atan2f(norm.x, norm.y) * Rad / PI;

}
static float AngleBarrel(sf::Vector2f &origin, sf::Vector2i &end) {

	sf::Vector2f ending((float)end.x, (float)end.y);

	sf::Vector2f V(origin - ending);
	float M = sqrtf((V.x * V.x) + (V.y * V.y));
	sf::Vector2f norm = V / M;

	return -atan2f(norm.x, norm.y) * Rad / PI;
}
static sf::Vector2f DirectionF(sf::Vector2f &origin, sf::Vector2f &comp) {
	sf::Vector2f V(origin - comp);
	float M = sqrt((V.x * V.x) + (V.y * V.y));
	sf::Vector2f norm = V / M;
	return norm;
}
static sf::Vector2f Direction(sf::Vector2f &V) {
	float M = sqrt((V.x * V.x) + (V.y * V.y));
	sf::Vector2f norm = V / M;
	return norm;
}
static sf::Vector2f DirectionI(sf::Vector2f &origin, sf::Vector2i &mouse) {

	sf::Vector2f Mouse = sf::Vector2f((float)mouse.x, (float)mouse.y);
	sf::Vector2f V(origin - Mouse);
	float M = sqrt((V.x * V.x) + (V.y * V.y));
	sf::Vector2f norm = V / M;
	return norm;
}
static float Distance(sf::Vector2f first, sf::Vector2f second) {
	float dist = sqrtf(((second.x - first.x)*(second.x - first.x))
		+ ((second.y - first.y) * (second.y - first.y)));

	return dist;
}