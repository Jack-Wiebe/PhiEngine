#pragma once
#include "BaseComponent.h"
#include <SFML\Graphics\Transform.hpp>
#include <SFML\System\Vector2.hpp>
#include <SFML\System\Vector3.hpp>
#include "..\Engine\PhysicsEngine.h"
#include "..\Component\TransformComponent.h"


class PhysicsComponent:BaseComponent
{
public:
	PhysicsComponent();
	float mass;
	float bounciness;

	bool obeysGravity;
	bool grounded;

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
	void SetAABB();
	void Integrate(float dt);

	~PhysicsComponent();
private:
	sf::Vector2f totalForces;
	PhysicsEngine* engine;

};