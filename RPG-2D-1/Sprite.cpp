#include "Sprite.h"

Sprite::Sprite(sf::Texture* texture, sf::RenderWindow* window) {
	texture->setSmooth(true);
	this->setTexture(*texture);
	this->width = this->getGlobalBounds().width;
	this->height = this->getGlobalBounds().height;
	this->window_width = window->getSize().x;
	this->window_height = window->getSize().y;
	this->window = window;
}

void Sprite::rotate() {
	sf::Vector2f playerPos = this->getPosition();
	sf::Vector2i curserPos = sf::Mouse::getPosition(*window);
	float dx = curserPos.x - playerPos.x;
	float dy = curserPos.y - playerPos.y;
	float rotation = atan2(dy, dx) * 180 / PI + 90;
	this->setRotation(rotation);
}