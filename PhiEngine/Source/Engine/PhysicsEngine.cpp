#include "PhysicsEngine.h"
#include "..\Component\PhysicsComponent.h"

PhysicsEngine::PhysicsEngine(sf::Clock* _clock)
{
	g_Clock = _clock;
	
}

template <typename T> std::vector<T>& PhysicsEngine::GetRange(std::vector<T> &ogVec, int initInd, int finalInd)
{
	vector<T> newVec;
	for (int i = a; i <= b, i++)
	{
		newVec.push_back(ogVec[i]);
	}
	return &newVec;
}

float PhysicsEngine::Dot(sf::Vector2f ls, sf::Vector2f rs)
{
	return (ls.x + rs.x) * (ls.y + rs.y);
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
	
	for (std::vector<PhysicsComponent*>::iterator it = rigidBodies.begin(); it != rigidBodies.end(); ++it)
	{
		//std::cout << "outer Integrate" << std::endl;
		(*it)->Integrate(dT);
	}
	/*for each(PhysicsComponent* rb in rigidBodies)
	{
		rb->Integrate(dT);
	}*/
}

void PhysicsEngine::CheckCollisions()
{

	for (std::vector<PhysicsComponent*>::iterator bodyA = rigidBodies.begin(); bodyA != rigidBodies.end(); bodyA++)
	{
		//rigidBodies.size() - rigidBodies.at*(bodyA)
		//int pos = std::find(rigidBodies.begin(), rigidBodies.end(), bodyA) - rigidBodies.begin();
		for (std::vector<PhysicsComponent*>::iterator bodyB = bodyA; bodyB != rigidBodies.end(); bodyB++)
		{
			if (bodyA != bodyB)
			{
				//std::cout << "Check" << std::endl;
				
				CollisionPair pair;
				CollisionInfo colInfo;
				pair.rigidBodyA = (*bodyA);
				pair.rigidBodyB = (*bodyB);
				
				//sf::Vector2f distance = pair.rigidBodyA->m_owner->GetTransform()->GetPosition() - pair.rigidBodyB->m_owner->GetTransform()->GetPosition();
				/*std::cout << pair.rigidBodyA->m_owner->GetName() << std::endl;
				std::cout << pair.rigidBodyB->m_owner->GetName() << std::endl;*/
				//std::cout << pair.rigidBodyA->m_owner->GetTransform()->GetPosition().y << std::endl;
				//std::cout << (*bodyA)->transform->GetPosition().y << std::endl;
				//std::cout << "dis x" << distance.x << "|| dis y" << distance.y << std::endl;
				
				sf::Vector2f halfsizeAbase = ((*bodyA)->aabb.tRight - (*bodyA)->aabb.bleft);
				//printf("haldsizeAbase.y: %f\n", halfsizeAbase.y);
				sf::Vector2f halfsizeA = sf::Vector2f((abs(halfsizeAbase.x)*-1)+ abs(halfsizeAbase.x),abs(halfsizeAbase.y));
				halfsizeA = halfsizeA / 2.0f;
				sf::Vector2f halfsizeBbase = ((*bodyB)->aabb.tRight - (*bodyB)->aabb.bleft);
				sf::Vector2f halfsizeB = sf::Vector2f(abs(halfsizeBbase.x), abs(halfsizeBbase.y) );
				halfsizeB = halfsizeB / 2.0f;
				//printf("haldsizeB: %f\n", halfsizeA.y);
				//printf("Body A pos original: %f, %f\n", (*bodyA)->transform->GetPosition().x, (*bodyA)->transform->GetPosition().y);
				//printf("Body B pos original: %f, %f\n", (*bodyB)->transform->GetPosition().x, (*bodyB)->transform->GetPosition().y);

				sf::Vector2f tempB = (*bodyB)->transform->GetPosition() + halfsizeB;
				sf::Vector2f tempA = (*bodyA)->transform->GetPosition() + halfsizeA;

				//printf("Body A pos new: %f, %f\n", tempA.x, tempA.y);
				//printf("Body B pos new: %f, %f\n", tempB.x, tempB.y);

				sf::Vector2f distance = tempB - tempA;
				//printf("Distance: %f, %f\n", distance.x, distance.y);

				float absDistX = abs(distance.x);
				float  absDisty = abs(distance.y);
				//std::cout << absDistX << std::endl;
				sf::Vector2f gap = sf::Vector2f(absDistX, absDisty) - (halfsizeA+halfsizeB);
				
				
				//std::cout << "gap x->" << gap.x << "|| gap y->"<<gap.y << std::endl;
				//std::cout << std::endl;
				if (gap.x <=0.0f && gap.y <= 0.0f)
				{
					//std::cout << "gap.x < 0 && gap.y < 0" <<std:: endl;
					std::map<PhysicsEngine::CollisionPair, PhysicsEngine::CollisionInfo>::iterator it = collisions.find(pair);
					if (it != collisions.end())
					{
						//element found;
						//std::cout << "map check" << std::endl;
						collisions.erase(it);
					}

					if (gap.x > gap.y)
					{
						if (distance.x > 0)
						{
							//system("pause");
							//printf("Colided");
							colInfo.collisionNormal = sf::Vector2f(1.0f, 0.0f);
						}
						else
						{
							//printf("Colided");
							//system("pause");
							colInfo.collisionNormal = sf::Vector2f(-1.0f, 0.0f);
						}
						colInfo.penetration = gap.x;
					}
					else
					{
						//std::cout << "shitfuckkers" << std::endl;
						//stem("pause");
						if (distance.y > 0)
						{
							//printf("Colided");
							//std::cout << "shit" << std::endl;
							colInfo.collisionNormal = sf::Vector2f(0.0f, 1.0f);
						}
						else
						{
							//printf("Colided");
							//std::cout << "fuck" << std::endl;
							colInfo.collisionNormal = sf::Vector2f(0.0f, -1.0f);
						}
						colInfo.penetration = gap.y;
						//system("pause");
					}
					
					collisions.insert(std::pair<PhysicsEngine::CollisionPair, PhysicsEngine::CollisionInfo>(pair, colInfo));
					//std::cout << "poop" << std::endl;
					//system("pause");
				}
				else
				{
					
					std::map<PhysicsEngine::CollisionPair, PhysicsEngine::CollisionInfo>::iterator it = collisions.find(pair);
					if (it != collisions.end())
					{
						//std::cout << "poop" << std::endl;
						//element found;
						collisions.erase(it);
						std::cout << "poop" << std::endl;
					}
				}
			}
			
		}
		
	}
}

