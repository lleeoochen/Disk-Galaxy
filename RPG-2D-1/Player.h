#pragma once
#include <iostream>
#include "Sprite.h"

class Player : public Sprite {
public:
	Player(sf::Texture* texture, sf::RenderWindow* window);
	void move();
	const float SPEED = 0.5;
};