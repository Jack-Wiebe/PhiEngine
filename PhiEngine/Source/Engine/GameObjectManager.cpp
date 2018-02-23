#include "GameObjectManager.h"

unsigned int GameObjectManager::newID = 0;

GameObject* GameObjectManager::Instantiate() {

	GameObject* object = new GameObject(newID);
	m_sceneGraph[newID] = object;
	newID++;
	
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
		(i->second)->Update(msec);
	}

}
