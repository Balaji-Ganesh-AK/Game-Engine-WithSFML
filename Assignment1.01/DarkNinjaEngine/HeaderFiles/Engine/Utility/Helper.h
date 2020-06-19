#pragma once
#include <cmath>
#include <sstream>

#define  PrintToOutput(value)\
{\
	std::ostringstream os_;\
	os_ << value;\
	OutputDebugStringA(os_.str().c_str());\
}\

inline bool AreAboutEqual(float I_lhs, float I_rhs, float epsilon=0.0001f)
{
	return fabs(I_lhs-I_rhs)<epsilon;
}

inline bool IsZero(float I_val)
{
	return AreAboutEqual(I_val, 0.00000001f);
}
inline bool NaNCheck(float I_val)
{
	return I_val == I_val ? false : true;
}