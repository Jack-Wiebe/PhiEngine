#pragma once

#include "BaseComponent.h"
#include <SFML\Graphics\Transform.hpp>
#include <SFML\System\Vector3.hpp>


class TransformComponent : public BaseComponent {
public:
	
	TransformComponent();
	TransformComponent(float _x, float _y, float _z);

	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	bool SendMessage(BaseMessage* msg);
	sf::Vector3f m_Position;
	sf::Vector3f m_Rotation;
	sf::Vector3f m_Scale;

	 sf::Transform transformMatrix;
};
