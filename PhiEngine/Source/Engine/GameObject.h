#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Transform.hpp>
#include "..\Component\TransformComponent.h"
//#include "..\Component\PhysicsComponent.h"

//class BaseComponent;
//class TransformComponent;

#include <vector>
#include <iostream>
class GameObject
{
public:
	GameObject(unsigned int id);
	GameObject(unsigned int id, std::string name);
	~GameObject(void);

	bool SetTexture(std::string filename);
	void SetSprite();
	void SetScale(sf::Vector2f _scale);
	void SetScale(float x, float y);
	sf::Sprite* GetSprite();

	unsigned int GetID();

	void SetName(std::string);
	std::string GetName();

	void SetTransform(const TransformComponent &transform);
	TransformComponent* GetTransform();
	TransformComponent* GetWorldTransform();

	void SetParent(GameObject* parent);
	void AddChild(GameObject* child);
	virtual void OnCollision(GameObject* other);
	GameObject* GetChildByName(std::string name);

	bool HasParent();

	void AddComponent(BaseComponent* component);

	template <typename T>inline T* GetComponent()
	{
		for (std::vector<BaseComponent*>::iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			if (dynamic_cast<T*>(*it) != NULL)
			{
				return (T*)(*it);
			}
		}
		return nullptr;
	}

	virtual void Awake();
	virtual void Start();
	virtual void LateUpdate(float msec);
	virtual void Update(float msec);
	virtual void Draw(sf::RenderWindow* mainWindow);

protected:
	std::string m_name;
	unsigned int m_GameObjectID;
	GameObject* m_Parent;
	TransformComponent m_worldTransform;
	TransformComponent m_transform;

	sf::Texture m_tex;
	sf::Sprite m_sprite;

	std::vector<GameObject*> m_children;
	std::vector<BaseComponent*> m_components;

private:

};

