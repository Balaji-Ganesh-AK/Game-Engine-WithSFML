#include "Instantiate.h"
#include "../../../../nlohmann/json.hpp"
#include "Shared/LoadFileToBuffer.h"

namespace Engine
{

	static void operator<<(vector3D::vector3D& vec, nlohmann::json& json_obj)
	{
		assert(json_obj.is_array() && json_obj.size() == 3);

		vec.x = (json_obj[0]);
		vec.y = (json_obj[1]);
		vec.z = (json_obj[2]);
	}


	Entity* Instantiate(const char* Path)
	{
		Entity* GameObject = nullptr;
		using json = nlohmann::json;
		std::vector<uint8_t> PlayerData = Engine::LoadFileToBuffer(Path);
		json jsonGameObject = json::parse(PlayerData);
		for (int i = 0; i < jsonGameObject["List"].size(); i++)
		{
			std::string Name = jsonGameObject["List"][i]["name"];
			vector3D::vector3D location;
			location << jsonGameObject["List"][i]["position"];

			GameObject = new Entity(Name.c_str());

			GameObject->AttachComponent(new Position(location.x, location.y, location.z));

			if (jsonGameObject["List"][i].contains("components"))
			{
				for (json::iterator it = jsonGameObject["List"][i]["components"].begin(); it != jsonGameObject["List"][i]["components"].end(); ++it)
				{
					if (it.key() == "renderdata")
					{
						std::string sprite = jsonGameObject["List"][i]["components"]["renderdata"]["sprite"];
					
						if(CheckCache(sprite))
						{
							GameObject->AttachComponent(new SpriteSFML(FindTextureFromCache(sprite)));
						}
						else
						{
						
							GameObject->AttachComponent(new SpriteSFML(sprite.c_str()));
						}
						
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
		return GameObject;
	}

	

	bool CheckCache(std::string I_TextureName)
	{

		for (auto it = EntityManagerMain.TextureCache.begin(); it != EntityManagerMain.TextureCache.end(); ++it)
		{

			std::string test = it->first;
			if (I_TextureName.compare(test) == 0)
			{
				//ReturnGameObject = it->second;

				return true;

			}

		}
		return false;
	}

	sf::Texture FindTextureFromCache(std::string I_TextureName)
	{

		sf::Texture texture;
		for (auto it = EntityManagerMain.TextureCache.begin(); it != EntityManagerMain.TextureCache.end(); ++it)
		{

			std::string test = it->first;
			if (I_TextureName.compare(test) == 0)
			{
				texture = it->second;

				return texture;

			}

		}

		return texture;
	}

}