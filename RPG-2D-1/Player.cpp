#include "Player.h"

Player::Player(sf::Texture* texture) : Sprite(texture) {
	this->setOrigin(this->width / 2, this->height / 2);
	this->setPosition(
		CLOCK->getElapsedTime().asMicroseconds() % 100 / 100.f * WINDOW->getSize().x, 
		CLOCK->getElapsedTime().asMicroseconds() % 100 / 100.f * WINDOW->getSize().y);
	health = Health();
	team = 0;
	score = 0;
	deathTime = 0;
	player_speed = 0.3f;
	exploded = false;
}

bool Player::exists() {
	return this->health.currentHealth > 0;
}

void Player::draw() {
	Sprite::draw();
	health.draw();

	if (scoreboard != NULL) {
		scoreboard->score = score;
		scoreboard->draw();
	}
}

void Player::updateEnemies() {
	for (unsigned int i = 0; i < enemies.size(); i++) {
		Player* enemy = enemies[i];
		if (!enemy->exists()) {
			enemies.erase(enemies.begin() + i);
			i--;
		}
	}
}

void Player::setPosition(float x, float y) {
	Sprite::setPosition(x, y);
	health.setPosition(sf::Vector2f(this->getPosition().x, this->getPosition().y - this->height / 2 - 10));
}

void Player::fireAll() {

	removeFlashes();

	//Fire all bullets
	for (unsigned int i = 0; i < bullets.size(); i++) {
		Bullet& bullet = bullets[i];

		//Bullet shot enemy
		if (enemyShot(bullet)) {
			i--;
			continue;
		}

		//Bullet went outside of window
		if (bullet.getPosition().x < 0 || bullet.getPosition().x > WINDOW->getSize().x || bullet.getPosition().y < 0 || bullet.getPosition().y > WINDOW->getSize().y) {
			bullets.erase(bullets.begin()); //Bullet disappears outside of window
			i--;
			continue;
		}

		//Draw bullet
		bullet.move(bullet.velocity);
		(*WINDOW).draw(bullet);
	}
}

void Player::trackScore(Score* scoreboard) {
	this->scoreboard = scoreboard;
}

//Remove flashing from player being hit
void Player::removeFlashes() {
	if (CLOCK->getElapsedTime().asMilliseconds() % 200 == 0) {
		for (unsigned int j = 0; j < flashes.size(); j++) {
			Player* player = flashes[j];
			player->setColor(sf::Color::White);
			flashes.erase(flashes.begin());
			j--;
		}
	}
}

//Bullet disappears when hit enemy
bool Player::enemyShot(Bullet& bullet) {
	bool shot = false;
	for (unsigned int j = 0; j < this->enemies.size() && !shot; j++) {
		Player* enemy = this->enemies[j];

		if (sqrt(pow(bullet.getPosition().x - enemy->getPosition().x, 2) + pow(bullet.getPosition().y - enemy->getPosition().y, 2)) < enemy->width / 2) {
			bullets.erase(bullets.begin());
			shot = true;
			enemy->health.setHealth(enemy->health.currentHealth - 1); //reduce health
			enemy->setColor(sf::Color(255, 0, 0));
			flashes.push_back(enemy);

			float ds = 60 / (CLOCK->getElapsedTime().asSeconds());
			if (ds == 0) score += 1;
			else score += int(ds);
		}
	}
	return shot;
}
