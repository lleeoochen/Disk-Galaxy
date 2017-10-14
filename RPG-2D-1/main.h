#pragma once
#include <SFML/Graphics.hpp>


class Main {
public:
	Main(int i) {};
	sf::RenderWindow* window;
	bool startLogin();
	void startGame();
};
