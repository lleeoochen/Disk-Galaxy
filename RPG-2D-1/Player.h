#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Player : public sf::Sprite {
	public:
		Player(sf::Texture& texture);
		int getWidth();
		int getHeight();
};
