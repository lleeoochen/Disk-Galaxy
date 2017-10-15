#pragma once
#include <SFML/Graphics.hpp>
#include "Global.h"

class Score {
public:
	Score();
	void draw();

	sf::RectangleShape background;
	sf::Text text;
	int score;
	const float WIDTH = 200.f;
	const float HEIGHT = 50.f;
};