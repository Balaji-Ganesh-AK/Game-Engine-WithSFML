#pragma once
#include <vector>
#include "../DarkNinjaEngine/HeaderFiles/Engine/Components/Entity.h"


namespace Engine
{
	class AISystem
	{
	private:
		std::vector<Entity*> _EntityListWithAI;
		Entity* _PPplayer;
		
	public:
		void AddEntity(Entity * I_Entity);
		void FollowPlayer(Entity *I_Player);
		void Run();
	};
}