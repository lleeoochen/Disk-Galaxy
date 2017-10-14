#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Sprite.h"
#include <math.h>

class Bullet : public Sprite {
public:
	Bullet(sf::Texture* texture);
	static sf::Vector2f Bullet::calculateAngle(Bullet& bullet);
	sf::Clock* clock;
};


static bool AVAILABLE = true;