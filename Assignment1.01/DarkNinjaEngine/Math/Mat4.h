#pragma once
#include "Vec3.h"
#include "Vec4.h"


namespace Engine
{
	namespace Maths
	{
		struct mat4
		{
			union 
			{
				
				float elements[4*4];
				vector4D row[4];
			};
			mat4();
			mat4(float diagonal);
			mat4(const vector4D& row0 , const vector4D& row1, const vector4D& row2, const vector4D& row3);



			//Operations

			static mat4 identity();
			void Invert();
			mat4 Inverse();
			

			//Following Column major ordering
			mat4& multiply(const mat4& other);
			friend mat4 operator*(mat4 left, const mat4& right);
			mat4& operator*=(const mat4& other);

			
			

			//Camera Matrix
			static mat4 orthographic(float left, float right, float top, float bottom, float near, float far);
			static mat4 perspective(float fov, float aspectRation, float near, float far);

			//Translation Matrix
			static mat4 translation(const vector3D::vector3D &translation);
			static mat4 translation(const float x, const float y, const float z);
			static mat4 rotation(float angle, const vector3D::vector3D& axis);
			static mat4 CreateZRotation(float angle);
			static mat4 scale(const vector3D::vector3D& scale);
			static mat4 Transpose(const mat4& matrix);
			
			


			//Vector 4 Multiplication

			vector4D Mulitply(const vector4D & other);

			 
		};

		
	}
}
