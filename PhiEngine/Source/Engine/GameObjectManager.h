#pragma once

#include "GameObject.h"
#include <vector>
#include <map>
#include <iterator>


class GameObjectManager
{
public:

	GameObject* Instantiate();

	bool SendMessage(BaseMessage* msg);

	void Awake();
	void Start();
	void LateUpdate(float msec);
	void Update(float msec);


private:
	
	std::map<unsigned int, GameObject*> m_sceneGraph;
	static unsigned int newID;

};