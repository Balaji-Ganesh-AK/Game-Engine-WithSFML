//#include "stdafx.h"
#include "../../../HeaderFiles/Engine/Utility/Time.h"


float Engine::Time::CalculateTime()
{
	
	static long long PreviousTick;
	static float  PreviousTickMs = 0.0f;
	LARGE_INTEGER  _CurrentTimeTick, ElaspedTime;
	LARGE_INTEGER _Frequency;
	
	
	QueryPerformanceCounter(&_CurrentTimeTick);
	QueryPerformanceFrequency(&_Frequency);
		
	
	if (PreviousTickMs !=0.0f)
	{
		ElaspedTime.QuadPart =  _CurrentTimeTick.QuadPart- PreviousTick;
		ElaspedTime.QuadPart *= 100000;
		ElaspedTime.QuadPart /=_Frequency.QuadPart;
		PreviousTickMs =  static_cast<float> (ElaspedTime.QuadPart) / 1000;
		
	}
	else
		PreviousTickMs = 16.6;
	
	PreviousTick = _CurrentTimeTick.QuadPart;
#ifdef  _DEBUG
	//this is for having a constant time during debugging mode.
	if(PreviousTickMs>19.0f)
	{
		PreviousTickMs = 16.6f;
	}
#endif

	
	//float temp =
	deltaSeconds = PreviousTickMs / 1000;
	return PreviousTickMs;
}


