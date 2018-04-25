#pragma once

#include "Player.h"


#include <vector>
#include <map>
#include <iterator>

class GameObject;

class GameObjectManager
{
public:

	GameObjectManager();

	GameObject* Instantiate();
	GameObject* Instantiate(std::string name);
	Player* Instantiate(std::string name, signed int health);

	bool SendMessage(BaseMessage* msg);

	void Awake();
	void Start();
	void LateUpdate(float msec);
	void Update(float msec);
	void Draw(sf::RenderWindow* mainWindow);

	GameObject* FindObjectByName(std::string name);

private:
	
	std::map<unsigned int, GameObject*> m_sceneGraph;
	static unsigned int newID;

};