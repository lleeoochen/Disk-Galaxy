#include "Player.h"

Player::Player(sf::Texture& texture) {
	texture.setSmooth(true);
	this->setTexture(texture);
}

int Player::getWidth(){
	return this->getGlobalBounds().width;
}

int Player::getHeight() {
	return this->getGlobalBounds().height;
}
