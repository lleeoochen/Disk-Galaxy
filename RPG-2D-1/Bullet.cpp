#include "Bullet.h"

Bullet::Bullet(sf::Texture* texture, sf::RenderWindow* window) : Sprite(texture, window) {
	
}

void Bullet::newBullet(Sprite* player, sf::RenderWindow* window, sf::Texture* texture, int time) {

	if (time % 100 == 0)
		AVAILABLE = true;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && AVAILABLE) {
		Bullet bullet(texture, window); //Create new bullet
		bullet.setPosition((*player).getPosition());
		bullet.rotate();

		bullets.push_back(bullet); //Add new bullet to list
		AVAILABLE = false;
	}
}

void Bullet::fireAll(sf::RenderWindow* window, std::vector<Player>* players, float BULLET_SPEED) {
	for (unsigned int i = 0; i < bullets.size(); i++) {
		Bullet& bullet = bullets[i];

		bool shot = false;
		for (unsigned int j = 0; j < players->size() && !shot; j++) {
			Player player = (*players)[j];
			if ( sqrt(
				pow(bullet.getPosition().x - player.getPosition().x, 2) + 
				pow(bullet.getPosition().y - player.getPosition().y, 2)) < player.width / 2) {
				bullets.erase(bullets.begin());
				i--;
				shot = true;
			}
		}

		if (shot) {
			//shot, do nothing
		}
		else if (bullet.getPosition().x < 0 || bullet.getPosition().x > window->getSize().x || bullet.getPosition().y < 0 || bullet.getPosition().y > window->getSize().y) {
			bullets.erase(bullets.begin());
			i--;
		}
		else {
			sf::Vector2f velocity = calculateAngle(bullet);

			velocity.x *= BULLET_SPEED;
			velocity.y *= BULLET_SPEED;
			if (velocity.x != 0 && velocity.y != 0)
				velocity /= std::sqrt(2.f);

			bullet.move(velocity);
			(*window).draw(bullet);
		}
	}
}

//Calculate angle between 4 quadrants
sf::Vector2f Bullet::calculateAngle(Bullet& bullet) {
	float angle;
	sf::Vector2f velocity(0, 0);
	if (bullet.getRotation() >= 270) {
		angle = bullet.getRotation() - 270;
		velocity.x = -cosf(angle * PI / 180);
		velocity.y = -sinf(angle * PI / 180);
	}
	else if (bullet.getRotation() >= 180) {
		angle = bullet.getRotation() - 180;
		velocity.x = -sinf(angle * PI / 180);
		velocity.y = cosf(angle * PI / 180);
	}
	else if (bullet.getRotation() >= 90) {
		angle = bullet.getRotation() - 90;
		velocity.x = cosf(angle * PI / 180);
		velocity.y = sinf(angle * PI / 180);
	}
	else {
		angle = bullet.getRotation();
		velocity.x = sinf(angle * PI / 180);
		velocity.y = -cosf(angle * PI / 180);
	}
	return velocity;
}