#pragma once
#include "Global.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

class Sprite : public sf::Sprite {
public:
	Sprite(sf::Texture* texture);
	void aim(sf::Vector2i position);
	void draw();
	float getDistance(Sprite other);

	float width;
	float height;
	int window_width;
	int window_height;
};

static const float PI = 3.1415926f;
