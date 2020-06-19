//#include "stdafx.h"
#include "../DarkNinjaEngine/HeaderFiles/Engine/AISystem/AISystem.h"

void Engine::AISystem::AddEntity(Entity* I_Entity)
{
	_EntityListWithAI.push_back(I_Entity);
}

void Engine::AISystem::FollowPlayer(Entity* I_Player)
{
	_PPplayer = I_Player;
}

void Engine::AISystem::Run()
{
	
}
