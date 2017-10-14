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
bool startLogin();
void startGame();
sf::Texture getTexture(std::string filename);
sf::Font getFont(std::string filename);

int main() {
	if (startLogin())
		startGame();
	return 0;
}

bool startLogin() {
	WINDOW = new sf::RenderWindow(sf::VideoMode(960, 540), "Disk Galaxy", sf::Style::Titlebar | sf::Style::Default);

	sf::Texture textureGalaxy = getTexture("galaxy.png");
	sf::Texture texture = getTexture("StartButton.png");
	sf::Font font = getFont("summit.ttf");

	sf::Text title;
	title.setString("Welcome to Disk Galaxy!");
	title.setFont(font);
	title.setPosition(WINDOW->getSize().x / 2 - title.getGlobalBounds().width / 2, WINDOW->getSize().y * 1 / 4 - title.getGlobalBounds().height / 2);
	title.setCharacterSize(30);
	title.setFillColor(sf::Color::White);

	Sprite button(&texture);
	button.setPosition(WINDOW->getSize().x / 2 - button.width / 2, WINDOW->getSize().y * 3 / 4 - button.height / 2);
	Sprite background(&textureGalaxy);

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
					WINDOW->close();
					delete WINDOW;
					return true;
				}
			}
		}

		//Draw window
		WINDOW->clear();
		background.draw();
		button.draw();
		WINDOW->draw(title);
		WINDOW->display();
	}
	delete WINDOW;
	return false;
}

void startGame() {
	//Setup textures
	sf::Texture textureUFO = getTexture("ufo.png");
	sf::Texture textureGalaxy = getTexture("galaxy.png");
	sf::Texture textureBullet = getTexture("bullet.png");

	//Setup window
	WINDOW = new sf::RenderWindow(sf::VideoMode(960, 540), "Disk Galaxy", sf::Style::Titlebar | sf::Style::Default);
	CLOCK = new sf::Clock();
	Sprite background(&textureGalaxy);

	//Setup player
	User player(&textureUFO);
	player.setPosition(WINDOW->getSize().x / 2, WINDOW->getSize().y - player.height / 2);

	//Setup enemy
	Robot robot1(&textureUFO);
	robot1.setPosition(WINDOW->getSize().x / 2, WINDOW->getSize().y / 2);

	Robot robot2(&textureUFO);
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
				delete WINDOW;
				delete CLOCK;
				return;
			}
		}

		//Control player movement
		if (player.exists()) {
			player.move();
			player.aim(sf::Mouse::getPosition(*WINDOW));
			player.fire(&textureBullet, BULLET_SPEED);
			player.draw();
		}

		//Control robot1 movement
		if (robot1.exists()) {
			robot1.move();
			if (player.exists()) {
				robot1.aim((sf::Vector2i) player.getPosition());
				robot1.fire(&textureBullet, BULLET_SPEED);
			}
			robot1.draw();
		}

		//Control robot2 movement
		if (robot2.exists()) {
			robot2.move();
			if (player.exists()) {
				robot2.aim((sf::Vector2i) player.getPosition());
				robot2.fire(&textureBullet, BULLET_SPEED);
			}
			robot2.draw();
		}

		//Draw objects
		WINDOW->display();
	}
	delete WINDOW;
	delete CLOCK;
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