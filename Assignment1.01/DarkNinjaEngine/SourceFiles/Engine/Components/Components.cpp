//#include "stdafx.h"
#include "../DarkNinjaEngine/HeaderFiles/Engine/Components/Components.h"
#include <cassert>
#include "../../../HeaderFiles/Engine/Components/Entity.h"
#include "../../../HeaderFiles/Engine/RenderingSystem/RenderingSystem.h"
#include "../../../HeaderFiles/Engine/Utility/Time.h"
#include "../DarkNinjaEngine/HeaderFiles/Engine/PhysicsSystem/PhysicsSystem.h"
#include "../DarkNinjaEngine/HeaderFiles/Engine/Utility/Helper.h"
#include "Syncronization/Mutex.h"
#include "Syncronization/ScopeLock.h"
#include "HeaderFiles/Engine/Collider/Collider.h"


Entity *CurrentEntity = nullptr;
SmartPointer<Entity> current_smart_pointer(CurrentEntity);
EntityManager EntityManagerMain;
Engine::Mutex _Mutex;
sf::Clock GameTimer;
void EntityManager::Update()
{

	CheckForNewGameObject();
	CheckForMarkedObjects();
	for (auto it = EntityManagerMain._SmartEntityList.begin(); it != EntityManagerMain._SmartEntityList.end(); ++it)
	{
		
		current_smart_pointer = it->second;
		it->second->Update();

	}
	
}

void EntityManager::ShutDown()
{
	//Delete all the stored cache texture;
	TextureCache.clear();
	for (auto it = EntityManagerMain._SmartEntityList.begin(); it != EntityManagerMain._SmartEntityList.end(); ++it)
	{

		current_smart_pointer = it->second;
		it->second->Destroy();

	}
	CheckForMarkedObjects();
}


Entity* EntityManager::FindGameObjectByTag(std::string Name)
{
	SmartPointer<Entity> ReturnGameObject;

	for (auto it = EntityManagerMain._SmartEntityList.begin(); it != EntityManagerMain._SmartEntityList.end(); ++it)
	{

		std::string test = it->second->get_name();
				if (Name.compare(test)==0)
				{
					//ReturnGameObject = it->second;
					
					return it->second.GetData();
					
				}
		
			}
			return nullptr;
}

void EntityManager::AddToCache(std::string I_TextureName, sf::Texture I_Texture)
{
	EntityManagerMain.TextureCache.insert(std::pair<std::string, sf::Texture>(I_TextureName, I_Texture));
}

void EntityManager::Destroy(Entity * i_entity)
{
	for (auto it = EntityManagerMain._SmartEntityList.begin(); it != EntityManagerMain._SmartEntityList.end(); ++it)
	{

		std::string test = it->second->get_name();
		if (i_entity->get_name().compare(test) == 0)
		{
			//ReturnGameObject = it->second;
			auto todelete = _SmartEntityList.find(test);
			todelete->second->End();
			_SmartEntityList.erase(todelete);
			PrintToOutput("deleted");
			break;

		}

	}
}

void EntityManager::Destroy(Entity* I_Entity, float Time)
{
	sf::Clock clock;
	static float current_time = clock.getElapsedTime().asSeconds();
	 
	for (auto it = EntityManagerMain._SmartEntityList.begin(); it != EntityManagerMain._SmartEntityList.end(); ++it)
	{

		std::string test = it->second->get_name();
		if (I_Entity->get_name().compare(test) == 0)
		{
			//ReturnGameObject = it->second;
			auto todelete = _SmartEntityList.find(test);
			todelete->second->End();
			_SmartEntityList.erase(todelete);
			PrintToOutput("deleted");
			break;

		}

	}
}

int EntityManager::GetTotalGameObjectCount()
{
	return EntityManagerMain._SmartEntityList.size();
}



