#include "Robot.h"

Robot::Robot(sf::Texture * texture) : Player(texture) {
	direction = 0;
}

void Robot::act() {
	if (exists()) {
		updateEnemies();
		move();
		if (enemies.size() != 0)
			aim((sf::Vector2i) (*enemies[0]).getPosition());
		fire();
		draw();
	}
	else {
		if (deathTime == 0.f) {
			deathTime = CLOCK->getElapsedTime().asSeconds();
		}
		if (CLOCK->getElapsedTime().asSeconds() - deathTime < 0.5) {
			setTexture(*TEXTURE_EXPLOSION);
			draw();
		}
		else {
			exploded = true;
		}
	}
}

void Robot::move() {

	//Change direction every 0.5 seconds
	if (CLOCK->getElapsedTime().asMilliseconds() % 500 == 0)
		direction = (int)(rand() % 4);

	//Set speed
	float speed = (rand() % 4) / 10.f;

	//Create vector from direction and speed
	sf::Vector2f velocity;
	if (direction == 0)
		velocity = sf::Vector2f(speed, 0);
	if (direction == 1)
		velocity = sf::Vector2f(-speed, 0);
	if (direction == 2)
		velocity = sf::Vector2f(0, speed);
	if (direction == 3)
		velocity = sf::Vector2f(0, -speed);

	//Border check for left and right
	if (this->getPosition().x - this->width / 2 + velocity.x <= 0 || this->getPosition().x + this->width / 2 + velocity.x >= WINDOW->getSize().x) {
		velocity.x = -velocity.x;
		if (direction == 0) 
			direction = 1;
		else 
			direction = 0;
	}

	//Border check for top and down
	if (this->getPosition().y - this->height / 2 + velocity.y <= 0 || this->getPosition().y + this->height / 2 + velocity.y >= WINDOW->getSize().y) {
		velocity.y = -velocity.y;
		if (direction == 2)
			direction = 3;
		else
			direction = 2;
	}

	//Move robot and healthbar
	Sprite::move(velocity);
	health.setPosition(sf::Vector2f(this->getPosition().x, this->getPosition().y - this->height / 2 - 10));
}

void Robot::fire() {

	if (CLOCK->getElapsedTime().asMilliseconds() % 200 == 0 && enemies.size() != 0) {
		Bullet bullet; //Create new bullet
		bullet.setPosition(this->getPosition());
		bullet.setRotation(this->getRotation());
		bullet.setVelocity();
		bullets.push_back(bullet); //Add new bullet to list
	}

	fireAll();
}