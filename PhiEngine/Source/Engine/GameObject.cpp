#include "GameObject.h"



GameObject::GameObject()
{
	m_Parent = NULL;
}


GameObject::~GameObject(void)
{
	for (unsigned int i = 0; i < m_children.size(); i++)
	{
	
		delete m_children[i];
		
	}
}

void GameObject::setTransform(const TransformComponent & transform)
{
	m_transform = transform;
}

TransformComponent GameObject::GetTransform()
{
	return m_transform;
}

TransformComponent GameObject::GetWorldTransform()
{
	return m_worldTransform;
}

void GameObject::SetParent(GameObject& parent)
{
	m_Parent = &parent;
	m_Parent->AddChild(this);
}

void GameObject::AddChild(GameObject* child)
{
	m_children.push_back(child);
	child->m_Parent = this;
}

void  GameObject::AddComponent(BaseComponent* component) {

	m_components.push_back(component);

}

void GameObject::Awake(){

}

void GameObject::Start() {

}

void GameObject::LateUpdate(float msec)
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
	for (std::vector<GameObject*>::iterator i = m_children.begin(); i != m_children.end(); i++)
	{
		(*i)->Update(msec);
	}
}
