#pragma once

#include "SFML\Graphics.hpp"
#include "SFML\Graphics\Text.hpp"
#include <iostream>

class SplashScreen
{
private:
	static sf::Texture _splashTex;
	static sf::Sprite _splashSprite;

	static sf::Text TEST;
	static sf::Clock time;

public:
	static void draw(sf::RenderWindow& window);
	static void init(sf::Vector2f screenSize);
};