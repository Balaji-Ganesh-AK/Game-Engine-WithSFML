#pragma once


#include "../DarkNinjaEngine/HeaderFiles/Engine/Components/Components.h"
#include <cassert>




#include "Math/Vec3.h"



class Entity
{
	friend class EntityManager;
public:
	Entity(const char* name);
	~Entity();

	void Start();
	void Update();
	void End();




	//Attach new component
	void AttachComponent(Components* NewComponent);

	//Fetch the attached componenets
	template<class T>
	T* GetComponent();

	
	//Gets the name of the Entity
	std::string get_name();

	void Destroy(float Time);
	void Destroy();
	
	//gets the ID of the actor
	int getID();

	void SetGameObjectTag(std::string I_Tag) { _Tag = I_Tag; };
	std::string GetGameObjectTag() { return _Tag; };

	bool IsActive() { return _IsActive; };
	void IsActive(bool IsActive) { _IsActive = IsActive; };
private:
	std::string _Tag = "";
	float _MarkedForDeath=false;
	float AliveTimer;
	bool _IsSelfDestructActivated = false;
	 float _SelfDestructingTimer;
	float _SelfDestructionStartTimer;
	
	//List of attached components.

	void AddGameObject();
	//Object is Active by default
	bool _IsActive = true;

	std::vector<Components* > _Components; //smartptr
	//TODO Write your own string function from 1.04
	std::string  _Name;
	int _max = 32;

};

template <class T>
T* Entity::GetComponent()
{
	int i = 0;
	T* ptr = nullptr;
	for (i = 0; i < _Components.size(); i++)
	{
		ptr = dynamic_cast<T*>(_Components.at(i));
		if (ptr)
			break;

	}
	return ptr;
}

//Transform class nu name change panidu
class Position : public Components
{
	
public:
	Position(const float x = 0.0, const float y = 0.0, const float z = 0.0);
	~Position();
	void  Update() override;

	
	void setPosition(const vector3D::vector3D& I_NewPosition);
	void setRotation(const float I_Rotation);
	void addRotation(const float I_Rotation);
	
	vector3D::vector3D getPosition() const;
	vector3D::vector3D getPrevPosition() const;
	float getRotation() const;
	
	void End() override;
	void setPrevPosition(const vector3D::vector3D& I_PrevPosition);



private:
	vector3D::vector3D _CurrentPosition;
	vector3D::vector3D  _NewPosition;
	vector3D::vector3D _PrevPosition;
	float _NewRotation = 0.0f;
	float _CurrentRotation = 0.0f;
};

#ifdef glib
//Sprite
class Sprite :public Components
{
public:
	Sprite(const char* path);
	void Update() override;
	GLib::Sprites::Sprite* sprite;
	void End() override;
	~Sprite();
	void SetExtent(vector3D::vector3D I_Extent);
	 vector3D::vector3D GetExtent()const { return _Extent; }

	
	
private:
	void* LoadFile(const char* i_pFilename, size_t& o_sizeFile);
	vector3D::vector3D _Extent = vector3D::vector3D::Zero();
	vector3D::vector3D _Center;
	GLib::Sprites::Sprite* CreateSprite(const char* i_pFilename);
};
#endif
class SpriteSFML :public Components
{
public:
	SpriteSFML(const char* path);
	SpriteSFML(sf::Texture I_Texture);
	void Update() override;
	void End() override;
	sf::Sprite sprite;
	
	vector3D::vector3D GetExtent()const { return _Extent; }
private:
	SmartPointer<Entity> _CurrentEntity; 
	sf::Texture texture;
	vector3D::vector3D _Extent = vector3D::vector3D::Zero();
	vector3D::vector3D _Center= vector3D::vector3D::Zero();
};





class RigidBody2D : public Components
{
public:
	RigidBody2D(float I_Mass);
	void Update() override;
	void End() override;
	void AddForce(const vector3D::vector3D I_Force);
	void setGravity(const float I_Gravity );
	void setMass(const float I_Mass);
	
	void setDrag(vector3D::vector3D I_Drag);
	void setAcclertation(vector3D::vector3D I_Acceleration);
	void setVelocity(vector3D::vector3D I_Velocity);
	vector3D::vector3D  getVelocity() { return _Velocity; }

	vector3D::vector3D  getDrag() { return _Drag; }
	float getMass();
	float getGravity();
	void setDrag(float I_Drag) { _Kd = I_Drag; };
	float getKD() { return _Kd; }
	
	vector3D::vector3D getForce();
private:
	SmartPointer<Entity> _CurrentEntity;
	float _Mass;
	float _Gravity = 0.0f;
	 
	 float _Kd = 0.4f;
	
	 vector3D::vector3D _Velocity = vector3D::vector3D::Zero();
	 vector3D::vector3D _MAcceleration = vector3D::vector3D::Zero();
	vector3D::vector3D _Drag  = vector3D::vector3D::Zero();
	 vector3D::vector3D _Force = vector3D::vector3D::Zero();
	
};



//AI class
class AI : public Components
{

public:
    void  Update() override;
	//Should Enable Random Movement?

	bool EnableRandomMovement = true;

private:
	//Generate Random movements for the AI
	void RandomMovement();

};

#pragma region Collider

//Simple box Collider
class BoxCollider: public Components
{
	//Struct storing the bounding boxes
	struct AABB
	{
		vector3D::vector3D m_Center;
		vector3D::vector3D m_Extents;
	};

	struct CollisionData
	{
		bool IsCollided;
		SmartPointer<Entity> Actor;
		SmartPointer<Entity> Other;
		
	};
public:
	BoxCollider();
	void End() override;
	void SetCollisionData(SmartPointer<Entity> _Actor, SmartPointer<Entity> _Other);
	Entity* GetOtherEntity();
	void SetCollision(bool _IsCollided);
	bool IsCollided();

private:
	SmartPointer<Entity> _CurrentEntity;
	AABB BoundingBox;
	CollisionData _CollisionData;
};
#pragma endregion 

