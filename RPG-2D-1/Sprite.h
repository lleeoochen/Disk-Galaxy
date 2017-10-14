#pragma once
#include "Global.h"
#include <SFML/Graphics.hpp>

class Sprite : public sf::Sprite {
public:
	Sprite(sf::Texture* texture);
	void aim(sf::Vector2i position);
	void draw();

	int width;
	int height;
	float window_width;
	float window_height;
};

static const double PI = 3.1415926;