#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Sprite.h"
#include "Player.h"
#include "Bullet.h"

//Variables
const float BULLET_SPEED = 1;
std::vector<Player*> players;
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
	sf::Clock clock;

	//Setup player
	Player player(&textureUFO, &window);
	player.setPosition(window.getSize().x / 2, window.getSize().y - player.height / 2);

	Player health(NULL, &window);
	health.setScale(5, 5);
	health.setColor(sf::Color::Green);

	//Setup enemy
	Player enemy(&textureUFO, &window);
	enemy.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	players.push_back(&enemy);

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
		Bullet::fireAll(&window, &players, BULLET_SPEED, clock.getElapsedTime().asMilliseconds());

		//Draw objects
		window.draw(player);
		window.draw(enemy);
		window.draw(health);
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