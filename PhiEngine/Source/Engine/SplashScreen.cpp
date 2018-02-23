
#include "SplashScreen.h"

sf::Texture SplashScreen::_splashTex;
sf::Sprite SplashScreen::_splashSprite;

sf::Text SplashScreen::TEST;
sf::Clock SplashScreen::time;

void SplashScreen::draw(sf::RenderWindow& window)
{

	TEST.setString(std::to_string(time.getElapsedTime().asSeconds()));
	TEST.setPosition(window.getSize().x / 2, window.getSize().y / 2);

	//std::cout << std::to_string(time.getElapsedTime().asSeconds()) << std::endl;

	window.clear();
	window.draw(_splashSprite);
	window.draw(TEST);
	window.display();
	//std::cout << "SPLASH!" << std::endl;

}
void SplashScreen::init(sf::Vector2f screenSize)
{

	if (_splashTex.loadFromFile("../Assets/Images/splashscreen.jpeg") != true)
	{
		return;
	}

	_splashSprite.setTexture(_splashTex);
	_splashSprite.setPosition(0.0f, 0.0f);
	_splashSprite.setScale(
		screenSize.x / _splashSprite.getLocalBounds().width,
		screenSize.y / _splashSprite.getLocalBounds().height);

	TEST = sf::Text();
	TEST.setPosition(screenSize.x / 2, screenSize.y / 2);
	TEST.setFillColor(sf::Color::Magenta);
	time = sf::Clock();

}
