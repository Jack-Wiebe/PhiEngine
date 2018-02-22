#include "GameObject.h"



GameObject::GameObject()
{
	m_Parent = NULL;
}


GameObject::~GameObject(void)
{
	for (unsigned int i = 0; i < children.size(); i++)
	{
	
		delete children[i];
		
	}
}

void GameObject::setTransform(const sf::Transform & transform)
{
	m_transform = transform;
}

sf::Transform GameObject::GetTransform()
{
	return m_transform;
}

sf::Transform GameObject::GetWorldTransform()
{
	return m_worldTransform;
}

void GameObject::SetParent(GameObject& parent)
{
	m_Parent = &parent;
	m_Parent->f_AddChild(this);
}

void GameObject::f_AddChild(GameObject* child)
{
	children.push_back(child);
	child->m_Parent = this;
}

void GameObject::LateUpdate()
{
}

void GameObject::Update(float msec)
{
	if (m_Parent)
	{
		m_worldTransform = m_Parent->m_worldTransform*m_transform;
	}
	else
	{
		m_worldTransform = m_transform;
	}
	for (std::vector<GameObject*>::iterator i = children.begin;
		i != children.end(); i++)
	{
		(*i)->Update(msec);
	}
}
