# include "Collider.h"
#include <algorithm>    // std::max
#define SimpleCollision

//#define SATCollision


Engine::Collider collision_System;
using namespace Engine;








float getMax(float a, float b, float c, float d)
{
	float max1 = std::max(a, b);
	float max2 = std::max(c, d);
	return (std::max(max1, max2));

}
float getMin(float a, float b, float c, float d)
{
	float min1 = std::min(a, b);
	float min2 = std::min(c, d);
	return (std::min(min1, min2));

}



bool check(vector2D  ATopLeftInWorld, vector2D  ATopRightInWorld, vector2D  ABottomRightInWorld, vector2D  ABottomLeftInWorld, vector2D  BTopLeftInWorld, vector2D  BTopRightInWorld, vector2D  BBottomRightInWorld, vector2D  BBottomLeftInWorld, vector2D axis)
{
	float dot11 = ATopLeftInWorld.Dot(axis.Normalize());
	float dot12 = ATopRightInWorld.Dot(axis.Normalize());
	float dot13 = ABottomRightInWorld.Dot(axis.Normalize());
	float dot14 = ABottomLeftInWorld.Dot(axis.Normalize());

	float maxA = getMax(dot11, dot12, dot13, dot14);
	float minA = getMin(dot11, dot12, dot13, dot14);
	//Dot Products B

	float dot21 = BTopLeftInWorld.Dot(axis.Normalize());
	float dot22 = BTopRightInWorld.Dot(axis.Normalize());
	float dot23 = BBottomRightInWorld.Dot(axis.Normalize());
	float dot24 = BBottomLeftInWorld.Dot(axis.Normalize());

	float maxB = getMax(dot21, dot22, dot23, dot24);
	float minB = getMin(dot21, dot22, dot23, dot24);


	PrintToOutput("Max A -->" << maxA << "\tMaxB-->" << maxB << "\tMin A-->" << minA << "\tMin B-->" << minB);
	if (maxA - minB > 0)
	{

		return true;
	}
	return false;
}





void Engine::Collider::addEntity(SmartPointer<Entity> I_Entity)
{

	//Check if the object has a position component
	if (I_Entity->GetComponent<Position>())
	{
		assert(I_Entity->GetComponent<Position>());
		_SmartEntityListWithBoxCollider.push_back(I_Entity);
	}
	else
	{
		PrintToOutput("Object is missing Position Component");
	}


}


void Engine::Collider::Run(sf::RenderWindow* I_Window)
{
	_Window = I_Window;
	RunBox();
}

void Engine::Collider::End()
{
}

void Collider::Destroy(SmartPointer<Entity> I_Entity)
{
	for (int i = 0; i < _SmartEntityListWithBoxCollider.size(); i++)
	{
		if (_SmartEntityListWithBoxCollider[i]->get_name() == I_Entity->get_name())
		{
			_SmartEntityListWithBoxCollider.erase(_SmartEntityListWithBoxCollider.begin() + i);
		}
	}
}

void Engine::Collider::FindCollision()
{
	const size_t count = _SmartEntityListWithBoxCollider.size();

	if (count > 1)
	{
		for (size_t i = 0; i < (count - 1); i++)
		{
			for (size_t j = 1; j < count; j++)
			{
				if (_SmartEntityListWithBoxCollider[i]->IsActive() && _SmartEntityListWithBoxCollider[j]->IsActive())
					Check2DBoxCollision(_SmartEntityListWithBoxCollider[i], _SmartEntityListWithBoxCollider[j]);
			}
		}
	}
}