void EntityManager::CheckForMarkedObjects()
{
	std::vector<Entity* > ListOFGameObjectToDelete;
	for (auto it = EntityManagerMain._SmartEntityList.begin(); it != EntityManagerMain._SmartEntityList.end(); ++it)
	{
		if(it->second->_MarkedForDeath)
		{
			ListOFGameObjectToDelete.push_back(it->second.GetData());
		}
	}
	for (int i =0 ; i < ListOFGameObjectToDelete.size();i++)
	{
		Destroy(ListOFGameObjectToDelete[i]);
	}
	ListOFGameObjectToDelete.clear();
	
	
}

void EntityManager::CheckForNewGameObject()
{
	if(_SmartTempEntityList.size()>0)
	{
		_SmartEntityList.insert(_SmartTempEntityList.begin(), _SmartTempEntityList.end());
		_SmartTempEntityList.clear();
	}
}

Components::Components()
{
}




Components::~Components()
{
}

void Components::Start()
{
}

void Components::Update()
{
}

void Components::End()
{
}




Entity::Entity(const char* name) : _Name(name ? _strdup(name) : nullptr)
{
	this->AliveTimer = GameTimer.getElapsedTime().asSeconds();

	if (_Name == "")
	{
		EntityManagerMain.emptyGameObjectCount++;
		_Name = "EmptyGameObject ";
		_Name += std::to_string(EntityManagerMain.emptyGameObjectCount);
	}
	
	AddGameObject();
	
	CurrentEntity = this;
	current_smart_pointer = nullptr;
	current_smart_pointer = SmartPointer<Entity>(CurrentEntity);


}

Entity::~Entity()
{
}


void Entity::Start()
{
}

void Entity::Update()
{

	if(_IsSelfDestructActivated)
	{
		if(GameTimer.getElapsedTime().asSeconds() > _SelfDestructionStartTimer+_SelfDestructingTimer)
		{
			_MarkedForDeath = true;
			_IsActive = false;
		
		}
	}
	if (_IsActive == true)
	{

		for (int i = 0; i < _Components.size(); i++)
		{
			_Components[i]->Update();
			
		}
	}
}

void Entity::End()
{
	for (int i = 0; i < _Components.size(); i++)
	{
		_Components[i]->End();
	}
}

std::string Entity::get_name()
{
	return _Name;
}

void Entity::Destroy(float Time)
{
	_SelfDestructingTimer = Time;
	_SelfDestructionStartTimer = GameTimer.getElapsedTime().asSeconds();
	_IsSelfDestructActivated = true;
}

void Entity::Destroy()
{

	_MarkedForDeath = true;

	//EntityManagerMain.Destroy(this);
}

int Entity::getID()
{

	return 0;
}

void Entity::AddGameObject()
{
	//EntityManagerMain._SmartEntityList.insert({ this->get_name(),SmartPointer<Entity>(this) });
	Engine::ScopeLock scope(_Mutex);
	EntityManagerMain._SmartTempEntityList.insert({ this->get_name(),SmartPointer<Entity>(this) });
}

// Attach Component
void Entity::AttachComponent(Components* NewComponent)
{
	if (NewComponent)
	{
		_Components.push_back(NewComponent);
	}
}


//Position Component
Position::Position(const float x, const float y, const float z) {

	_CurrentPosition.x = x;
	_CurrentPosition.y = y;
	_CurrentPosition.z = z;
	_CurrentRotation = z;
	_NewPosition = _CurrentPosition;
	_PrevPosition = _CurrentPosition;
	_NewRotation = _CurrentRotation;
}

Position::~Position()
{
	PrintToOutput("Position Destoryed");
}

void Position::Update()
{
	_CurrentPosition = _NewPosition;
	_CurrentRotation = _NewRotation;
}

void Position::setPosition(const vector3D::vector3D& I_NewPosition)
{
	_NewPosition = I_NewPosition;
	
}

void Position::setRotation(const float I_Rotation)
{
	_NewRotation = I_Rotation;
}

