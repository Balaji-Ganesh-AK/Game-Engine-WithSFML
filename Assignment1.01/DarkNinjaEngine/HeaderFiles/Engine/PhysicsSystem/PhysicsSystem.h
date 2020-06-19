#pragma once
#include <vector>
#include "../DarkNinjaEngine/HeaderFiles/Engine/Components/Entity.h"

namespace Engine
{
	class PhysicsSystem
	{
	private:
		std::vector<SmartPointer<Entity>> _SmartEntityListWithRigidBody2D;

		/*vector3D::vector3D  currentPos, prePos;*/
		vector3D::vector3D Gravity = vector3D::vector3D(0,-0.0,0);
		float time;
		friend Position;
	public:
		
		
		void addEntity(SmartPointer<Entity> I_Entity);

		 void Run(float dt);
		void Destroy(SmartPointer<Entity> i_entity);

		inline void ShutDown()
		{
			
		}


	};

}

extern Engine::PhysicsSystem physics_system;

