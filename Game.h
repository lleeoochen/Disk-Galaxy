#pragma once
#include <SFML\Graphics.hpp>
#include "Global.h"
#include "Utility.h"
#include "Score.h"
#include "Sprite.h"
#include "Player.h"
#include "User.h"
#include "Robot.h"
#include "Bullet.h"


class Game {
public:
	Game();
	void startGame();
private:
	void preRound(std::string message);
	Player startRound();
	bool toGame;
	const std::string high_score_path = "Data/high_score.csv";
};