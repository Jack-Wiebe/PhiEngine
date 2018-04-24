#pragma once

#include "GameObject.h"
#include "..\Component\PhysicsComponent.h"
#include <SFML\Graphics.hpp>


class InputManager
{
public:
	InputManager();

	sf::RenderWindow* m_window;

	void Update(sf::RenderWindow* _mainWindow, GameObject* _user, GameObject* _user2, sf::Clock* clock);

};