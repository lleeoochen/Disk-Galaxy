#include "Score.h"

Score::Score() {
	background = sf::RectangleShape(sf::Vector2f(WIDTH, HEIGHT));
	background.setFillColor(sf::Color::Black);
	background.setPosition(WINDOW->getSize().x - background.getGlobalBounds().width, 0);
	
	text.setFont(FONT);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setPosition(background.getPosition());
	text.setCharacterSize(10);
	text.setFillColor(sf::Color::White);
	score = 0;
}

void Score::draw() {
	this->text.setString("Points: " + std::to_string(score));
	WINDOW->draw(background);
	WINDOW->draw(text);
}