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

sf::Sprite * GameObject::GetSprite()
{
	return &m_sprite;
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
	child->m_Parent = this;
}

void GameObject::OnCollision(GameObject* other)
{

}

GameObject * GameObject::GetChildByName(std::string name)
{
	for (std::vector<GameObject*>::iterator i = m_children.begin(); i != m_children.end(); i++)
	{
		if ((*i)->GetName() == name)
		{
			return (*i);
		}
		else
		{
			continue;
		}
	}
	std::cout << "no child with " << name << " was found" << std::endl;
	return nullptr;
}

bool GameObject::HasParent()
{
	if (m_Parent)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void GameObject::AddComponent(BaseComponent* component) {

	m_components.push_back(component);
	component->m_owner = this;
	//std::cout << component->m_owner->GetName() << std::endl;
}

/*BaseComponent* GameObject::GetComponent(std::string type)
{
	for (std::vector<BaseComponent*>::iterator it = m_components.begin(); it != m_components.end(); ++it)
	{
		if ((*it)->m_type == type)
		{
			return (*it);
		}
	}
}*/

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
		//m_worldTransform.SetMatrix((m_Parent->GetWorldTransform()->GetMatrix()) * (m_transform.GetMatrix()));
		m_worldTransform = m_transform * m_Parent->m_worldTransform;
		std::cout << this->m_name<<" "<<this->m_Parent->GetName() << std::endl;
		//m_transform = m_Parent->m_worldTransform;

		//std::cout << "Child " << GetID() << ": " << m_transform.GetRotation() << " " << m_worldTransform.GetRotation() << std::endl;
	}
	else
	{
		//std::cout << "Parent: " << GetID() << ": " << m_transform.GetRotation() << " " << m_worldTransform.GetRotation() << std::endl;
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
	//std::cout << "Object " << GetID() << ": " << m_transform.GetRotation() << " " << m_worldTransform.GetRotation() << std::endl;
	m_sprite.setPosition(m_worldTransform.GetPosition());
	m_sprite.setScale(m_worldTransform.GetScale());
	m_sprite.setRotation(m_worldTransform.GetRotation());
	mainWindow->draw(m_sprite);
}
