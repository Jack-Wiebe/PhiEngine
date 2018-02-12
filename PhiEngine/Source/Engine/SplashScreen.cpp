
#include "SplashScreen.h"

void SplashScreen::draw(sf::RenderWindow& window)
{

	sf::Texture _splashTex;
	if (_splashTex.loadFromFile("Assets/Images/SplashScreen.jpg") != true)
	{
		return;
	}

	sf::Sprite _splashSprite;
	_splashSprite.setTexture(_splashTex);

	window.draw(_splashSprite);
	window.display();


}
