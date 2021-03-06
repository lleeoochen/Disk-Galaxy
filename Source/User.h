#pragma once
#include "Player.h"

class User : public Player {
public:
	User(sf::Texture* texture);
	void act();
	void move();
	void fire();
	void updateEnemies();
};