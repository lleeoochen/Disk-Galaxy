#pragma once
#include <iostream>
#include <math.h>
#include "Player.h"

class Robot : public Player {
public:
	Robot(sf::Texture* texture);
	void act();
	void move();
	void fire();
	void updateEnemies();
private:
	int direction;
};