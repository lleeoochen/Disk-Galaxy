#include "Health.h"

Health::Health() {
	this->maxHealth = 100;
	this->currentHealth = 100;
	this->redBar = sf::RectangleShape(sf::Vector2f(WIDTH, HEIGHT));
	this->greenBar = sf::RectangleShape(sf::Vector2f(WIDTH, HEIGHT));

	redBar.setOrigin(redBar.getGlobalBounds().width / 2, redBar.getGlobalBounds().height / 2);
	greenBar.setOrigin(greenBar.getGlobalBounds().width / 2, greenBar.getGlobalBounds().height / 2);

	redBar.setFillColor(sf::Color::Red);
	greenBar.setFillColor(sf::Color::Green);
}

void Health::setHealth(float health) {
	this->currentHealth = health;
}

void Health::setMaxHealth(float maxHealth) {
	this->maxHealth = maxHealth;
}

void Health::setPosition(sf::Vector2f position) {
	redBar.setPosition(position);
	greenBar.setPosition(position);
}

void Health::operator= (Health otherHealth) {
	this->currentHealth = otherHealth.currentHealth;
	this->maxHealth = otherHealth.maxHealth;
}

void Health::draw() {
	WINDOW->draw(redBar);
	if (currentHealth <= maxHealth && currentHealth >= 0) {
		greenBar.setSize(sf::Vector2f(WIDTH * currentHealth / maxHealth, HEIGHT));
		WINDOW->draw(greenBar);
	}
}
