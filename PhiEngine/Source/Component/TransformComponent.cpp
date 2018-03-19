#include "TransformComponent.h"



TransformComponent::TransformComponent()
{
	m_Position = sf::Vector2f(1.0f, 1.0f);
	m_Rotation = 0.0f;
	m_Scale = sf::Vector2f(1.0f, 1.0f);
}

TransformComponent::TransformComponent(float x, float y)
{
	m_Position = sf::Vector2f(x, y);
	m_Rotation = 0.0f;
	m_Scale = sf::Vector2f(1.0f, 1.0f);
}

sf::Vector2f TransformComponent::GetPosition()
{
	return m_Position;
}
float TransformComponent::GetRotation() {
	return m_Rotation;
}
sf::Vector2f TransformComponent::GetScale() {
	return m_Scale;
}

void TransformComponent::SetPosition(sf::Vector2f pos) {
	m_Position = pos;
}

void TransformComponent::SetRotation(float rot) {
	m_Rotation = rot;
}

void TransformComponent::SetScale(sf::Vector2f scale)
{
	m_Scale = scale;
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
