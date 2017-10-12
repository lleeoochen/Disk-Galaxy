#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Sprite.h"
#include "Player.h"
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
	sf::RenderWindow window(sf::VideoMode(960, 540), "Disk Galaxy", sf::Style::Titlebar | sf::Style::Default);

	sf::Texture textureGalaxy = getTexture("galaxy.png");
	sf::Texture texture = getTexture("StartButton.png");
	sf::Font font = getFont("summit.ttf");

	sf::Text title;
	title.setString("Welcome to Disk Galaxy!");
	title.setFont(font);
	title.setPosition(window.getSize().x / 2 - title.getGlobalBounds().width / 2, window.getSize().y * 1 / 4 - title.getGlobalBounds().height / 2);
	title.setCharacterSize(30);
	title.setFillColor(sf::Color::White);

	Sprite button(&texture, &window, NULL);
	button.setPosition(window.getSize().x / 2 - button.width / 2, window.getSize().y * 3 / 4 - button.height / 2);
	Sprite background(&textureGalaxy, &window, NULL);

	//Game loop
	while (window.isOpen()) {

		//Event loop
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i mouse = sf::Mouse::getPosition(window);
				int dx = mouse.x - button.getPosition().x;
				int dy = mouse.y - button.getPosition().y;
				if (dx >= 0 && dy >= 0 && dx <= button.width && dy <= button.height) {
					window.close();
					return true;
				}
			}
		}


		//Draw window
		window.clear();
		window.draw(background);
		window.draw(button);
		window.draw(title);
		window.display();
	}
	return false;
}

void startGame() {
	//Setup textures
	sf::Texture textureUFO = getTexture("ufo.png");
	sf::Texture textureGalaxy = getTexture("galaxy.png");
	sf::Texture textureBullet = getTexture("bullet.png");

	//Setup window
	sf::RenderWindow window(sf::VideoMode(960, 540), "Disk Galaxy", sf::Style::Titlebar | sf::Style::Default);
	sf::Clock clock;
	Sprite background(&textureGalaxy, &window, &clock);

	//Setup player
	Player player(&textureUFO, &window, &clock);
	player.setPosition(window.getSize().x / 2, window.getSize().y - player.height / 2);

	//Setup enemy
	Robot robot1(&textureUFO, &window, &clock);
	robot1.setPosition(window.getSize().x / 2, window.getSize().y / 2);

	Robot robot2(&textureUFO, &window, &clock);
	robot2.setPosition(window.getSize().x / 4, window.getSize().y / 4);

	//Add enemies
	player.enemies.push_back(&robot1);
	player.enemies.push_back(&robot2);
	robot1.enemies.push_back(&player);
	robot1.enemies.push_back(&robot2);
	robot2.enemies.push_back(&player);
	robot2.enemies.push_back(&robot1);

	//Game loop
	while (window.isOpen()) {

		//Clear window
		window.clear();
		window.draw(background);

		//Event loop
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Control player movement
		if (player.exists()) {
			player.move();
			player.aim(sf::Mouse::getPosition(window));
			player.fire(&textureBullet, BULLET_SPEED, false);
			player.draw();
		}

		//Control robot1 movement
		if (robot1.exists()) {
			robot1.move();
			if (player.exists()) {
				robot1.aim((sf::Vector2i) player.getPosition());
				robot1.fire(&textureBullet, BULLET_SPEED, true);
			}
			robot1.draw();
		}

		//Control robot2 movement
		if (robot2.exists()) {
			robot2.move();
			if (player.exists()) {
				robot2.aim((sf::Vector2i) player.getPosition());
				robot2.fire(&textureBullet, BULLET_SPEED, true);
			}
			robot2.draw();
		}

		//Draw objects
		window.display();
	}
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