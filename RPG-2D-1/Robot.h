#pragma once
#include <iostream>
#include <math.h>
#include "Player.h"

class Robot : public Player {
public:
	Robot(sf::Texture* texture, sf::RenderWindow* window, sf::Clock* clock);
	void move();
};