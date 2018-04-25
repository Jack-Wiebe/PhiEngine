#pragma once
#include "GameObject.h"
class GameObjectManager;
class PhysicsEngine;
using namespace std;
using namespace sf;
class Player:public GameObject
{
	
	public:
		Player(unsigned int id,std::string name , int health) :GameObject(id, name) {
		
		
		};
		int score;
		int _health;
		bool isAlive ;
		bool isfire;
		bool isHit;
		GameObject* Bullet;
		void fire(GameObjectManager* gm, PhysicsEngine* pE, Vector2f pos, Vector2f vel, float rot,Vector2f offset);

};