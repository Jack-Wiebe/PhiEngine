#include "Player.h"
#include "GameObjectManager.h"
#include "PhysicsEngine.h"






void Player::fire(GameObjectManager* gm, PhysicsEngine* pE, Vector2f pos, Vector2f vel,float rot, Vector2f offset)
{
	
	GameObject* b = gm->Instantiate("bullet");
	b->GetTransform()->SetPosition(pos+offset);
	b->GetTransform()->SetRotation(rot);
	b->AddComponent(new PhysicsComponent(pE));
	b->GetComponent<PhysicsComponent>()->currentVelocity=vel;
	
	b->SetTexture("Accorn.png");
	b->SetSprite();
	b->GetComponent<PhysicsComponent>()->Awake();



}
