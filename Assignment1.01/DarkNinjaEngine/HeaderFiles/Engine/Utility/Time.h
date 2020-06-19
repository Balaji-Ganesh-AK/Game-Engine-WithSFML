#pragma once

#include "windows.h"
#include  "profileapi.h"

namespace Engine
{
	class Time
	{
	private:
		
	public:
		static float CalculateTime();
		static float GetDeltaTime();
		static float deltaSeconds;
	};
	
}