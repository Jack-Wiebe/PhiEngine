#pragma once
#include "..\Engine\BaseMessage.h"
class BaseComponent
{
public:
	virtual void Awake() {};
	virtual void Start() {};
	virtual void Update() {};
	virtual void Late() {};
	virtual void SendMessage(BaseMessage* message) {};
	BaseComponent();
	~BaseComponent();
};

