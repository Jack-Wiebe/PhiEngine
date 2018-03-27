#pragma once
#include "..\Engine\BaseMessage.h"
//#include "..\Engine\GameObject.h"

class GameObject;

class BaseComponent
{
public:

	GameObject* m_owner;

	virtual void Awake() {}
	virtual void Start() {}
	virtual void Update() {}
	virtual void LateUpdate() {}
	virtual bool SendMessage(BaseMessage* msg) { return false; }
	

protected:

};

