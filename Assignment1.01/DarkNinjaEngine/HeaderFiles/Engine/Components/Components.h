#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>


#include "../Math/Vector2.h"
#include <vector>
#include "../GLib/GLib.h"
#include "SmartPointer.h"


class Entity;

class EntityManager
{
	
public:
	void Update();
	//Delete all gameobjects
	void ShutDown();
	
	std::map<std::string, SmartPointer<Entity>> _SmartEntityList;// smartptr
	std::map<std::string, SmartPointer<Entity>> _SmartTempEntityList;


	//For Storing all the texture in this.
	std::map<std::string, sf::Texture > TextureCache;

	
	int _tag = 0;
	int emptyGameObjectCount = 0;
	
	//find game object by name
	Entity *FindGameObjectByTag(std::string Name);
	void AddToCache(std::string I_TextureName, sf::Texture I_Texture);
	

	void Destroy(Entity * I_Entity);
	void Destroy(Entity* I_Entity, float Time);
	
	//Total Game object count in the world
	int GetTotalGameObjectCount();


private :
	void CheckForMarkedObjects();
	void CheckForNewGameObject();
};

extern EntityManager EntityManagerMain;

class Components 
{
	
public:
	

	Components();
	virtual ~Components();

	//Life Time of the Component
	virtual void Start();
	virtual void Update();
	virtual void End();
};



