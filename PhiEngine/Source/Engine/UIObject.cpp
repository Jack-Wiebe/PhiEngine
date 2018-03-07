#include "UIObject.h"


UIObject::UIObject(unsigned int id):GameObject(id)
{

}

UIObject::UIObject(unsigned int id, std::string name):GameObject(id, name)
{

}

UIObject::UIObject(unsigned int id, std::string name, std::string txt) :GameObject(id, name)
{
	m_text.setString(txt);
}
UIObject::UIObject(unsigned int id, std::string name, std::string txt, std::string filename) : GameObject(id, name)
{
	
	if (m_font.loadFromFile("../Assets/Images/" + filename) != true)
	{
		std::cout << "failed to load font" << std::endl;
	}
	m_text.setString(txt);

}

std::string UIObject::GetText() 
{
	return m_text.getString();
}

void UIObject::SetText(std::string txt)
{
	m_text.setString(txt);
}

bool UIObject::SetFont(std::string filename)
{
	

	if (m_font.loadFromFile("../Assets/Images/" + filename) != true)
	{
		std::cout << "failed to load font" << std::endl;
	}
}

void UIObject::SetColor(sf::Color col)
{
	m_text.setFillColor(col);
}

sf::Color UIObject::GetColor()
{
	return sf::Color();
	//return m_text.getColor();
}

