#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

class Utility {
public:
	static void addHighScore(std::string filename, std::string name, int score);
	static int getHighScore(std::string filename, std::string name);
	static void writeFile(std::string filename, std::string message);
	static std::string readFile(std::string filename);
	static sf::Texture getTexture(std::string filename);
	static sf::Font getFont(std::string filename);


private:
	template<class T> 
	static T getAsset(std::string filename);
};