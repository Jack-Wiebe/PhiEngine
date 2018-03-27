#include "GameObject.h"



GameObject::GameObject(unsigned int id)
{
	m_GameObjectID = id;
	m_Parent = NULL;
	m_transform = TransformComponent();
	m_name = std::to_string(m_GameObjectID);
}

GameObject::GameObject(unsigned int id, std::string name)
{
	m_GameObjectID = id;
	m_Parent = NULL;
	m_transform = TransformComponent();
	m_name = name;
}


GameObject::~GameObject(void)
{
	for (unsigned int i = 0; i < m_children.size(); i++)
	{
	
		delete m_children[i];
		
	}
}

void GameObject::SetName(std::string name)
{
	m_name = name;
}

std::string GameObject::GetName()
{
	return m_name;
}


bool GameObject::SetTexture(std::string filename) 
{

	if (m_tex.loadFromFile("../Assets/Images/" + filename) != true)
	{
		std::cout << "failed to load image" << std::endl;
		return false;
	}
	
	return true;

}
void GameObject::SetSprite()
{
	m_sprite.setTexture(m_tex);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);
}

void GameObject::SetScale(sf::Vector2f _scale)
{
	m_sprite.setScale(_scale);
	m_transform.SetScale(_scale);
}

void GameObject::SetScale(float x, float y)
{
	m_sprite.setScale(x,y);
	m_transform.SetScale(sf::Vector2f(x,y));
}

void GameObject::SetTransform(const TransformComponent & transform)
{
	m_transform = transform;
}

unsigned int GameObject::GetID()
{
	return m_GameObjectID;
}

TransformComponent* GameObject::GetTransform()
{
	return &m_transform;
}

TransformComponent* GameObject::GetWorldTransform()
{
	return &m_worldTransform;
}

void GameObject::SetParent(GameObject* parent)
{
	m_Parent = parent;
	m_Parent->AddChild(this);
}

void GameObject::AddChild(GameObject* child)
{
	m_children.push_back(child);
	//child->m_Parent = this;
}

void  GameObject::AddComponent(BaseComponent* component) {

	m_components.push_back(component);
	component->m_owner = this;

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
		//printf("Parent x: %f, y: %f", m_Parent->GetWorldTransform)
		m_worldTransform.SetMatrix((m_Parent->GetWorldTransform()->GetMatrix()) * (m_transform.GetMatrix()));
		//m_worldTransform = m_transform * m_Parent->m_worldTransform;

		std::cout << m_transform.GetPosition().x << " " << m_Parent->m_worldTransform.GetPosition().x << std::endl;
	}
	else
	{
		m_worldTransform = m_transform;
	}
	for (std::vector<GameObject*>::iterator i = m_children.begin(); i != m_children.end(); i++)
	{
		//std::cout << (*i)->GetName() << " " << (*i)->GetID() << std::endl;
		(*i)->Update(msec);
	}
}

void GameObject::Draw(sf::RenderWindow* mainWindow)
{
	m_sprite.setPosition(m_worldTransform.GetPosition());
	m_sprite.setScale(m_worldTransform.GetScale());
	m_sprite.setRotation(m_worldTransform.GetRotation());
	mainWindow->draw(m_sprite);
}
