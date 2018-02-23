#pragma once

#include "BaseComponent.h"
#include <SFML\Graphics\Transform.hpp>
#include <SFML\System\Vector3.hpp>


class TransformComponent : public BaseComponent {
public:
	
	TransformComponent();
	TransformComponent(float _x, float _y);

	TransformComponent operator*(const TransformComponent& t)
	{
		TransformComponent trans = TransformComponent();
		trans.transformMatrix = t.transformMatrix * this->transformMatrix;
		return trans;
	}

	bool SendMessage(BaseMessage* msg);

	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	

protected:
	sf::Vector2f m_Position;
	float        m_Rotation;
	sf::Vector2f m_Scale;

	 sf::Transform transformMatrix;
};
