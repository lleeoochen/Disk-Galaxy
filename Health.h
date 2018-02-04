#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Global.h"

class Health {
public:
	Health();
	void setHealth(float health);
	void setMaxHealth(float maxHealth);
	void setPosition(sf::Vector2f position);
	void operator=(Health otherHealth);
	void draw();

	const float HEIGHT = 5.f;
	const float WIDTH = 100.f;
	float currentHealth;
	float maxHealth;
	sf::RectangleShape redBar;
	sf::RectangleShape greenBar;
};