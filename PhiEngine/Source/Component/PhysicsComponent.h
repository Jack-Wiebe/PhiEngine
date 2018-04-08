#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H
//#include "BaseComponent.h"
#include <SFML\Graphics\Transform.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\System\Vector2.hpp>
#include <SFML\System\Vector3.hpp>
//#include "..\Engine\PhysicsEngine.h"
#include "..\Component\TransformComponent.h"
//#include "BaseComponent.h"

class PhysicsEngine;
//class TransformComponent;

//class BaseComponent;

class PhysicsComponent: public BaseComponent
{
public:
	PhysicsComponent(PhysicsEngine* _engine);
	PhysicsComponent(PhysicsEngine* _engine, sf::Vector2f _gravity);
	PhysicsComponent(PhysicsEngine* _engine, sf::Vector2f _gravity, bool, float);
	float mass;
	float bounciness;
	sf::Vector2f gravity;
	bool obeysGravity = true;
	bool grounded = false;

	TransformComponent transform;

	sf::Vector2f currentVelocity;
	sf::Vector2f maxVelocity;

	struct AABB
	{
		public:
			sf::Vector2f bleft;
			sf::Vector2f tRight;
	};

	AABB aabb;

	void Awake();
	void Start();
	void Stop();
	void Update();
	void LateUpdate();

	void AddForc(sf::Vector2f);
	bool isGrounded();
	void SetGravity(sf::Vector2f newGravity);
	void SetAABB();
	void Integrate(float dt);

	~PhysicsComponent();
private:
	sf::Vector2f totalForces;
	PhysicsEngine* engine;
	sf::Sprite *p_sprite;
};

#endif