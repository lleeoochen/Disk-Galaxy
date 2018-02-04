#include "Player.h"
std::vector<Player*> Player::players;

Player::Player(sf::Texture* texture) : Sprite(texture) {
	this->setOrigin(this->width / 2, this->height / 2);
	this->setPositionRandom();
	health = Health();
	name = "";
	id = 0;
	team = 0;
	score = 0;
	deathTime = 0;
	player_speed = 0.3f;
	exploded = false;
	scoreboard = NULL;
	players.push_back(this);

	nameText.setFont(FONT);
	nameText.setCharacterSize(12);
	nameText.setColor(sf::Color::White);
	nameText.setString(name);
	nameText.setOrigin(sf::Vector2f(nameText.getGlobalBounds().width / 2, nameText.getGlobalBounds().height / 2));
}

bool Player::exists() {
	return this->health.currentHealth > 0;
}

void Player::draw() {
	Sprite::draw();
	health.draw();
	nameText.setPosition(sf::Vector2f(this->getPosition().x, this->getPosition().y - this->height / 2 - 30));
	WINDOW->draw(nameText);

	if (scoreboard != NULL) {
		scoreboard->score = score;
		scoreboard->draw();
	}
}

void Player::setName(std::string newName) {
	name = newName;
	nameText.setString(name);
	nameText.setOrigin(sf::Vector2f(nameText.getGlobalBounds().width / 2, nameText.getGlobalBounds().height / 2));
}

void Player::setPosition(float x, float y) {
	Sprite::setPosition(x, y);
	health.setPosition(sf::Vector2f(this->getPosition().x, this->getPosition().y - this->height / 2 - 10));
	nameText.setPosition(sf::Vector2f(this->getPosition().x, this->getPosition().y - this->height / 2));
}

void Player::setPositionRandom() {
	float x = CLOCK->getElapsedTime().asMicroseconds() % 100 / 100.f * (WINDOW->getSize().x - 2 * this->width) + this->width;
	float y = CLOCK->getElapsedTime().asMicroseconds() % 100 / 100.f * (WINDOW->getSize().y - 2 * this->height) + this->height;
	setPosition(x, y);
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
