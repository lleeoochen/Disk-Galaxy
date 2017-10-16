#include "Bullet.h"

Bullet::Bullet() : Sprite(TEXTURE_BULLET) {
	bullet_speed = 1;
}

void Bullet::setVelocity() {
	velocity = Bullet::calculateAngle(*this);
	velocity.x *= bullet_speed;
	velocity.y *= bullet_speed;
	if (velocity.x != 0 && velocity.y != 0) 
		velocity /= std::sqrt(2.f);
}

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