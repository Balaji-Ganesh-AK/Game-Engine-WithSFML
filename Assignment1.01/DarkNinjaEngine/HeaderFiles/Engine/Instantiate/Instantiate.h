#pragma once
#include <SFML/Graphics.hpp>
#include "HeaderFiles/Engine/Components/Entity.h"

class Entity;
namespace Engine
{

	
	/*Entity* Instantiate(const char* Path);*/
	Entity* Instantiate(const char* Path);

	
	bool CheckCache(std::string I_TextureName);
	sf::Texture FindTextureFromCache(std::string I_TextureName);
	//Cache for storing texture data.
	//This improves performance 
	
	
}
