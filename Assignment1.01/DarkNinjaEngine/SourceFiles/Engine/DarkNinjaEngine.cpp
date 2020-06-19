//#include <stdafx.h>
#include "../../HeaderFiles/Engine/DarkNinjaEngine.h"
#include <cassert>
#include "../../HeaderFiles/Engine/RenderingSystem/RenderingSystem.h"
#include "../../HeaderFiles/Engine/PhysicsSystem/PhysicsSystem.h"
#include "../../HeaderFiles/Engine/Utility/Helper.h"
#include "../DarkNinjaEngine/JobSystem/JobSystem.h"


#include "../../../nlohmann/json.hpp"
#include "../../Shared/LoadFileToBuffer.h"
#include "HeaderFiles/Engine/Collider/Collider.h"

namespace Engine
{
	float Time::deltaSeconds = 0.0f;


	bool bQuit = false;

	

	void Init(sf::RenderWindow* I_Window)
	{
		_Window = I_Window;
		Engine::GameObjectThread("data\\GameObjectData.json");
		EntityManagerMain.Update();
		
	}

	void Engine::Run()
	{
		float dt = Engine::Time::CalculateTime();
	
		EntityManagerMain.Update();
		physics_system.Run(dt);
		collision_System.Run(_Window);
		rendering_system.Run(_Window);
	
		//rendering_system.Run();

	}

	void ShutDown()
	{
		EntityManagerMain.ShutDown();
		//EntityManagerMain.Update();
		//rendering_system.End();
		///*JobSystem::RequestShutdown();*/

	}

	void GameObjectThread(const char* I_Path)
	{
		//CreateGameObjects();
		void(*CreateGameObjectsPointer)();
		CreateGameObjectsPointer = CreateGameObjects;
		Path = I_Path;


		JobSystem::CreateQueue("Default", 1);
		{
			JobSystem::RunJob("GameObjectCreation", CreateGameObjectsPointer , "Default");
			do
			{
				PrintToOutput("Check for new gameobjects here!");
				Sleep(10);
			} while (JobSystem::HasJobs("Default"));
		}
		//JobSystem::RequestShutdown();
	}

#pragma region  GameObjectCreation
	void operator<<(vector2D& vec, nlohmann::json& json_obj)
	{
		assert(json_obj.is_array() && json_obj.size() == 2);

		vec.x = (json_obj[0]);
		vec.y = (json_obj[1]);
	}
	void operator<<(vector3D::vector3D& vec, nlohmann::json& json_obj)
	{
		assert(json_obj.is_array() && json_obj.size() == 3);

		vec.x = (json_obj[0]);
		vec.y = (json_obj[1]);
		vec.z = (json_obj[2]);
	}

	void CreateGameObjects()
	{
		
		using json = nlohmann::json;
		std::vector<uint8_t> PlayerData = Engine::LoadFileToBuffer(Path);
		json jsonGameObject = json::parse(PlayerData);

		for (int i = 0; i < jsonGameObject["List"].size(); i++)
		{
			std::string Name = jsonGameObject["List"][i]["name"];
			vector3D::vector3D location;
			location << jsonGameObject["List"][i]["position"];

			Entity* GameObject = new Entity(Name.c_str());

			GameObject->AttachComponent(new Position(location.x, location.y ,location.z));

			if (jsonGameObject["List"][i].contains("components"))
			{
				for (json::iterator it = jsonGameObject["List"][i]["components"].begin(); it != jsonGameObject["List"][i]["components"].end(); ++it)
				{
					if (it.key() == "renderdata")
					{
						std::string sprite = jsonGameObject["List"][i]["components"]["renderdata"]["sprite"];
						GameObject->AttachComponent(new SpriteSFML(sprite.c_str()));
					}
					if (it.key() == "rigidbody2D")
					{
						const float gravity = jsonGameObject["List"][i]["components"]["rigidbody2D"]["gravity"];
						const float mass = jsonGameObject["List"][i]["components"]["rigidbody2D"]["mass"];
						GameObject->AttachComponent(new RigidBody2D(mass));
						GameObject->GetComponent<RigidBody2D>()->setGravity(gravity);
				
					}
					if (it.key() == "boxcollider")
					{
						GameObject->AttachComponent(new BoxCollider());
					}
				}

			}
		}

	}

	void CreateGameObjects(const char* I_Path)
	{
		using json = nlohmann::json;
		std::vector<uint8_t> PlayerData = Engine::LoadFileToBuffer(I_Path);
		json jsonGameObject = json::parse(PlayerData);

		for (int i = 0; i < jsonGameObject["List"].size(); i++)
		{
			std::string Name = jsonGameObject["List"][i]["name"];
			vector3D::vector3D location;
			location << jsonGameObject["List"][i]["position"];

			Entity* GameObject = new Entity(Name.c_str());

			GameObject->AttachComponent(new Position(location.x, location.y, location.z));

			if (jsonGameObject["List"][i].contains("components"))
			{
				for (json::iterator it = jsonGameObject["List"][i]["components"].begin(); it != jsonGameObject["List"][i]["components"].end(); ++it)
				{
					if (it.key() == "renderdata")
					{
						std::string sprite = jsonGameObject["List"][i]["components"]["renderdata"]["sprite"];
						GameObject->AttachComponent(new SpriteSFML(sprite.c_str()));
					}
					if (it.key() == "rigidbody2D")
					{
						const float gravity = jsonGameObject["List"][i]["components"]["rigidbody2D"]["gravity"];
						const float mass = jsonGameObject["List"][i]["components"]["rigidbody2D"]["mass"];
						GameObject->AttachComponent(new RigidBody2D(mass));
						GameObject->GetComponent<RigidBody2D>()->setGravity(gravity);

					}
					if(it.key()=="boxcollider")
					{
						GameObject->AttachComponent(new BoxCollider());
					}
				}

			}
		}
	}


#pragma endregion
}
	
