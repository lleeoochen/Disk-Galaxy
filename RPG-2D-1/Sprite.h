#pragma once
#include <SFML/Graphics.hpp>

class Sprite : public sf::Sprite {
public:
	Sprite(sf::Texture* texture, sf::RenderWindow* window);
	void rotate();
	void draw();

	int width;
	int height;
	float window_width;
	float window_height;
	sf::RenderWindow* window;
};

static const double PI = 3.1415926;