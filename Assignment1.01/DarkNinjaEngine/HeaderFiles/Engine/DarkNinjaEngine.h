#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctype.h>
#include <conio.h>

#include "Math/Vec3.h"
#include "../../HeaderFiles/Engine/Components/Components.h"
#include "../Engine/Input/EngineInput.h"
#include "Instantiate/Instantiate.h"
#include "../../HeaderFiles/Engine/Utility/time.h"
#include "Instantiate/Instantiate.h"
#include "../../HeaderFiles/Engine/Components/Entity.h"



namespace Engine
{
	
	void Init(sf::RenderWindow* I_Window);
	void Run();
	void ShutDown();
	void CreateGameObjects();
	void CreateGameObjects(const char* I_Path);
	void GameObjectThread(const char* I_Path);
	static sf::RenderWindow* _Window;
	static const char* Path;
}



