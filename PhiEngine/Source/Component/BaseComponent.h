#pragma once
#include "..\Engine\BaseMessage.h"
//#include "..\Engine\GameObject.h"
#include <string>

class GameObject;

class BaseComponent
{
public:

	GameObject* m_owner;
	std::string m_type;

	virtual void Awake() {}
	virtual void Start() {}
	virtual void Update() {}
	virtual void LateUpdate() {}
	virtual bool SendMessage(BaseMessage* msg) { return false; }
	

protected:

};

