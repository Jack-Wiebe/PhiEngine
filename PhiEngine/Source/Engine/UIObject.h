#pragma once

#include "GameObject.h"
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Transform.hpp>
#include "..\Component\TransformComponent.h"
#include <vector>
#include <iostream>

class UIObject:GameObject
{
public:

	UIObject(unsigned int id);
	UIObject(unsigned int id, std::string name);
	UIObject(unsigned int id, std::string name, std::string txt);
	UIObject(unsigned int id, std::string name, std::string txt, std::string filename);

	std::string GetText();
	void SetText(std::string txt);

	bool SetFont(std::string filename);

	sf::Color GetColor();
	void SetColor(sf::Color);
	

protected:
	
	sf::Text m_text;
	sf::Font m_font;

};