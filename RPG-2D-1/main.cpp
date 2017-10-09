#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Player.h"

const float PI = 3.1415926;
const float SPEED = 0.5;
const float BULLET_SPEED = 1;
const int WIDTH = 960;
const int HEIGHT = 540;
bool AVAILABLE = true;
std::vector<Player> bullets;

void handleMovement(Player& player);
void handleRotation(Player& player, sf::RenderWindow& window);
void handleBullet(Player& player, sf::RenderWindow& window, sf::Texture& texture, int time);
sf::Texture getTexture(std::string filename);

int main() {

	//Setup window
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Disk Galaxy", sf::Style::Titlebar | sf::Style::Default);

	//Setup textures
	sf::Texture textureUFO = getTexture("ufo.png");
	sf::Texture textureGalaxy = getTexture("galaxy.png");
	sf::Texture textureBullet = getTexture("bullet.png");

	//Setup players
	Player background(textureGalaxy);
	Player player(textureUFO);
	player.setOrigin(player.getWidth() / 2, player.getHeight() / 2);
	player.setPosition(WIDTH / 2, HEIGHT - player.getHeight() / 2);

	sf::Clock clock;

	//Game loop
	while (window.isOpen()) {

		//Clear window
		window.clear();
		window.draw(background);

		//Event loop
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Control movement and rotation
		handleMovement(player);
		handleRotation(player, window);
		handleBullet(player, window, textureBullet, clock.getElapsedTime().asMilliseconds());

		//Draw objects
		window.draw(player);
		window.display();
	}

	return 0;
}



//Control player movement
void handleMovement(Player& player) {
	sf::Vector2f velocity(0.f, 0.f);

	//Four movement direction and boundary check
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x - player.getWidth() / 2 >= 0)
		velocity.x -= SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x + player.getWidth() / 2 <= WIDTH)
		velocity.x += SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player.getPosition().y - player.getHeight() / 2 >= 0)
		velocity.y -= SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player.getPosition().y + player.getHeight() / 2 <= HEIGHT)
		velocity.y += SPEED;

	//Diagonal movement (/sqrt(2))
	if (velocity.x != 0 && velocity.y != 0)
		velocity /= std::sqrt(2.f);

	//Move players
	player.move(velocity);
}

//Control player rotation
void handleRotation(Player& player, sf::RenderWindow& window) {
	sf::Vector2f playerPos = player.getPosition();
	sf::Vector2i curserPos = sf::Mouse::getPosition(window);

	float dx = curserPos.x - playerPos.x;
	float dy = curserPos.y - playerPos.y;

	float rotation = atan2(dy, dx) * 180 / PI + 90;
	player.setRotation(rotation);
}

//Control bullet
void handleBullet(Player& player, sf::RenderWindow& window, sf::Texture& texture, int time) {

	if (time % 100 == 0)
		AVAILABLE = true;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && AVAILABLE) {
		Player bullet(texture);
		bullet.setPosition(player.getPosition());
		handleRotation(bullet, window);
		bullets.push_back(bullet);
		AVAILABLE = false;
	}

	for (int i = 0; i < bullets.size(); i++) {
		Player& bullet = bullets[i];
		if (bullet.getPosition().x < 0 || bullet.getPosition().x > WIDTH || bullet.getPosition().y < 0 || bullet.getPosition().y > HEIGHT) {
			bullets.erase(bullets.begin());
			i--;
		}
		else {

			float angle;
			sf::Vector2f velocity(0, 0);
			if (bullet.getRotation() >= 270) {
				angle = bullet.getRotation() - 270;
				velocity.x = -cosf(angle * PI / 180) * BULLET_SPEED;
				velocity.y = -sinf(angle * PI / 180) * BULLET_SPEED;
			}
			else if (bullet.getRotation() >= 180) {
				angle = bullet.getRotation() - 180;
				velocity.x = -sinf(angle * PI / 180) * BULLET_SPEED;
				velocity.y = cosf(angle * PI / 180) * BULLET_SPEED;
			}
			else if (bullet.getRotation() >= 90) {
				angle = bullet.getRotation() - 90;
				velocity.x = cosf(angle * PI / 180) * BULLET_SPEED;
				velocity.y = sinf(angle * PI / 180) * BULLET_SPEED;
			}
			else {
				angle = bullet.getRotation();
				velocity.x = sinf(angle * PI / 180) * BULLET_SPEED;
				velocity.y = -cosf(angle * PI / 180) * BULLET_SPEED;
			}

			bullet.move(velocity);
			window.draw(bullet);
		}
	}
}

//Get texture from file
sf::Texture getTexture(std::string filename) {
	sf::Texture texture;
	texture.loadFromFile(filename);
	return texture;
}