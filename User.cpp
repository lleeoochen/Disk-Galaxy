#include "User.h"

User::User(sf::Texture* texture) : Player(texture) {

}

void User::act() {

	if (exists()) {
		updateEnemies();
		move();
		aim(sf::Mouse::getPosition(*WINDOW));
		fire();
		draw();
	}
	else {
		if (deathTime == 0.f) { 
			deathTime = CLOCK->getElapsedTime().asSeconds();
			score = -1;
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

void User::move() {
	sf::Vector2f velocity(0.f, 0.f);

	//Four movement direction and boundary check
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && this->getPosition().x - this->width / 2 >= 0)
		velocity.x -= player_speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && this->getPosition().x + this->height / 2 <= window_width)
		velocity.x += player_speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->getPosition().y - this->width / 2 >= 0)
		velocity.y -= player_speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->getPosition().y + this->height / 2 <= window_height)
		velocity.y += player_speed;

	//Diagonal movement (/sqrt(2))
	if (velocity.x != 0 && velocity.y != 0)
		velocity /= std::sqrt(2.f);

	//Set movement
	Sprite::move(velocity);
	health.setPosition(sf::Vector2f(this->getPosition().x, this->getPosition().y - this->height / 2 - 10));
}

void User::fire() {
	if (CLOCK->getElapsedTime().asMilliseconds() % 50 == 0) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) | sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			Bullet bullet; //Create new bullet
			bullet.setPosition(this->getPosition());
			bullet.aim(sf::Mouse::getPosition(*WINDOW));
			bullet.setVelocity();
			bullets.push_back(bullet); //Add new bullet to list
		}
	}
	fireAll();
}




void User::updateEnemies() {

	//Add new enemy
	for (unsigned int i = 0; i < players.size(); i++) {
		Player* player = players[i];

		//Different team
		if (player->team != this->team) {
			bool tracked = false;

			//Check if enemy is tracked
			for (unsigned int j = 0; j < enemies.size() && !tracked; j++) {
				Player* enemy = enemies[j];
				if (player->id == enemy->id) tracked = true;
			}

			//Add if not tracked
			if (!tracked)
				enemies.push_back(player);
		}
	}

	//Delete dead enemy
	for (unsigned int i = 0; i < enemies.size(); i++) {
		Player* enemy = enemies[i];
		if (!enemy->exists()) {
			enemies.erase(enemies.begin() + i);
			i--;
		}
	}
}