void Position::addRotation(const float I_Rotation)
{
	_NewRotation += I_Rotation;
}


vector3D::vector3D Position::getPosition() const
{
	return _CurrentPosition;
}
vector3D::vector3D Position::getPrevPosition() const
{
	return _PrevPosition;
}

float Position::getRotation() const
{
	return _CurrentRotation;
}

void Position::End()
{
	 
}

void Position::setPrevPosition(const vector3D::vector3D& I_PrevPosition)
{
	_PrevPosition = I_PrevPosition;
}

#ifdef glib
//Sprites
Sprite::Sprite(const char* path)
{
	//path = "data\\GoodGuy.dds";
	sprite = CreateSprite(path);
	rendering_system.addEntity(current_smart_pointer);
}

void Sprite::Update()
{
	
}

void Sprite::End()
{
	current_smart_pointer = nullptr;
	GLib::Sprites::Release(sprite);
	
}


Sprite::~Sprite()
{
	GLib::Sprites::Release(sprite);
}

void Sprite::SetExtent(vector3D::vector3D I_Extent)
{
	_Extent = I_Extent;
}



void* Sprite::LoadFile(const char* i_pFilename, size_t& o_sizeFile)
{
	assert(i_pFilename != NULL);

	FILE* pFile = NULL;

	errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
	if (fopenError != 0)
		return NULL;

	assert(pFile != NULL);

	int FileIOError = fseek(pFile, 0, SEEK_END);
	assert(FileIOError == 0);

	long FileSize = ftell(pFile);
	assert(FileSize >= 0);

	FileIOError = fseek(pFile, 0, SEEK_SET);
	assert(FileIOError == 0);

	uint8_t* pBuffer = new uint8_t[FileSize];
	assert(pBuffer);

	size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
	assert(FileRead == FileSize);

	fclose(pFile);

	o_sizeFile = FileSize;

	return pBuffer;
}

GLib::Sprites::Sprite* Sprite::CreateSprite(const char* i_pFilename)
{
	assert(i_pFilename);

	size_t sizeTextureFile = 0;

	// Load the source file (texture data)
	void* pTextureFile = LoadFile(i_pFilename, sizeTextureFile);

	// Ask GLib to create a texture out of the data (assuming it was loaded successfully)
	GLib::Texture* pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;

	// exit if something didn't work
	// probably need some debug logging in here!!!!
	if (pTextureFile)
		delete[] pTextureFile;

	if (pTexture == nullptr)
		return NULL;

	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int depth = 0;

	// Get the dimensions of the texture. We'll use this to determine how big it is on screen
	bool result = GLib::GetDimensions(pTexture, width, height, depth);
	assert(result == true);
	assert((width > 0) && (height > 0));
	_Extent.x = float(width) / 2;
	_Extent.y = float(height) / 2;
	_Extent.z = float(depth) / 2;

	// Define the sprite edges
	GLib::Sprites::SpriteEdges	Edges = { -float(width / 2.0f), float(height), float(width / 2.0f), 0.0f };
	GLib::Sprites::SpriteUVs	UVs = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } };
	GLib::RGBA							Color = { 255, 255, 255, 255 };

	// Create the sprite
	GLib::Sprites::Sprite* pSprite = GLib::Sprites::CreateSprite(Edges, 0.1f, Color, UVs);
	if (pSprite == nullptr)
	{
		GLib::Release(pTexture);
		return nullptr;
	}

	// Bind the texture to sprite
	GLib::Sprites::SetTexture(*pSprite, *pTexture);

	return pSprite;
}
#endif

SpriteSFML::SpriteSFML(const char* path)
{
	if (!texture.loadFromFile(path))
	{
		std::cout << "load failed " << std::endl;
		system("pause");
	}
	else
	{
		
		EntityManagerMain.AddToCache(path, texture);
		sprite.setTexture(texture);
		_Extent.x= static_cast<float>(sprite.getTexture()->getSize().x) / 2;
		_Extent.y= static_cast<float>(sprite.getTexture()->getSize().y )/ 2;
	
		PrintToOutput("load Success "<< _Extent<<"\n");
	}
	rendering_system.addEntity(current_smart_pointer);
	_CurrentEntity = current_smart_pointer;
}

