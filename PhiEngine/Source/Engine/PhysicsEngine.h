#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#pragma once
#include <vector>
#include <map>
#include <cmath>
#include <ctime>
#include <SFML\Graphics.hpp>
//#include "..\Component\BaseComponent.h"
#include "..\Component\PhysicsComponent.h"
//#include "..\Component\TransformComponent.h"
#include "GameObject.h"


//class PhysicsComponent;

class PhysicsEngine
{
public:
	PhysicsEngine();
public:
	sf::Clock* g_Clock;
	sf::Time* g_time;
	float time;
	float groundedTol;
	struct CollisionPair
	{
	
		mutable PhysicsComponent* rigidBodyA;
		mutable PhysicsComponent* rigidBodyB;

		bool operator<(const CollisionPair &l)const
		{
			//CollisionPair returnColPair;
			//CollisionPair* ogColPair = this;

			//ogColPair->rigidBodyA
			unsigned int rbA = this->rigidBodyA->m_owner->GetID();
			unsigned int rbB = this->rigidBodyB->m_owner->GetID();
			
			return (l.rigidBodyA->m_owner->GetID() < rbA || l.rigidBodyB->m_owner->GetID() < rbB);
		}

		//bool operator<(const CollisionPair& lhs, const CollisionPair& rhs) { return lhs == rhs; }

		//bool operator==(const CollisionPair& lhs, const CollisionPair& rhs) { return lhs.i == rhs.i; }

		bool operator==(const CollisionPair &t) const
		{
			//CollisionPair* ogColPair = this;

			unsigned int rbA = this->rigidBodyA->m_owner->GetID();
			unsigned int rbB = this->rigidBodyB->m_owner->GetID();

			return (t.rigidBodyA->m_owner->GetID() == rbA && t.rigidBodyB->m_owner->GetID() == rbB);
		}

	};

	struct CollisionInfo {
		sf::Vector2f collisionNormal;
		float penetration;
	};

	void AddRigidBody(PhysicsComponent* rigidBody);
	bool isGrounded(PhysicsComponent* rigidBody);
	void Awake();
	void Start();

	void Update();
	void LateUpdate();

	float Dot(sf::Vector2f ls, sf::Vector2f rs);

	template<typename T> std::vector<T>& GetRange(std::vector<T> &ogVec, int initInd, int finalInd);

	~PhysicsEngine();
protected:
	void Integrate(float dT);
	void CheckCollisions();
	void ResolveCollisions();
public:
	void UpdatePhysics();
private:
	std::map<CollisionPair, CollisionInfo> collisions;
	std::vector<PhysicsComponent*> rigidBodies;

	
	

};

#endif