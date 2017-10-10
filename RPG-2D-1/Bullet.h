#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Sprite.h"
#include "Player.h"
#include <math.h>

class Bullet : public Sprite {
public:
	Bullet(sf::Texture* texture, sf::RenderWindow* window);
	static void Bullet::newBullet(Sprite* player, sf::RenderWindow* window, sf::Texture* texture, int time);
	static void fireAll(sf::RenderWindow* window, std::vector<Player>* players, float BULLET_SPEED);
	static sf::Vector2f Bullet::calculateAngle(Bullet& bullet);
};


static bool AVAILABLE = true;
static std::vector<Bullet> bullets;