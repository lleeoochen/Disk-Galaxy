#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Sprite.h"
#include <math.h>

class Bullet : public Sprite {
public:
	Bullet();
	static sf::Vector2f Bullet::calculateAngle(Bullet& bullet);
	sf::Clock* clock;
};