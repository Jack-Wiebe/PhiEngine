#pragma once
#include <vector>
#include <map>
#include <cmath>
#include <ctime>
#include <SFML\Graphics.hpp>
#include "..\Component\PhysicsComponent.h"
#include "..\Component\TransformComponent.h"


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
		PhysicsComponent* rigidBodyA;
		PhysicsComponent* rigidBodyB;
	};
	struct CollisionInfo {
		sf::Vector2f collisionNormal;
		float penetration;//;)
	};

	void AddRigidBody(PhysicsComponent* rigidBody);
	bool isGrounded(PhysicsComponent* rigidBody);
	void Awake();
	void Start();

	void Update();
	void LateUpdate();

	~PhysicsEngine();
protected:
	void Integrate(float dT);
	void CheckCollisions();
	void ResolveCollisions();
	void PositionalCorrection(CollisionPair* c);
public:
	void UpdatePhysics();
private:
	std::map<CollisionPair, CollisionInfo> collisions;
	std::vector<PhysicsComponent*> rigidBodies;

	
	

};