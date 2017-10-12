#include "Sprite.h"

Sprite::Sprite(sf::Texture* texture, sf::RenderWindow* window, sf::Clock* clock) {
	if (texture != NULL) {
		texture->setSmooth(true);
		this->setTexture(*texture);
	}
	this->width = this->getGlobalBounds().width;
	this->height = this->getGlobalBounds().height;
	this->window_width = window->getSize().x;
	this->window_height = window->getSize().y;
	this->window = window;
	this->clock = clock;
}

void Sprite::aim(sf::Vector2i position) { //genrify to position vector
	sf::Vector2f playerPos = this->getPosition();
	float dx = position.x - playerPos.x;
	float dy = position.y - playerPos.y;
	float rotation = atan2(dy, dx) * 180 / PI + 90;
	this->setRotation(rotation);
}

void Sprite::draw() {
	window->draw(*this);
}