void Engine::Collider::Check2DBoxCollision(SmartPointer<Entity> Collidable1,
	SmartPointer<Entity> Collidable2)
{
	if(Collidable1->get_name() == Collidable2->get_name())
	{
		
		return;
	}
#ifdef  SimpleCollision


	vector3D::vector3D S_Center1 = Collidable1->GetComponent<Position>()->getPosition();
	S_Center1.x += Collidable1->GetComponent<SpriteSFML>()->GetExtent().x;
	S_Center1.y += Collidable1->GetComponent<SpriteSFML>()->GetExtent().y;

	float width1 = Collidable1->GetComponent<SpriteSFML>()->GetExtent().x * 2;
	float height1 = Collidable1->GetComponent<SpriteSFML>()->GetExtent().y * 2;

	vector3D::vector3D S_Center2 = Collidable2->GetComponent<Position>()->getPosition();
	S_Center2.x += Collidable1->GetComponent<SpriteSFML>()->GetExtent().x;
	S_Center2.y += Collidable2->GetComponent<SpriteSFML>()->GetExtent().y;

	float width2 = Collidable2->GetComponent<SpriteSFML>()->GetExtent().x * 2;
	float height2 = Collidable2->GetComponent<SpriteSFML>()->GetExtent().y * 2;
	if (S_Center1.x < (S_Center2.x + width2) && (S_Center1.x + width1)> S_Center2.x&&
		S_Center1.y < (S_Center2.y+ height2) && (S_Center1.y + height1)> S_Center2.y
		) {
		//Collidable2->GetComponent<RigidBody2D>()->setVelocity(vector3D::vector3D::Zero());
		//Collidable1->GetComponent<RigidBody2D>()->setVelocity(vector3D::vector3D::Zero());
	}
	


#pragma  region ComplexCollision
	using namespace Maths;

	//For Collidable One
	mat4 MARot = mat4::CreateZRotation(Collidable1->GetComponent<Position>()->getRotation());
	mat4 MATranslation = mat4::translation(S_Center1);

	mat4 MAToWorld = MATranslation * MARot;
	mat4 MWorldToA = MAToWorld.Inverse();

	//For Collidable two
	mat4 MBRot = mat4::CreateZRotation(Collidable2->GetComponent<Position>()->getRotation());
	mat4 MBTranslation = mat4::translation(S_Center2);
	mat4 MBToWorld = MBTranslation * MBRot;
	mat4 MWorldToB = MBToWorld.Inverse();

	//Separation test variables

	//Obj A
	mat4 MAToB = MWorldToB * MAToWorld;
	vector4D ABBCenterInB = MAToB.Mulitply(vector4D(0, 0, 0, 1.0f));
	vector4D AExtentsXInB = MAToB.Mulitply(vector4D(Collidable1->GetComponent<SpriteSFML>()->GetExtent().x, 0, 0, 0));
	vector4D AExtentsYInB = MAToB.Mulitply(vector4D(0, Collidable1->GetComponent<SpriteSFML>()->GetExtent().y, 0, 0));

	float AProjectinOntoB_X = fabs(AExtentsXInB.x) + fabs(AExtentsYInB.x);
	float AProjectinOntoB_Y = fabs(AExtentsXInB.y) + fabs(AExtentsYInB.y);

	//Obj B
	mat4 MBToA = MWorldToA * MBToWorld;
	vector4D BBBCenterInA = MBToA.Mulitply(vector4D(0, 0, 0, 1.0f));
	vector4D BExtentsXInA = MBToA.Mulitply(vector4D(Collidable2->GetComponent<SpriteSFML>()->GetExtent().x, 0, 0, 0));
	vector4D BExtentsYInA = MBToA.Mulitply(vector4D(0, Collidable2->GetComponent<SpriteSFML>()->GetExtent().y, 0, 0));

	float BProjectinOntoA_X = fabs(BExtentsXInA.x) + fabs(BExtentsYInA.x);
	float BProjectinOntoA_Y = fabs(BExtentsXInA.y) + fabs(BExtentsYInA.y);

	//Object A xy
	bool IsSeparatedX = fabs(ABBCenterInB.x - 0) > (Collidable2->GetComponent<SpriteSFML>()->GetExtent().x + AProjectinOntoB_X);
	bool IsSeparatedY = fabs(ABBCenterInB.y - 0) > (Collidable2->GetComponent<SpriteSFML>()->GetExtent().y + AProjectinOntoB_Y);
	bool BIsSeparatedX = fabs(BBBCenterInA.x - 0) > (Collidable1->GetComponent<SpriteSFML>()->GetExtent().x + BProjectinOntoA_X);
	bool BIsSeparatedY = fabs(BBBCenterInA.y - 0) > (Collidable1->GetComponent<SpriteSFML>()->GetExtent().y + BProjectinOntoA_Y);

#ifdef _DEBUG
	vector2D outline = vector2D(Collidable1->GetComponent<SpriteSFML>()->sprite.getTexture()->getSize().x, Collidable1->GetComponent<SpriteSFML>()->sprite.getTexture()->getSize().y);
	sf::RectangleShape rectangle(sf::Vector2f(width1, height1));
	rectangle.setOrigin(0,0);
	vector3D::vector3D Offset_test = Collidable1->GetComponent<Position>()->getPosition();
	
	rectangle.setPosition(Offset_test.x, Offset_test.y);
	rectangle.setOutlineColor(sf::Color::Red);
	rectangle.setOutlineThickness(1);
	rectangle.setFillColor(sf::Color(255, 255, 255, 0));
	_Window->draw(rectangle);


	vector2D outline2 = vector2D(Collidable2->GetComponent<SpriteSFML>()->sprite.getTexture()->getSize().x, Collidable1->GetComponent<SpriteSFML>()->sprite.getTexture()->getSize().y);
	sf::RectangleShape rectangle2(sf::Vector2f(width2, height2));
	rectangle2.setOrigin(0, 0);
	vector3D::vector3D Offset_test2 = Collidable2->GetComponent<Position>()->getPosition();
	rectangle2.setPosition(Offset_test2.x, Offset_test2.y);
	rectangle2.setOutlineColor(sf::Color::Blue);
	rectangle2.setFillColor(sf::Color(255, 255, 255, 0));
	rectangle2.setOutlineThickness(1);
	_Window->draw(rectangle2);
#endif
	if (IsSeparatedY == false && IsSeparatedX == false && BIsSeparatedX == false && BIsSeparatedY == false)
	{
		//Collidable1->GetComponent<RigidBody2D>()->setVelocity(vector3D::vector3D::Zero());
 		//Collidable1->GetComponent<BoxCollider>()->SetCollisionData(Collidable1, Collidable2);
 		Collidable2->GetComponent<BoxCollider>()->SetCollisionData(Collidable2, Collidable1);
		

		
		
		
	}
	



#endif
#ifdef  SATCollisionWithMatrix


	vector3D::vector3D S_Center1 = Collidable1->GetComponent<Position>()->getPosition();
	S_Center1.y = Collidable1->GetComponent<Sprite>()->GetExtent().y;
	S_Center1.x = 0;
	float width1 = Collidable1->GetComponent<Sprite>()->GetExtent().x * 2;
	float height1 = Collidable1->GetComponent<Sprite>()->GetExtent().y * 2;

	vector3D::vector3D S_Center2 = Collidable2->GetComponent<Position>()->getPosition();
	S_Center2.y = Collidable2->GetComponent<Sprite>()->GetExtent().y;
	S_Center2.x = 0;
	float width2 = Collidable2->GetComponent<Sprite>()->GetExtent().x * 2;
	float height2 = Collidable2->GetComponent<Sprite>()->GetExtent().y * 2;

#pragma  region ComplexCollision
	using namespace Maths;

	//For Collidable One
	mat4 MARot = mat4::CreateZRotation(Collidable1->GetComponent<Position>()->getRotation());
	mat4 MATranslation = mat4::translation(Collidable1->GetComponent<Position>()->getPosition());

	mat4 ATopLeftInTrans = mat4::translation(S_Center1.x - Collidable1->GetComponent<Sprite>()->GetExtent().x, S_Center1.y + Collidable1->GetComponent<Sprite>()->GetExtent().y, 0);
	mat4 ATopRightInTrans = mat4::translation(S_Center1.x + Collidable1->GetComponent<Sprite>()->GetExtent().x, S_Center1.y + Collidable1->GetComponent<Sprite>()->GetExtent().y, 0);
	mat4 ABottomLeftInTrans = mat4::translation(S_Center1.x - Collidable1->GetComponent<Sprite>()->GetExtent().x, S_Center1.y - Collidable1->GetComponent<Sprite>()->GetExtent().y, 0);
	mat4 ABottomRightInTrans = mat4::translation(S_Center1.x + Collidable1->GetComponent<Sprite>()->GetExtent().x, S_Center1.y - Collidable1->GetComponent<Sprite>()->GetExtent().y, 0);

	PrintToOutput("A Points is Trans = " << ATopLeftInTrans.row[0] << "ATopRightInWorld " << ATopLeftInTrans.row[1] << "ABottomLeftInWorld " << ATopLeftInTrans.row[2] << "ABottomRightInWorld " << ATopLeftInTrans.row[3] << "\n");
	mat4 MAToWorld = MARot * MATranslation;
	mat4 MWorldToA = MAToWorld.Inverse();
	//Four points 
	mat4 ATopLeftInWorld = MARot * ATopLeftInTrans;
	mat4 ATopRightInWorld = MARot * ATopRightInTrans;
	mat4 ABottomLeftInWorld = MARot * ABottomLeftInTrans;
	mat4 ABottomRightInWorld = MARot * ABottomRightInTrans;

	PrintToOutput("A Points is ATopLeftInWorld = " << ATopLeftInWorld.row[0] << "ATopRightInWorld " << ATopLeftInWorld.row[1] << "ABottomLeftInWorld " << ATopLeftInWorld.row[2] << "ABottomRightInWorld " << ATopLeftInWorld.row[3] << "\n");
	//For Collidable two
	mat4 MBRot = mat4::CreateZRotation(Collidable2->GetComponent<Position>()->getRotation());
	mat4 MBTranslation = mat4::translation(Collidable2->GetComponent<Position>()->getPosition());
	mat4 MBToWorld = MBRot * MBTranslation;
	mat4 MWorldToB = MBToWorld.Inverse();

	//Separation test variables

	//Obj A
	mat4 MAToB = MWorldToB * MAToWorld;
	vector4D ABBCenterInB = MAToB.Mulitply(vector4D(S_Center1.x, S_Center1.y, 0, 1.0f));


	vector4D AExtentsXInB = MAToB.Mulitply(vector4D(Collidable1->GetComponent<Sprite>()->GetExtent().x, 0, 0, 0));
	vector4D AExtentsYInB = MAToB.Mulitply(vector4D(0, Collidable1->GetComponent<Sprite>()->GetExtent().y, 0, 0));

	//Four points 
	vector4D ATopLeftInB = MAToB.Mulitply(vector4D(S_Center1.x - Collidable1->GetComponent<Sprite>()->GetExtent().x, S_Center1.y + Collidable1->GetComponent<Sprite>()->GetExtent().y, 0, 1.0f));
	vector4D ATopRightInB = MAToB.Mulitply(vector4D(S_Center1.x + Collidable1->GetComponent<Sprite>()->GetExtent().x, S_Center1.y + Collidable1->GetComponent<Sprite>()->GetExtent().y, 0, 1.0f));
	vector4D ABottomLeftInB = MAToB.Mulitply(vector4D(S_Center1.x - Collidable1->GetComponent<Sprite>()->GetExtent().x, S_Center1.y - Collidable1->GetComponent<Sprite>()->GetExtent().y, 0, 1.0f));
	vector4D ABottomRightInB = MAToB.Mulitply(vector4D(S_Center1.x + Collidable1->GetComponent<Sprite>()->GetExtent().x, S_Center1.y - Collidable1->GetComponent<Sprite>()->GetExtent().y, 0, 1.0f));

	float AProjectinOntoB_X = fabs(AExtentsXInB.x) + fabs(AExtentsYInB.x);
	float AProjectinOntoB_Y = fabs(AExtentsXInB.y) + fabs(AExtentsYInB.y);

	//Obj B
	mat4 MBToA = MWorldToA * MBToWorld;
	vector4D BBBCenterInA = MBToA.Mulitply(vector4D(S_Center2.x, S_Center2.y, 0, 1.0f));
	vector4D BExtentsXInA = MBToA.Mulitply(vector4D(Collidable2->GetComponent<Sprite>()->GetExtent().x, 0, 0, 0));
	vector4D BExtentsYInA = MBToA.Mulitply(vector4D(0, Collidable2->GetComponent<Sprite>()->GetExtent().y, 0, 0));

	float BProjectinOntoA_X = fabs(BExtentsXInA.x) + fabs(BExtentsYInA.x);
	float BProjectinOntoA_Y = fabs(BExtentsXInA.y) + fabs(BExtentsYInA.y);

	//Object A xy
	bool IsSeparatedX = fabs(ABBCenterInB.x - S_Center2.x) > (Collidable2->GetComponent<Sprite>()->GetExtent().x + AProjectinOntoB_X);
	bool IsSeparatedY = fabs(ABBCenterInB.y - S_Center2.y) > (Collidable2->GetComponent<Sprite>()->GetExtent().y + AProjectinOntoB_Y);

	if (IsSeparatedY == false && IsSeparatedX == false)
	{
		//adad
		/*PrintToOutput("Collision Detected");*/
		/*Collidable1->GetComponent<RigidBody2D>()->AddForce(Collidable1->GetComponent<RigidBody2D>()->getForce() * -90000);*/
		/*Collidable1->GetComponent<RigidBody2D>()->setVelocity(Collidable1->GetComponent<RigidBody2D>()->getVelocity()*-1);*/
		Collidable1->GetComponent<RigidBody2D>()->setVelocity(vector3D::vector3D::Zero());
	}
	bool BIsSeparatedX = fabs(BBBCenterInA.x - S_Center1.x) > (Collidable1->GetComponent<Sprite>()->GetExtent().x + BProjectinOntoA_X);
	bool BIsSeparatedY = fabs(BBBCenterInA.y - S_Center1.y) > (Collidable1->GetComponent<Sprite>()->GetExtent().y + BProjectinOntoA_Y);
	if (BIsSeparatedY == false && BIsSeparatedX == false)
	{
		//adad
		PrintToOutput("Collision Detected");
		//Collidable2->GetComponent<RigidBody2D>()->setVelocity(vector3D::vector3D::Zero());
	}

	//PrintToOutput("A Points is ATopLeftInB = " << ATopLeftInB << "ATopRightInB " << ATopRightInB << "ABottomLeftInB " << ABottomLeftInB << "ABottomRightInB " << ABottomRightInB <<"\n");
#endif

#ifdef  SATCollision



	//Object A Calulations;
	vector3D::vector3D S_Center1 = Collidable1->GetComponent<Position>()->getPosition();
	S_Center1.y += Collidable1->GetComponent<Sprite>()->GetExtent().y;

	vector2D ACenterInWorld = vector2D(S_Center1.x, S_Center1.y);
	vector2D ATopLeftInWorld = vector2D(S_Center1.x - Collidable1->GetComponent<Sprite>()->GetExtent().x, S_Center1.y + Collidable1->GetComponent<Sprite>()->GetExtent().y);
	vector2D ATopRightInWorld = vector2D(S_Center1.x + Collidable1->GetComponent<Sprite>()->GetExtent().x, S_Center1.y + Collidable1->GetComponent<Sprite>()->GetExtent().y);
	vector2D ABottomLeftInWorld = vector2D(S_Center1.x - Collidable1->GetComponent<Sprite>()->GetExtent().x, S_Center1.y - Collidable1->GetComponent<Sprite>()->GetExtent().y);
	vector2D ABottomRightInWorld = vector2D(S_Center1.x + Collidable1->GetComponent<Sprite>()->GetExtent().x, S_Center1.y - Collidable1->GetComponent<Sprite>()->GetExtent().y);

	ACenterInWorld = GetRotationFromAngle(ACenterInWorld, Collidable1->GetComponent<Position>()->getRotation());
	ATopLeftInWorld = GetRotationFromAngle(ATopLeftInWorld, Collidable1->GetComponent<Position>()->getRotation());
	ATopRightInWorld = GetRotationFromAngle(ATopRightInWorld, Collidable1->GetComponent<Position>()->getRotation());
	ABottomLeftInWorld = GetRotationFromAngle(ABottomLeftInWorld, Collidable1->GetComponent<Position>()->getRotation());
	ABottomRightInWorld = GetRotationFromAngle(ABottomRightInWorld, Collidable1->GetComponent<Position>()->getRotation());


	//Object B Calulations;
	vector3D::vector3D S_Center2 = Collidable2->GetComponent<Position>()->getPosition();
	S_Center2.y += Collidable2->GetComponent<Sprite>()->GetExtent().y;

	vector2D BCenterInWorld = vector2D(S_Center2.x, S_Center2.y);
	vector2D BTopLeftInWorld = vector2D(S_Center2.x - Collidable2->GetComponent<Sprite>()->GetExtent().x, S_Center2.y + Collidable2->GetComponent<Sprite>()->GetExtent().y);
	vector2D BTopRightInWorld = vector2D(S_Center2.x + Collidable2->GetComponent<Sprite>()->GetExtent().x, S_Center2.y + Collidable2->GetComponent<Sprite>()->GetExtent().y);
	vector2D BBottomLeftInWorld = vector2D(S_Center2.x - Collidable2->GetComponent<Sprite>()->GetExtent().x, S_Center2.y - Collidable2->GetComponent<Sprite>()->GetExtent().y);
	vector2D BBottomRightInWorld = vector2D(S_Center2.x + Collidable2->GetComponent<Sprite>()->GetExtent().x, S_Center2.y - Collidable2->GetComponent<Sprite>()->GetExtent().y);

	BCenterInWorld = GetRotationFromAngle(BCenterInWorld, Collidable2->GetComponent<Position>()->getRotation());
	BTopLeftInWorld = GetRotationFromAngle(BTopLeftInWorld, Collidable2->GetComponent<Position>()->getRotation());
	BTopRightInWorld = GetRotationFromAngle(BTopRightInWorld, Collidable2->GetComponent<Position>()->getRotation());
	BBottomLeftInWorld = GetRotationFromAngle(BBottomLeftInWorld, Collidable2->GetComponent<Position>()->getRotation());
	BBottomRightInWorld = GetRotationFromAngle(BBottomRightInWorld, Collidable2->GetComponent<Position>()->getRotation());


	//Side 1 bottom
	vector2D RightAxis = getNormal(ABottomLeftInWorld, ABottomRightInWorld);
	vector2D LeftAxis = getNormal(ABottomRightInWorld, ABottomLeftInWorld);

	vector2D BottomAxis = getNormal(ATopLeftInWorld, ATopRightInWorld);


	bool Side1true = check(ATopLeftInWorld, ATopRightInWorld, ABottomLeftInWorld, ABottomRightInWorld, BTopLeftInWorld, BTopRightInWorld, BBottomLeftInWorld, BBottomRightInWorld, RightAxis);
	bool Side2true = check(ATopLeftInWorld, ATopRightInWorld, ABottomLeftInWorld, ABottomRightInWorld, BTopLeftInWorld, BTopRightInWorld, BBottomLeftInWorld, BBottomRightInWorld, BottomAxis);

	if (Side1true)
	{
		PrintToOutput("Testing " << RightAxis.Normalize() << "\n");

	}


	//Dot Products A 


	// PrintToOutput("Dot values dot11-----> " << dot21 << " \t dot12 " << dot22 << " \t dot13 " << dot23 << "\t dot14 " << dot24 << "\n");


#endif
}

void Engine::Collider::RunBox()
{
	FindCollision();
}

