#include "TransformComponent.h"



TransformComponent::TransformComponent()
{
	m_Position = sf::Vector3f(1.0f, 1.0f, 1.0f);
}

TransformComponent::TransformComponent(float x, float y, float z)
{
	m_Position = sf::Vector3f(x, y, z);
}


void TransformComponent::Awake()
{

}
void TransformComponent::Start()
{

}
void TransformComponent::Update()
{

}
void TransformComponent::LateUpdate()
{

}

bool TransformComponent::SendMessage(BaseMessage* msg) {
	return false;
}
