#include "Utility.h"

//Write high score
void Utility::addHighScore(std::string filename, std::string name, int score) {
	writeFile(filename, name + "," + std::to_string(score));
}

//Read high score
int Utility::getHighScore(std::string filename, std::string name) {
	std::fstream data(filename);
	std::string row, value = "";

	while (std::getline(data, row)) {
		std::stringstream lineStream(row);
		std::string cell;
		if (std::getline(lineStream, cell, ',') && cell == name) {
			std::getline(lineStream, cell, ',');
			value = cell;
		}
	}

	if (value == "")
		value = "-1";

	std::cout << std::stoi(value) << std::endl;
	return std::stoi(value);
}

//Write file
void Utility::writeFile(std::string filename, std::string message) {
	std::ofstream stream;
	stream.open(filename);
	stream << message << std::endl;
	stream.close();
}

//Read file
std::string Utility::readFile(std::string filename) {
	std::fstream data(filename);
	std::string row, value = "";
	while (std::getline(data, row))
		value += row;
	return value;
}

sf::Texture Utility::getTexture(std::string filename) {
	return getAsset<sf::Texture>(filename);
}

sf::Font Utility::getFont(std::string filename) {
	return getAsset<sf::Font>(filename);
}

//Get texture from file
template<class T>
T Utility::getAsset(std::string filename) {
	T obj;
	if (!obj.loadFromFile("Assets/" + filename))
		std::cout << filename << " not found." << std::endl;
	return obj;
}