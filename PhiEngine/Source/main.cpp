#include "EngineInitialization.h"
#include <SFML\Graphics.hpp>
using namespace std;

void main(int argc, char **argv)
{
	LPCTSTR Title = "PhiEngine";
	if (!IsOnlyInstance(Title))
	{
		//error
	}
	DWORDLONG SpaceNeeded = 300000000;
	if (!CheckStorage(SpaceNeeded))
	{
		//error
	}
	DWORDLONG RAMNeeded = 300000000;
	DWORDLONG VRAMNeeded = 300000000;
	if (!CheckMemory(RAMNeeded, VRAMNeeded))
	{
		//error
	}

	DWORD Success = ReadCPUSpeed();
	system("pause");
	sf::RenderWindow window({ 1024,769 }, "wuddup wit it");
	while (window.isOpen())
	{
		sf::Event m_event;
		while (window.pollEvent(m_event))
		{
			if (m_event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear();
		window.display();
	}
}