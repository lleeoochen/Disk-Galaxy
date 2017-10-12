#include "Player.h"

Player::Player(sf::Texture* texture, sf::RenderWindow* window, sf::Clock* clock) : Sprite(texture, window, clock) {
	this->setOrigin(this->width / 2, this->height / 2);
	health = Health();
	health.window = window;
}

bool Player::exists() {
	return this->health.currentHealth > 0;
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

void Player::fire(sf::Texture* texture, float bulletSpeed, bool autoShoot) {

	if (clock->getElapsedTime().asMilliseconds() % 100 == 0) {

		if (autoShoot || sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			Bullet bullet(texture, window, clock); //Create new bullet
			bullet.setPosition(this->getPosition());

			if (autoShoot)
				bullet.setRotation(this->getRotation());
			else
				bullet.aim(sf::Mouse::getPosition(*window));

			bullets.push_back(bullet); //Add new bullet to list
		}
	}

	fireAll(bulletSpeed);
}

void Player::draw() {
	Sprite::draw();
	health.draw();
}

void Player::setPosition(float x, float y) {
	Sprite::setPosition(x, y);
	health.setPosition(sf::Vector2f(this->getPosition().x, this->getPosition().y - this->height / 2 - 10));
}

void Player::fireAll(float bulletSpeed) {

	//Remove flashing from player being hit
	if (clock->getElapsedTime().asMilliseconds() % 200 == 0) {
		for (unsigned int j = 0; j < flashes.size(); j++) {
			Player* player = flashes[j];
			player->setColor(sf::Color::White);
			flashes.erase(flashes.begin());
			j--;
		}
	}

	//Fire all bullets
	for (unsigned int i = 0; i < bullets.size(); i++) {
		Bullet& bullet = bullets[i];

		//Bullet disappears when hit enemy
		bool shot = false;
		for (unsigned int j = 0; j < this->enemies.size() && !shot; j++) {
			Player* enemy = this->enemies[j];

			if (!enemy->exists()) {
				enemies.erase(enemies.begin() + j);
				j--;
			} 
			else if (sqrt(pow(bullet.getPosition().x - enemy->getPosition().x, 2) + pow(bullet.getPosition().y - enemy->getPosition().y, 2)) < enemy->width / 2) {
				bullets.erase(bullets.begin());
				i--;
				shot = true;
				enemy->health.setHealth(enemy->health.currentHealth - 1); //reduce health
				enemy->setColor(sf::Color(255, 0, 0));
				flashes.push_back(enemy);
			}
		}

		if (shot) continue;

		if (bullet.getPosition().x < 0 || bullet.getPosition().x > window->getSize().x || bullet.getPosition().y < 0 || bullet.getPosition().y > window->getSize().y) {
			bullets.erase(bullets.begin()); //Bullet disappears outside of window
			i--;
		}
		else {
			sf::Vector2f velocity = Bullet::calculateAngle(bullet);

			velocity.x *= bulletSpeed;
			velocity.y *= bulletSpeed;
			if (velocity.x != 0 && velocity.y != 0)
				velocity /= std::sqrt(2.f);

			bullet.move(velocity);
			(*window).draw(bullet);
		}
	}
}
