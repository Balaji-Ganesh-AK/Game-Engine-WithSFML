
#include "../DarkNinjaEngine/HeaderFiles/Engine/RenderingSystem/RenderingSystem.h"

#include "HeaderFiles/Engine/Utility/Helper.h"
Engine::RenderingSystem rendering_system ;



void Engine::RenderingSystem::addEntity(SmartPointer<Entity> I_Entity)
{
	_SmartEntityListWithRendering.push_back(I_Entity);
}




void Engine::RenderingSystem::Run(sf::RenderWindow* I_Window)
{

	

	for (int i = 0; i < _SmartEntityListWithRendering.size(); i++)
	{
		if (_SmartEntityListWithRendering[i]->IsActive())
		{
		
			vector3D::vector3D	Offset_test;
			
			if (_SmartEntityListWithRendering[i]->GetComponent<Position>())
			{
				Offset_test = _SmartEntityListWithRendering[i]->GetComponent<Position>()->getPosition();
				
				const float Pi = 3.14159265358979323846f;
				float RotationRadians = (_SmartEntityListWithRendering[i]->GetComponent<Position>()->getRotation() * Pi) / 180.0f;
				_SmartEntityListWithRendering[i]->GetComponent<SpriteSFML>()->sprite.setPosition(Offset_test.x, Offset_test.y);
				_SmartEntityListWithRendering[i]->GetComponent<SpriteSFML>()->sprite.setRotation(RotationRadians);

				
				I_Window->draw(_SmartEntityListWithRendering[i]->GetComponent<SpriteSFML>()->sprite);
				
			}
		}

	}
	
}

void Engine::RenderingSystem::End()
{
	PrintToOutput("Destory Sprites here!");
}

void Engine::RenderingSystem::Destroy(SmartPointer<Entity> i_entity)
{
	for (int i = 0; i < _SmartEntityListWithRendering.size(); i++)
	{
		if (_SmartEntityListWithRendering[i]->get_name()== i_entity->get_name())
		{
			_SmartEntityListWithRendering.erase(_SmartEntityListWithRendering.begin()+i);
		}
	}
	
}