void PhysicsEngine::ResolveCollisions()
{

	for (std::map<PhysicsEngine::CollisionPair, PhysicsEngine::CollisionInfo>::iterator it = collisions.begin(); it != collisions.end(); ++it)
	{
		
		float minBounce = std::min(it->first.rigidBodyA->bounciness, it->first.rigidBodyB->bounciness);
		float velAlongNormal = Dot(it->first.rigidBodyB->currentVelocity - it->first.rigidBodyA->currentVelocity, it->second.collisionNormal);
		if (velAlongNormal > 0) continue;

		float j = -(1 + minBounce) * velAlongNormal;
		float invMassA, invMassB;
		
		if (it->first.rigidBodyA->mass = 0)
		{
			invMassA = 0;
		}
		else
		{
			invMassA = 1 / it->first.rigidBodyA->mass;
		}
		if (it->first.rigidBodyB->mass = 0)
		{
			invMassB = 0;
		}
		else
		{
			invMassB = 1 / it->first.rigidBodyB->mass;
		}

		j /= invMassA + invMassB;

		sf::Vector2f impluse = j * it->second.collisionNormal;

		it->first.rigidBodyA->currentVelocity -= invMassA * impluse;
		it->first.rigidBodyB->currentVelocity += invMassB * impluse;

		/*if (std::abs(it->second.penetration) > 0.01f)
		{
			const float percent = 0.2;

			float invMassA, invMassB;
			if (it->first.rigidBodyA->mass == 0)
				invMassA = 1;
			else
				invMassA = 1 / it->first.rigidBodyA->mass;
			if (it->first.rigidBodyB->mass == 0)
				invMassB = 1;
			else
				invMassB = 1 / it->first.rigidBodyB->mass;

			sf::Vector2f correction = percent * it->second.penetration / (invMassA + invMassB) * -it->second.collisionNormal;

			sf::Vector2f temp = it->first.rigidBodyA->transform->GetPosition();
			temp -= invMassA * correction;
			it->first.rigidBodyA->transform->SetPosition(temp);

			temp = it->first.rigidBodyB->transform->GetPosition();
			temp += invMassB * correction;
			it->first.rigidBodyB->transform->SetPosition(temp);
			std::cout << "resolve" << std::endl;
			system("pause");

		}*/

		//system("pause");
	}
}

void PhysicsEngine::UpdatePhysics()
{
	//std::cout << g_Clock->getElapsedTime().asSeconds() << std::endl;
	CheckCollisions();
	ResolveCollisions();
	Integrate(g_Clock->getElapsedTime().asSeconds());
}