SpriteSFML::SpriteSFML(sf::Texture I_Texture)
{
	texture = I_Texture;
	sprite.setTexture(texture);
	_Extent.x = static_cast<float>(sprite.getTexture()->getSize().x) / 2;
	_Extent.y = static_cast<float>(sprite.getTexture()->getSize().y) / 2;
	rendering_system.addEntity(current_smart_pointer);
	_CurrentEntity = current_smart_pointer;
}

void SpriteSFML::Update()
{
	
}

void SpriteSFML::End()
{
	rendering_system.Destroy(_CurrentEntity);
}

//Rigid Body
RigidBody2D::RigidBody2D(float I_Mass):
_Mass(I_Mass)
{
	physics_system.addEntity(current_smart_pointer);
	_CurrentEntity = current_smart_pointer;
}

void RigidBody2D::Update()
{

}

void RigidBody2D::End()
{
	physics_system.Destroy(_CurrentEntity);
}

void RigidBody2D::AddForce(const vector3D::vector3D I_Force)
{
	_Force =  I_Force;
}

void RigidBody2D::setGravity(const float I_Gravity)
{
	_Gravity=(I_Gravity);
}

void RigidBody2D::setMass(const float I_Mass)
{
	_Mass= (I_Mass);
}

void RigidBody2D::setDrag(vector3D::vector3D I_Drag)
{
	_Drag = I_Drag;
}

void RigidBody2D::setAcclertation(vector3D::vector3D I_Acceleration)
{
	_MAcceleration = I_Acceleration;
}

void RigidBody2D::setVelocity(vector3D::vector3D I_Velocity)
{
	_Velocity = I_Velocity;
}


float RigidBody2D::getMass()
{
	return _Mass;
}

float RigidBody2D::getGravity()
{
	return _Gravity;
}

vector3D::vector3D RigidBody2D::getForce()
{
	return _Force;
}

//AI Component 
void AI::Update()
{
	RandomMovement();
}

// AI Movements;
void AI::RandomMovement()
{

		if(CurrentEntity->GetComponent<Position>() && EnableRandomMovement==true)
		{
			
			vector3D::vector3D NewPosition = CurrentEntity->GetComponent<Position>()->getPosition();
			if(IsZero(NewPosition.y/2)&& IsZero(NewPosition.x / 2))
			{
				NewPosition.y += 1;
			}
	
			else if (!IsZero(NewPosition.x / 2)&& !IsZero(NewPosition.y / 2))
			{
				NewPosition.x -= .1;
			}
			else
			{
				NewPosition.y -= 1;
			}
			
			CurrentEntity->GetComponent<Position>()->setPosition(NewPosition);
		}
}


//Box Collider
BoxCollider::BoxCollider()
{
	collision_System.addEntity(current_smart_pointer);
	_CurrentEntity = current_smart_pointer;
}

void BoxCollider::End()
{
	collision_System.Destroy(_CurrentEntity);
}

void BoxCollider::SetCollisionData(SmartPointer<Entity> _Actor, SmartPointer<Entity> _Other)
{
	_CollisionData.IsCollided = true;
	_CollisionData.Actor = _Actor;
	_CollisionData.Other = _Other;
	
}

Entity* BoxCollider::GetOtherEntity()
{
	return _CollisionData.Other.GetData();
}

void BoxCollider::SetCollision(bool _IsCollided)
{
	_CollisionData.IsCollided = _IsCollided;
	if(!_IsCollided)
	{
		_CollisionData.Actor = nullptr;
		_CollisionData.Other = nullptr;
	}
	
}

bool BoxCollider::IsCollided()
{
	return _CollisionData.IsCollided;
}




