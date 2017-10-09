#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Player.h"

const float SPEED = 0.5;
const int WIDTH = 960;
const int HEIGHT = 540;
void handleMovement(sf::Sprite& player);
sf::Texture getTexture(std::string filename);

//Game driver
int main() {

	//Setup window
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Galaxy Game!", sf::Style::Titlebar | sf::Style::Default);

	//Setup textures
	sf::Texture textureUFO = getTexture("ufo.png");
	sf::Texture textureGalaxy = getTexture("galaxy.png");

	//Setup background
	Player background(textureGalaxy);

	//Setup player
	Player player(textureUFO);
	player.setOrigin(player.getWidth() / 2, player.getHeight() / 2);
	player.setPosition(WIDTH / 2, HEIGHT - player.getHeight() / 2);

	//Game loop
	while (window.isOpen()) {

		//Event loop
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Control movement
		handleMovement(player);

		//Draw objects
		window.clear();
		window.draw(background);
		window.draw(player);
		window.display();
	}

	return 0;
}

//Control player movement
void handleMovement(sf::Sprite& player) {
	sf::Vector2f velocity(0.f, 0.f);

	//Four movement direction and boundary check
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x - player.getGlobalBounds().width / 2 >= 0)
		velocity.x -= SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x + player.getGlobalBounds().width / 2 <= WIDTH)
		velocity.x += SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player.getPosition().y - player.getGlobalBounds().height / 2 >= 0)
		velocity.y -= SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player.getPosition().y + player.getGlobalBounds().height / 2 <= HEIGHT)
		velocity.y += SPEED;

	//Diagonal movement (/sqrt(2))
	if (velocity.x != 0 && velocity.y != 0)
		velocity /= std::sqrt(2.f);

	//Move players
	player.move(velocity);
}

//Get texture from file
sf::Texture getTexture(std::string filename) {
	sf::Texture texture;
	texture.loadFromFile(filename);
	return texture;
}