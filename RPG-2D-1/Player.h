#pragma once
#include <iostream>
#include "Bullet.h"
#include "Sprite.h"
#include "Health.h"

class Player : public Sprite {
public:
	Player(sf::Texture* texture);
	bool exists();
	void draw();
	void setPosition(float x, float y);
	void fireAll(float bulletSpeed);
	virtual void move() {};
	virtual void fire(float bulletSpeed) {};

	const float SPEED = 0.5;
	float deathTime = 0.f;
	std::vector<Player*> enemies;
	std::vector<Bullet> bullets;
	std::vector<Player*> flashes;
	Health health;
};