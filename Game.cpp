#include "Game.h"

Game::Game() {
	toGame = true;
}


void Game::startGame() {
	preRound("Welcome to Disk Galaxy!"); //Display startup screen
	while (toGame) {

		if (toGame) {
			Player player = startRound(); //Display gaming screen

			if (player.score >= Utility::getHighScore(high_score_path, player.name))
				Utility::addHighScore(high_score_path, player.name, player.score);

			if (player.score >= 0)
				preRound("You Won!\n\nScore: " + std::to_string(player.score));
			else
				preRound("You Lost...\n\nScore: " + std::to_string(player.score));
		}
	}
}


void Game::preRound(std::string message) {

	//Setup title
	sf::Text title;
	title.setString(message);
	title.setFont(FONT);
	title.setPosition(WINDOW->getSize().x / 2 - title.getGlobalBounds().width / 2, WINDOW->getSize().y * 1 / 4 - title.getGlobalBounds().height / 2);
	title.setCharacterSize(30);
	title.setColor(sf::Color::White);

	//Setup background
	Sprite background(TEXTURE_GALAXY);

	//Setup button
	Sprite button(TEXTURE_BUTTON);
	button.setPosition(WINDOW->getSize().x / 2 - button.width / 2, WINDOW->getSize().y * 3 / 4 - button.height / 2);

	//Game loop
	while (WINDOW->isOpen()) {

		//Event loop
		sf::Event event;
		while (WINDOW->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				WINDOW->close();
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i mouse = sf::Mouse::getPosition(*WINDOW);
				float dx = mouse.x - button.getPosition().x;
				float dy = mouse.y - button.getPosition().y;
				if (dx >= 0 && dy >= 0 && dx <= button.width && dy <= button.height) {
					toGame = true;
					return;
				}
			}
		}

		//Draw window
		WINDOW->clear();
		WINDOW->draw(background);
		WINDOW->draw(title);
		WINDOW->draw(button);
		WINDOW->display();
	}
	toGame = false;
}


Player Game::startRound() {
	float gameOverTime = 0.f;
	float gameOverDelay = 1.f;

	//Reset clock
	CLOCK->restart();

	//Setup background
	Sprite background(TEXTURE_GALAXY);

	//Setup players
	User user1(TEXTURE_UFO);
	Robot robot1(TEXTURE_UFO);
	Robot robot2(TEXTURE_UFO_ENEMY);
	Robot robot3(TEXTURE_UFO_ENEMY);

	//Setup score board
	Score scoreboard;
	user1.trackScore(&scoreboard);

	//Add enemies
	user1.id = 0; user1.team = 0; user1.name = "Wei Tung";
	robot1.id = 1; robot1.team = 0;
	robot2.id = 2; robot2.team = 1;
	robot3.id = 3; robot3.team = 1;

	//Game loop
	while (WINDOW->isOpen()) {

		//Clear window
		WINDOW->clear();
		WINDOW->draw(background);

		//Event loop
		sf::Event event;
		while (WINDOW->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				WINDOW->close();
				return user1;
			}
		}

		//Players act
		user1.act();
		robot1.act();
		robot2.act();
		robot3.act();

		//Draw players
		WINDOW->display();

		if (!user1.exists() || user1.enemies.size() == 0) {
			if (gameOverTime == 0.f)
				gameOverTime = CLOCK->getElapsedTime().asSeconds();
			if (CLOCK->getElapsedTime().asSeconds() - gameOverTime >= gameOverDelay)
				return user1;
		}
	}

	return user1;
}