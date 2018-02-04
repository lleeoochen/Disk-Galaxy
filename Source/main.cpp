#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Game.h"

//Functions
void initialize();
void finish();

//Main
int main() {

	//Intialize pointers
	initialize(); 

	//Start game
	Game game; game.startGame();

	//Delete pointers
	finish(); 

	return 0;
}

//Initialize global pointers
void initialize() {
	WINDOW = new sf::RenderWindow(sf::VideoMode(960, 540), "Disk Galaxy", sf::Style::Titlebar | sf::Style::Default);
	CLOCK = new sf::Clock();
	TEXTURE_GALAXY = new sf::Texture (Utility::getTexture("galaxy.png"));
	TEXTURE_BUTTON = new sf::Texture (Utility::getTexture("StartButton.png"));
	TEXTURE_UFO_ENEMY = new sf::Texture (Utility::getTexture("ufo.png"));
	TEXTURE_UFO = new sf::Texture (Utility::getTexture("ufo_4.png"));
	TEXTURE_BULLET = new sf::Texture (Utility::getTexture("bullet.png"));
	TEXTURE_EXPLOSION = new sf::Texture (Utility::getTexture("explosion.png"));
	FONT = Utility::getFont("summit.ttf");
}

//Delete all global pointers
void finish() {
	delete WINDOW;
	delete CLOCK;
	delete TEXTURE_GALAXY;
	delete TEXTURE_BUTTON;
	delete TEXTURE_UFO;
	delete TEXTURE_BULLET;
}