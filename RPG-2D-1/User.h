#pragma once
#include "Player.h"

class User : public Player {
public:
	User(sf::Texture* texture, sf::RenderWindow* window, sf::Clock* clock);
	void move();
	void fire(sf::Texture* textureBullet, float bulletSpeed);
};