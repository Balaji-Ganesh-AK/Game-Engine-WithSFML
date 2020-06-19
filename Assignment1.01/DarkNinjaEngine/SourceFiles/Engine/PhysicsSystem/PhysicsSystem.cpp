//#include "stdafx.h"
#include "../DarkNinjaEngine/HeaderFiles/Engine/PhysicsSystem/PhysicsSystem.h"
#include "../../../HeaderFiles/Engine/Utility/Time.h"
#include <HeaderFiles\Engine\Utility\Helper.h>

Engine::PhysicsSystem physics_system;



void Engine::PhysicsSystem::addEntity(SmartPointer<Entity> I_Entity)
{
	_SmartEntityListWithRigidBody2D.push_back(I_Entity);
}
void Engine::PhysicsSystem::Run(float dt)
{
	for (int i = 0; i < _SmartEntityListWithRigidBody2D.size(); i++)
	{
		if(_SmartEntityListWithRigidBody2D[i]->IsActive())
		{
			
		const vector3D::vector3D CurrentVelocity = _SmartEntityListWithRigidBody2D[i]->GetComponent<RigidBody2D>()->getVelocity();
		const vector3D::vector3D Drag = CurrentVelocity * -(_SmartEntityListWithRigidBody2D[i]->GetComponent<RigidBody2D>()->getKD());
		const vector3D::vector3D TotalForce = _SmartEntityListWithRigidBody2D[i]->GetComponent<RigidBody2D>()->getForce() + Drag;
		 vector3D::vector3D Acceleration = TotalForce / _SmartEntityListWithRigidBody2D[i]->GetComponent<RigidBody2D>()->getMass();
		Acceleration += Gravity;
		const vector3D::vector3D NextVelocity = CurrentVelocity + (Acceleration * dt);
		const vector3D::vector3D AverageVelocity = (CurrentVelocity + NextVelocity) / 2.0f;

		_SmartEntityListWithRigidBody2D[i]->GetComponent<RigidBody2D>()->setDrag(Drag);


		vector3D::vector3D currentPos = _SmartEntityListWithRigidBody2D[i]->GetComponent<Position>()->getPosition();
		currentPos = (currentPos + (AverageVelocity * dt));
		_SmartEntityListWithRigidBody2D[i]->GetComponent<Position>()->setPosition(currentPos);

		
		_SmartEntityListWithRigidBody2D[i]->GetComponent<RigidBody2D>()->setVelocity(NextVelocity);

		if(TotalForce > vector3D::vector3D::Zero())
		{
			
		_SmartEntityListWithRigidBody2D[i]->GetComponent<RigidBody2D>()->AddForce(TotalForce);
		}
		else
		{
			_SmartEntityListWithRigidBody2D[i]->GetComponent<RigidBody2D>()->AddForce(vector3D::vector3D::Zero());
		}
		

		}
#pragma region Old Physics
		//float time = Engine::Time::deltaSeconds;

		//if (_SmartEntityListWithRigidBody2D[i]->GetComponent<RigidBody2D>())
		//{
		//	
		//	//PrintToOutput("Physics game object name  force" << _SmartEntityListWithRigidBody2D[i]->GetComponent<RigidBody2D>()->getForce());
		//	vector3D::vector3D PrevPosition = _SmartEntityListWithRigidBody2D[i]->GetComponent<Position>()->getPrevPosition();
		//currentPos = _SmartEntityListWithRigidBody2D[i]->GetComponent<Position>()->getPosition();
		//_SmartEntityListWithRigidBody2D[i]->GetComponent<Position>()->setPrevPosition(currentPos);

		//vector3D::vector3D force = _SmartEntityListWithRigidBody2D[i]->GetComponent<RigidBody2D>()->getForce();
		//force.y -= _SmartEntityListWithRigidBody2D[i]->GetComponent<RigidBody2D>()->getGravity();

		//if(force.x >0)
		//{
		//	force.x -= 25.0;
		//}
		//	if(force.x < 0)
		//	{
		//		force.x += 25.0;
		//	}
		//	
		//	vector3D::vector3D a = force / _SmartEntityListWithRigidBody2D[i]->GetComponent<RigidBody2D>()->getMass();
		//currentPos = (currentPos*2.0 ) - PrevPosition + (a * time);
		//_SmartEntityListWithRigidBody2D[i]->GetComponent<Position>()->setPosition(currentPos);
		//
#pragma  endregion 



		
	}
}

void Engine::PhysicsSystem::Destroy(SmartPointer<Entity> i_entity)
{
	for (int i = 0; i < _SmartEntityListWithRigidBody2D.size(); i++)
	{
		if (_SmartEntityListWithRigidBody2D[i]->get_name() == i_entity->get_name())
		{
			_SmartEntityListWithRigidBody2D.erase(_SmartEntityListWithRigidBody2D.begin() + i);
		}
	}

}
