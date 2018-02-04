#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Sprite.h"
#include <math.h>

class Bullet : public Sprite {
public:
	Bullet();
	void setVelocity();
	static sf::Vector2f calculateAngle(Bullet& bullet);
	sf::Clock* clock;
	sf::Vector2f velocity;
	float bullet_speed;
};