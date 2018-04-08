#include "GameObjectManager.h"

unsigned int GameObjectManager::newID = 0;

GameObjectManager::GameObjectManager()
{

}

GameObject* GameObjectManager::Instantiate() {

	GameObject* object = new GameObject(newID);
	m_sceneGraph[newID] = object;
	newID++;
	return object;

}

GameObject* GameObjectManager::Instantiate(std::string name) {

	GameObject* object = new GameObject(newID, name);
	m_sceneGraph[newID] = object;
	newID++;
	return object;

}

GameObject* GameObjectManager::FindObjectByName(std::string name) {

	for (std::map<unsigned int, GameObject*>::iterator i = m_sceneGraph.begin(); i != m_sceneGraph.end(); ++i) {
		//std::cout << i->second->GetName() << std::endl;
		if (i->second->GetName() == name)
		{
			return i->second;
		}
	}
	std::cout << "failed to find object" << std::endl;;
}

bool GameObjectManager::SendMessage(BaseMessage* msg) {

	return false;
}

void GameObjectManager::Awake() {

	for (std::map<unsigned int, GameObject*>::iterator i = m_sceneGraph.begin(); i != m_sceneGraph.end(); ++i) {
		(i->second)->Awake();
	}

}

void GameObjectManager::Start() {

	for (std::map<unsigned int, GameObject*>::iterator i = m_sceneGraph.begin(); i != m_sceneGraph.end(); ++i) {
		(i->second)->Start();
	}

}

void GameObjectManager::LateUpdate(float msec) {

	for (std::map<unsigned int, GameObject*>::iterator i = m_sceneGraph.begin(); i != m_sceneGraph.end(); ++i) {
		(i->second)->LateUpdate(msec);
	}

}

void GameObjectManager::Update(float msec) {

	for (std::map<unsigned int, GameObject*>::iterator i = m_sceneGraph.begin(); i != m_sceneGraph.end(); ++i) {
		if(!i->second->HasParent())
			(i->second)->Update(msec);
	}

}

void GameObjectManager::Draw(sf::RenderWindow* mainWindow) {

	for (std::map<unsigned int, GameObject*>::iterator i = m_sceneGraph.begin(); i != m_sceneGraph.end(); ++i) {
		(i->second)->Draw(mainWindow);
	}

}
