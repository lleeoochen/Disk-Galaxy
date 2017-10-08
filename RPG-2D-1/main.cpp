#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

const float SPEED = 0.3;
const int WIDTH = 700;
const int HEIGHT = 600;
void handleMovement(sf::CircleShape& player);

//Game driver
int main() {

	//Basic setup
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "RPG-2D Game!", sf::Style::Titlebar | sf::Style::Default);
	sf::CircleShape player(30.f);
	player.setFillColor(sf::Color::Blue);
	player.setOrigin(player.getRadius(), player.getRadius());

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
		window.draw(player);
		window.display();
	}

	return 0;
}

//Control player movement
void handleMovement(sf::CircleShape& player) {
	sf::Vector2f velocity(0.f, 0.f);

	//Four movement direction and boundary check
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x - player.getRadius() >= 0)
		velocity.x -= SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x + player.getRadius() <= WIDTH)
		velocity.x += SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player.getPosition().y - player.getRadius() >= 0)
		velocity.y -= SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player.getPosition().y + player.getRadius() <= HEIGHT)
		velocity.y += SPEED;

	//Diagonal movement (/sqrt(2))
	if (velocity.x != 0 && velocity.y != 0)
		velocity /= std::sqrt(2.f);

	//Move players
	player.move(velocity);
}