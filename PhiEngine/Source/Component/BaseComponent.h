#pragma once
#include "..\Engine\BaseMessage.h"
class BaseComponent
{
public:
	virtual void Awake() {}
	virtual void Start() {}
	virtual void Update() {}
	virtual void LateUpdate() {}
	virtual bool SendMessage(BaseMessage* msg) { return false; }

};

