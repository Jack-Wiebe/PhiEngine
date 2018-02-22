#pragma once
#include <SFML\Graphics\Transform.hpp>
#include "..\Component\TransformComponent.h"
#include <vector>
class GameObject
{
public:
	GameObject();
	~GameObject(void);

	void setTransform(const TransformComponent &transform);
	TransformComponent GetTransform();
	TransformComponent GetWorldTransform();

	void SetParent(GameObject& parent);
	void AddChild(GameObject* child);

	virtual void LateUpdate();
	virtual void Update(float msec);

protected:
	GameObject* m_Parent;
	TransformComponent m_worldTransform;
	TransformComponent m_transform;
	std::vector<GameObject*> children;

private:

};

