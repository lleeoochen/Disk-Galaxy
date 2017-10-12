#include "Player.h"

Player::Player(sf::Texture* texture, sf::RenderWindow* window, sf::Clock* clock) : Sprite(texture, window, clock) {
	this->setOrigin(this->width / 2, this->height / 2);
	health = Health();
	health.window = window;
}

//Move player based on keystroke
void Player::move() {
	sf::Vector2f velocity(0.f, 0.f);

	//Four movement direction and boundary check
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && this->getPosition().x - this->width / 2 >= 0)
		velocity.x -= SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && this->getPosition().x + this->height / 2 <= window_width)
		velocity.x += SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->getPosition().y - this->width / 2 >= 0)
		velocity.y -= SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->getPosition().y + this->height / 2 <= window_height)
		velocity.y += SPEED;

	//Diagonal movement (/sqrt(2))
	if (velocity.x != 0 && velocity.y != 0)
		velocity /= std::sqrt(2.f);

	//Set movement
	Sprite::move(velocity);
	health.setPosition(sf::Vector2f(this->getPosition().x, this->getPosition().y - this->height / 2 - 10));
}

void Player::draw() {
	Sprite::draw();
	health.draw();
}

void Player::setPosition(float x, float y) {
	Sprite::setPosition(x, y);
	health.setPosition(sf::Vector2f(this->getPosition().x, this->getPosition().y - this->height / 2 - 10));
}