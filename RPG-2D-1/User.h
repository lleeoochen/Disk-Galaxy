#pragma once
#include "Player.h"

class User : public Player {
public:
	User(sf::Texture* texture);
	void move();
	void fire(sf::Texture* textureBullet, float bulletSpeed);
};