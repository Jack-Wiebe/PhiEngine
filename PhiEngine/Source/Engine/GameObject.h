#pragma once
#include <SFML\Graphics\Transform.hpp>
#include <vector>
class GameObject
{
public:
	GameObject();
	~GameObject(void);

	void setTransform(const sf::Transform &transform);
	sf::Transform GetTransform();
	sf::Transform GetWorldTransform();

	void SetParent(GameObject& parent);
	void f_AddChild(GameObject* child);

	virtual void LateUpdate();
	virtual void Update(float msec);

protected:
	GameObject* m_Parent;
	sf::Transform m_worldTransform;
	sf::Transform m_transform;
	std::vector<GameObject*> children;

private:

};

