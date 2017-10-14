#pragma once
#include <iostream>
#include <math.h>
#include "Player.h"

class Robot : public Player {
public:
	Robot(sf::Texture* texture);
	void move();
	void fire(sf::Texture* textureBullet, float bulletSpeed);
private:
	int direction;
};