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
	void fireAll();
	void trackScore(Score* score);
	void removeFlashes();
	bool enemyShot(Bullet& bullet);
	virtual void act() {};
	virtual void move() {};
	virtual void fire(float bulletSpeed) {};

	float player_speed; 
	float deathTime;
	int id;
	int team;
	int score;
	bool exploded;
	Health health;
	Score* scoreboard;
	std::vector<Player*> enemies;
	std::vector<Player*> flashes;
	std::vector<Bullet> bullets;
	static std::vector<Player*> players;
};