#include "Robot.h"

Robot::Robot(sf::Texture * texture, sf::RenderWindow * window, sf::Clock* clock) : Player(texture, window, clock) {
	
}

void Robot::move() {
	if (clock->getElapsedTime().asMilliseconds() % 100 == 0) {
		int direction = (int)(rand() % 4);
		float speed = rand() % 100;

		sf::Vector2f velocity;
		if (direction == 1)
			velocity = sf::Vector2f(speed, 0);
		if (direction == 2)
			velocity = sf::Vector2f(-speed, 0);
		if (direction == 3)
			velocity = sf::Vector2f(0, speed);
		if (direction == 4)
			velocity = sf::Vector2f(0, -speed);

		if (this->getPosition().x - this->width / 2 + velocity.x <= 0 || this->getPosition().x + this->width / 2 + velocity.x >= window->getSize().x)
			velocity.x = -velocity.x;
		if (this->getPosition().y - this->height / 2 + velocity.y <= 0 || this->getPosition().y + this->height / 2 + velocity.y >= window->getSize().y)
			velocity.y = -velocity.y;

		Sprite::move(velocity);
		health.setPosition(sf::Vector2f(this->getPosition().x, this->getPosition().y - this->height / 2 - 10));
	}
}