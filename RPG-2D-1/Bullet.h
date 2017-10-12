#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Sprite.h"
#include <math.h>

class Bullet : public Sprite {
public:
	Bullet(sf::Texture* texture, sf::RenderWindow* window, sf::Clock* clock);
	/*
	static void Bullet::newBullet(Sprite* player, sf::RenderWindow* window, sf::Texture* texture, sf::Clock* clock);
	static void fireAll(sf::RenderWindow* window, std::vector<Player*>* players, float BULLET_SPEED, sf::Clock* clock);
	*/
	static sf::Vector2f Bullet::calculateAngle(Bullet& bullet);
	sf::Clock* clock;
};


static bool AVAILABLE = true;