#pragma once
#include <iostream>
#include "Bullet.h"
#include "Sprite.h"
#include "Health.h"
#include "Score.h"

class Player : public Sprite {
public:
	Player(sf::Texture* texture);
	bool exists();
	void draw();
	void updateEnemies();
	void setPosition(float x, float y);
	void fireAll(float bulletSpeed);
	void trackScore(Score* score);

	virtual void act() {};
	virtual void move() {};
	virtual void fire(float bulletSpeed) {};

	float SPEED = 0.3; 
	float BULLET_SPEED = 1;
	float deathTime = 0.f;
	int score = 0;
	bool exploded = false;
	std::vector<Player*> enemies;
	std::vector<Bullet> bullets;
	std::vector<Player*> flashes;
	Health health;
	Score* scoreboard;
};