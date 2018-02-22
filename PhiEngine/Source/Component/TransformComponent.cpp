#include "TransformComponent.h"



TransformComponent::TransformComponent()
{
	m_Position = sf::Vector2f(1.0f, 1.0f);
}

TransformComponent::TransformComponent(float x, float y)
{
	m_Position = sf::Vector2f(x, y);
}


void TransformComponent::Awake()
{
	sf::Transform trans;
	trans = sf::Transform();
	trans = trans.translate(m_Position);
	trans = trans.rotate(m_Rotation);
	trans = trans.scale(m_Scale);
	transformMatrix = trans;
}
void TransformComponent::Start()
{

}
void TransformComponent::Update()
{
	sf::Transform trans;
	trans = sf::Transform();
	trans = trans.translate(m_Position);
	trans = trans.rotate(m_Rotation);
	trans = trans.scale(m_Scale);
	transformMatrix = trans;
}
void TransformComponent::LateUpdate()
{

}

bool TransformComponent::SendMessage(BaseMessage* msg) {
	return false;
}
