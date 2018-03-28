#pragma once

#include "GameObject.h"
#include "..\Component\PhysicsComponent.h"
#include <vector>
#include <map>
#include <iterator>


class InputManager
{
public:
	InputManager();

	void Update(sf::RenderWindow* mainWindow, GameObject* _user);

};