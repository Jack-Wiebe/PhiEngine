#pragma once
#include "BaseComponent.h"
#include <SFML\Graphics\Transform.hpp>
#include <SFML\System\Vector2.hpp>
#include <SFML\System\Vector3.hpp>
#include "..\Engine\PhysicsEngine.h"
#include "..\Engine\GameObject.h"
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
	sf::Vector2f gravity=sf::Vector2f(0.0f, -9.8f);
	struct AABB
	{
		public:
			sf::Vector2f bleft;
			sf::Vector2f tRight;
	};

	AABB aabb;

	void Awake() override;
	void Start() override;
	void Stop();
	void Update() override;
	void LateUpdate() override;

	void AddForc(sf::Vector2f forces);
	bool isGrounded();
	void SetAABB();
	void Integrate(float dt);
	void SetGravity(sf::Vector2f newGravity);

	~PhysicsComponent();
private:
	
	sf::Vector2f totalForces;
	PhysicsEngine* engine;
	sf::Sprite* p_sprite;

};