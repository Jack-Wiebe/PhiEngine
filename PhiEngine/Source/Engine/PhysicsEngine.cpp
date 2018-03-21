#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine()
{
	time = g_time->asSeconds;
	
}

void PhysicsEngine::AddRigidBody(PhysicsComponent* rigidBody)
{
	rigidBodies.push_back(rigidBody);
}

bool PhysicsEngine::isGrounded(PhysicsComponent* rigidBody)
{
	for each  (PhysicsComponent* rb in rigidBodies)
	{
		if (rb != rigidBody)
		{
			if (rigidBody->aabb.bleft.x<rb->aabb.tRight.x
				&&rigidBody->aabb.tRight.x>rb->aabb.bleft.x
				&& abs(rigidBody->aabb.bleft.y - rb->aabb.tRight.y) <= groundedTol)
			{
				if (abs(rigidBody->currentVelocity.y)<groundedTol)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void PhysicsEngine::Awake()
{
}

void PhysicsEngine::Start()
{
}

void PhysicsEngine::Update()
{
	UpdatePhysics();
}

void PhysicsEngine::LateUpdate()
{
}

PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::Integrate(float dT)
{
	for each(PhysicsComponent* rb in rigidBodies)
	{
		rb->Integrate(dT);
	}
}

void PhysicsEngine::CheckCollisions()
{
	for (std::vector<PhysicsComponent*>::iterator bodyA = rigidBodies.begin; bodyA == rigidBodies.end - 1; ++bodyA)
	{
		for (std::vector<PhysicsComponent*>::iterator bodyB = bodyA; bodyB != rigidBodies.size() - rigidBodies.at*(bodyA);++bodyB)
		{
			if (bodyA != bodyB)
			{
				CollisionPair pair;
				CollisionInfo colInfo;
				pair.rigidBodyA = bodyA;
				pair.rigidBodyB = bodyB;
				sf::Vector2f distance = bodyB.
			}
		}
	}
}

void PhysicsEngine::ResolveCollisions()
{
}

void PhysicsEngine::PositionalCorrection(CollisionPair* c)
{
}

void PhysicsEngine::UpdatePhysics()
{
	CheckCollisions();
	ResolveCollisions();
	Integrate(time);
}
