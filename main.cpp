#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Global.h"
#include "Score.h"
#include "Sprite.h"
#include "Player.h"
#include "User.h"
#include "Robot.h"
#include "Bullet.h"

//Variables
sf::Vector2i WIN_SIZE;
bool toGame = true;

//Functions
void initialize();
void preGame();
void startGame();
void deletePointers();
template<class T> T getAsset(std::string filename);

//Main
int main() {

	initialize(); //Intialize pointers
	while (toGame) {
		preGame(); //Display startup screen
		if (toGame) 
			startGame(); //Display gaming screen
	}
	deletePointers(); //Delete pointers

	return 0;
}


//Initialize global pointers
void initialize() {
	WINDOW = new sf::RenderWindow(sf::VideoMode(960, 540), "Disk Galaxy", sf::Style::Titlebar | sf::Style::Default);
	CLOCK = new sf::Clock();
	TEXTURE_GALAXY = new sf::Texture (getAsset<sf::Texture>("galaxy.png"));
	TEXTURE_BUTTON = new sf::Texture(getAsset<sf::Texture>("StartButton.png"));
	TEXTURE_UFO_ENEMY = new sf::Texture(getAsset<sf::Texture>("ufo.png"));
	TEXTURE_UFO = new sf::Texture(getAsset<sf::Texture>("ufo_4.png"));
	TEXTURE_BULLET = new sf::Texture(getAsset<sf::Texture>("bullet.png"));
	TEXTURE_EXPLOSION = new sf::Texture(getAsset<sf::Texture>("explosion.png"));
	FONT = getAsset<sf::Font>("summit.ttf");
}


//Start login
void preGame() {

	//Setup title
	sf::Text title;
	title.setString("Welcome to Disk Galaxy!");
	title.setFont(FONT);
	title.setPosition(WINDOW->getSize().x / 2 - title.getGlobalBounds().width / 2, WINDOW->getSize().y * 1 / 4 - title.getGlobalBounds().height / 2);
	title.setCharacterSize(30);
	title.setFillColor(sf::Color::White);

	//Setup background
	Sprite background(TEXTURE_GALAXY);

	//Setup button
	Sprite button(TEXTURE_BUTTON);
	button.setPosition(WINDOW->getSize().x / 2 - button.width / 2, WINDOW->getSize().y * 3 / 4 - button.height / 2);

	//Game loop
	while (WINDOW->isOpen()) {

		//Event loop
		sf::Event event;
		while (WINDOW->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				WINDOW->close();
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i mouse = sf::Mouse::getPosition(*WINDOW);
				float dx = mouse.x - button.getPosition().x;
				float dy = mouse.y - button.getPosition().y;
				if (dx >= 0 && dy >= 0 && dx <= button.width && dy <= button.height) {
					toGame = true;
					return;
				}
			}
		}

		//Draw window
		WINDOW->clear();
		WINDOW->draw(background);
		WINDOW->draw(title);
		WINDOW->draw(button);
		WINDOW->display();
	}
	toGame = false;
}

//Start game
void startGame() {

	//Reset clock
	CLOCK->restart();

	//Setup background
	Sprite background(TEXTURE_GALAXY);

	//Setup players
	User user1(TEXTURE_UFO);
	Robot robot1(TEXTURE_UFO);
	Robot robot2(TEXTURE_UFO_ENEMY);
	Robot robot3(TEXTURE_UFO_ENEMY);

	//Setup score board
	Score scoreboard;
	user1.trackScore(&scoreboard);

	//Add enemies
	user1.id = 0; user1.team = 0;
	robot1.id = 1; robot1.team = 0;
	robot2.id = 2; robot2.team = 1;
	robot3.id = 3; robot3.team = 1;

	//Game loop
	while (WINDOW->isOpen()) {

		//Clear window
		WINDOW->clear();
		WINDOW->draw(background);

		//Event loop
		sf::Event event;
		while (WINDOW->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				WINDOW->close();
				return;
			}
		}

		//Players act
		user1.act();
		robot1.act();
		robot2.act();
		robot3.act();

		//Draw players
		WINDOW->display();

		if (!user1.exists() || user1.enemies.size() == 0)
			return; //Game over
	}
}

//Delete all global pointers
void deletePointers() {
	delete WINDOW;
	delete CLOCK;
	delete TEXTURE_GALAXY;
	delete TEXTURE_BUTTON;
	delete TEXTURE_UFO;
	delete TEXTURE_BULLET;
}

//Get texture from file
template<class T>
T getAsset(std::string filename) {
	T obj;
	if (!obj.loadFromFile("Assets/" + filename))
		std::cout << filename << " not found." << std::endl;
	return obj;
}