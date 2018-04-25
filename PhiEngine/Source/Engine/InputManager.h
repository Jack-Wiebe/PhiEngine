#pragma once

#include "Player.h"
#include "..\Component\PhysicsComponent.h"
#include <SFML\Graphics.hpp>

class Player;
class GameObjectManager;
class PhysicsEngine;
class InputManager
{
public:
	InputManager();

	sf::RenderWindow* m_window;

	void Update(sf::RenderWindow* _mainWindow, Player* _user, Player* _user2, sf::Clock* clock,GameObjectManager* gm,PhysicsEngine* PE);

};