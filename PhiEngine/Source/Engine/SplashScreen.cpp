
#include "SplashScreen.h"

sf::Texture SplashScreen::_splashTex;
sf::Sprite SplashScreen::_splashSprite;

void SplashScreen::draw(sf::RenderWindow& window)
{


	window.draw(_splashSprite);
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
}
