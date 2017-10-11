#pragma once
#include <iostream>
#include "Sprite.h"
#include "Health.h"

class Player : public Sprite {
public:
	Player(sf::Texture* texture, sf::RenderWindow* window);
	void move();
	void draw();
	void setPosition(float x, float y);
	const float SPEED = 0.5;
	Health health;
};