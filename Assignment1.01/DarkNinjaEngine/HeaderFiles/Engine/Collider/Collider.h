#pragma once
#include "Math/Vec3.h"
#include <vector>
#include "../DarkNinjaEngine/HeaderFiles/Engine/Components/Entity.h"
#include "../../../HeaderFiles/Engine/Utility/Time.h"
#include <HeaderFiles\Engine\Utility\Helper.h>
#include "Math/Mat4.h"
namespace Engine
{
	class Collider
	{
		//Vector for storing game objects with box collision
		std::vector<SmartPointer<Entity>> _SmartEntityListWithBoxCollider;
		
		//Start the box Collider
		void RunBox();

		
		
		public:

		//Adds a game object to the vector
		void addEntity(SmartPointer<Entity> I_Entity);


		
		//Starts the collision system
		void Run(sf::RenderWindow* I_Window);
		//Call this to end the collision system
		void End();
		void Destroy(SmartPointer<Entity> I_Entity);

		//used for storing two objects which are colliding
		struct CollisionPair
		{
			WeakPointer<Entity> m_GameObject1;
			WeakPointer<Entity> m_GameObject2;
			//Collision time
			float				m_CollisionTime;
		};

		void FindCollision();
		void Check2DBoxCollision( SmartPointer<Entity> Collideable1,  SmartPointer<Entity> Collideable2);


	private:
		sf::RenderWindow* _Window;
	};
}
extern Engine::Collider collision_System;