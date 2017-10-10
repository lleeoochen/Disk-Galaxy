#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Sprite.h"
#include "Player.h"
#include "Bullet.h"

//Variables
const float BULLET_SPEED = 1;
sf::Vector2i WIN_SIZE;
sf::Texture getTexture(std::string filename);

int main() {

	//Setup textures
	sf::Texture textureUFO = getTexture("ufo.png");
	sf::Texture textureGalaxy = getTexture("galaxy.png");
	sf::Texture textureBullet = getTexture("bullet.png");

	//Setup window
	sf::RenderWindow window(sf::VideoMode(960, 540), "Disk Galaxy", sf::Style::Titlebar | sf::Style::Default);
	Sprite background(&textureGalaxy, &window);

	//Setup player
	Player player(&textureUFO, &window);
	player.setOrigin(player.width / 2, player.height / 2);
	player.setPosition(window.getSize().x / 2, window.getSize().y - player.height / 2);

	sf::Clock clock;

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
		player.move();
		player.rotate();

		//Control bullet movement
		Bullet::newBullet(&player, &window, &textureBullet, clock.getElapsedTime().asMilliseconds());
		Bullet::fireAll(&window, BULLET_SPEED);

		//Draw objects
		window.draw(player);
		window.display();
	}

	return 0;
}

//Get texture from file
sf::Texture getTexture(std::string filename) {
	sf::Texture texture;
	texture.loadFromFile(filename);
	return texture;
}