#include "User.h"

User::User(sf::Texture* texture) : Player(texture) {

}

void User::move() {
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

void User::fire(sf::Texture* textureBullet, float bulletSpeed) {
	if (CLOCK->getElapsedTime().asMilliseconds() % 100 == 0) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) | sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			Bullet bullet(textureBullet); //Create new bullet
			bullet.setPosition(this->getPosition());
			bullet.aim(sf::Mouse::getPosition(*WINDOW));
			bullets.push_back(bullet); //Add new bullet to list
		}
	}
	fireAll(bulletSpeed);
}
