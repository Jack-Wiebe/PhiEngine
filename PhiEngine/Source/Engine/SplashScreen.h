#pragma once

#include "SFML\Graphics.hpp"
#include <iostream>

class SplashScreen
{
private:
	static sf::Texture _splashTex;
	static sf::Sprite _splashSprite;

public:
	static void draw(sf::RenderWindow& window);
	static void init(sf::Vector2f screenSize);
};