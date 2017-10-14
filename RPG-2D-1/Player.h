#pragma once
#include <iostream>
#include "Bullet.h"
#include "Sprite.h"
#include "Health.h"

class Player : public Sprite {
public:
	Player(sf::Texture* texture, sf::RenderWindow* window, sf::Clock* clock);
	bool exists();
	virtual void move() {};
	void draw();
	virtual void fire(sf::Texture* texture, float bulletSpeed) {};
	void setPosition(float x, float y);
	const float SPEED = 0.5;
	std::vector<Player*> enemies;
	std::vector<Bullet> bullets;
	std::vector<Player*> flashes;
	Health health;
	void fireAll(float bulletSpeed);
};