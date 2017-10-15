#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Global.h"
#include "Sprite.h"
#include "Player.h"
#include "User.h"
#include "Robot.h"
#include "Bullet.h"

//Variables
const float BULLET_SPEED = 1;
sf::Vector2i WIN_SIZE;
bool toGame = false;

void initialize();
void startLogin();
void startGame();
void deletePointers();

sf::Texture getTexture(std::string filename);
sf::Font getFont(std::string filename);

//Main
int main() {
	initialize();
	startLogin();
	if(toGame) startGame();
	deletePointers();
	return 0;
}

//Initialize global pointers
void initialize() {
	WINDOW = new sf::RenderWindow(sf::VideoMode(960, 540), "Disk Galaxy", sf::Style::Titlebar | sf::Style::Default);
	CLOCK = new sf::Clock();
	TEXTURE_GALAXY = new sf::Texture (getTexture("galaxy.png"));
	TEXTURE_BUTTON = new sf::Texture(getTexture("StartButton.png"));
	TEXTURE_UFO = new sf::Texture(getTexture("ufo.png"));
	TEXTURE_BULLET = new sf::Texture(getTexture("bullet.png"));
	FONT = getFont("summit.ttf");
}

//Start login
void startLogin() {

	sf::Text title;
	title.setString("Welcome to Disk Galaxy!");
	title.setFont(FONT);
	title.setPosition(WINDOW->getSize().x / 2 - title.getGlobalBounds().width / 2, WINDOW->getSize().y * 1 / 4 - title.getGlobalBounds().height / 2);
	title.setCharacterSize(30);
	title.setFillColor(sf::Color::White);

	Sprite background(TEXTURE_GALAXY);
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
				int dx = mouse.x - button.getPosition().x;
				int dy = mouse.y - button.getPosition().y;
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

	//Setup window
	Sprite background(TEXTURE_GALAXY);

	//Setup player
	User player(TEXTURE_UFO);
	player.setPosition(WINDOW->getSize().x / 2, WINDOW->getSize().y - player.height / 2);

	//Setup enemy1
	Robot robot1(TEXTURE_UFO);
	robot1.setPosition(WINDOW->getSize().x / 2, WINDOW->getSize().y / 2);

	//Setup enemy2
	Robot robot2(TEXTURE_UFO);
	robot2.setPosition(WINDOW->getSize().x / 4, WINDOW->getSize().y / 4);

	//Add enemies
	player.enemies.push_back(&robot1);
	player.enemies.push_back(&robot2);
	robot1.enemies.push_back(&player);
	robot1.enemies.push_back(&robot2);
	robot2.enemies.push_back(&player);
	robot2.enemies.push_back(&robot1);

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

		//Control player movement
		if (player.exists()) {
			player.move();
			player.aim(sf::Mouse::getPosition(*WINDOW));
			player.fire(TEXTURE_BULLET, BULLET_SPEED);
			player.draw();
		}

		//Control robot1 movement
		if (robot1.exists()) {
			robot1.move();
			if (player.exists()) {
				robot1.aim((sf::Vector2i) player.getPosition());
				robot1.fire(TEXTURE_BULLET, BULLET_SPEED);
			}
			robot1.draw();
		}

		//Control robot2 movement
		if (robot2.exists()) {
			robot2.move();
			if (player.exists()) {
				robot2.aim((sf::Vector2i) player.getPosition());
				robot2.fire(TEXTURE_BULLET, BULLET_SPEED);
			}
			robot2.draw();
		}

		//Draw objects
		WINDOW->display();
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
sf::Texture getTexture(std::string filename) {
	sf::Texture texture;
	if (!texture.loadFromFile(filename))
		std::cout << filename << " not found." << std::endl;
	return texture;
}

//Get font from file
sf::Font getFont(std::string filename) {
	sf::Font font;
	if (!font.loadFromFile(filename))
		std::cout << filename << " not found." << std::endl;
	return font;
}