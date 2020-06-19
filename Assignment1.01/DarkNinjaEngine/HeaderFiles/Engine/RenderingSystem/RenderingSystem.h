#pragma once

#include <vector>
#include "../DarkNinjaEngine/HeaderFiles/Engine/Components/Entity.h"



namespace Engine
{
	
	class RenderingSystem
	{
		private:
	
		std::vector<SmartPointer<Entity>> _SmartEntityListWithRendering;// smartpointer
		public:
	
		void addEntity(SmartPointer<Entity> I_Entity);

		
		void Run(sf::RenderWindow *I_Window);
		void End();
		void Destroy(SmartPointer<Entity> i_entity);

		
	};
	 
}

extern Engine::RenderingSystem rendering_system;