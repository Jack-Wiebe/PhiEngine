#include "PhysicsComponent.h"
#include "..\Engine\PhysicsEngine.h"

PhysicsComponent::PhysicsComponent()
{
	
}

void PhysicsComponent::Awake()
{
}

void PhysicsComponent::Start()
{
	SetAABB();
	engine->AddRigidBody(this);
}

void PhysicsComponent::Stop()
{
	sf::Vector2f zero(0, 0);
	currentVelocity = zero;
	totalForces = zero;
}

void PhysicsComponent::Update()
{
}

void PhysicsComponent::LateUpdate()
{
}

void PhysicsComponent::AddForc(sf::Vector2f forces)
{
	totalForces += forces;
}

bool PhysicsComponent::isGrounded()
{
	grounded = engine->isGrounded(this);
	return grounded;
}

void PhysicsComponent::SetAABB()
{
	sf::FloatRect bounds;
	if (p_sprite)
	{
	  bounds= p_sprite->getGlobalBounds();
	}
	else
	{
		bounds = sf::FloatRect(transform.GetPosition().x, transform.GetPosition().y, transform.GetScale().x, transform.GetScale().y);
	}
	aabb.bleft = sf::Vector2f(bounds.left, (bounds.top + bounds.height));
	aabb.tRight = sf::Vector2f((bounds.left + bounds.width), bounds.top);
}

void PhysicsComponent::Integrate(float dt)
{
	if (obeysGravity && !isGrounded())
	{
		AddForc(gravity);
	}
	else
	{
		if (abs(currentVelocity.y) < 0.05f)
		{
			currentVelocity.y = 0;
		}
	}

	sf::Vector2f acceleration = totalForces / mass;
	if (mass == 0)
	{
		sf::Vector2f zero(0, 0);
		acceleration = zero;
	}

	currentVelocity += acceleration*dt;

	sf::Vector2f temp = transform.GetPosition();
	temp += currentVelocity*dt;
	transform.SetPosition(temp);
	SetAABB();
	
	sf::Vector2f zero(0, 0);
	totalForces = zero;
}

void PhysicsComponent::SetGravity(sf::Vector2f newGravity)
{
	gravity = newGravity;
}

PhysicsComponent::~PhysicsComponent()
{
}
