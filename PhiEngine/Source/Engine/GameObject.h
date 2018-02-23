#pragma once
#include <SFML\Graphics\Transform.hpp>
#include "..\Component\TransformComponent.h"
#include <vector>
class GameObject
{
public:
	GameObject(unsigned int id);
	~GameObject(void);

	void setTransform(const TransformComponent &transform);
	TransformComponent GetTransform();
	TransformComponent GetWorldTransform();

	void SetParent(GameObject& parent);
	void AddChild(GameObject* child);

	void AddComponent(BaseComponent* component);

	virtual void Awake();
	virtual void Start();
	virtual void LateUpdate(float msec);
	virtual void Update(float msec);

protected:
	unsigned int m_GameObjectID;
	GameObject* m_Parent;
	TransformComponent m_worldTransform;
	TransformComponent m_transform;

	std::vector<GameObject*> m_children;
	std::vector<BaseComponent*> m_components;

private:

};

