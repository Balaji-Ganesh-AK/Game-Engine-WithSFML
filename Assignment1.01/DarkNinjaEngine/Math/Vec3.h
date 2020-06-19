#pragma once
#include <iostream>

namespace  vector3D
{
	struct  vector3D
	{
		float x, y ,z;
		vector3D();
		vector3D(float x, float y, float z);


		static vector3D Down();
		static vector3D Zero();
		static vector3D Up();
		static vector3D Right();
		static vector3D Left();

		vector3D& Add(const vector3D& other);
		vector3D& Subtract(const vector3D& other);
		vector3D& Multiply(const vector3D& other);
		vector3D& Divide(const vector3D& other);

		vector3D& Add(float value);
		vector3D& Subtract(float value);
		vector3D& Multiply(float value);
		vector3D& Divide(float value);

		friend vector3D operator+(vector3D left, const vector3D& right);
		friend vector3D operator-(vector3D left, const vector3D& right);
		friend vector3D operator*(vector3D left, const vector3D& right);
		friend vector3D operator/(vector3D left, const vector3D& right);

		friend vector3D operator+(vector3D left, float value);
		friend vector3D operator-(vector3D left, float value);
		friend vector3D operator*(vector3D left, float value);
		friend vector3D operator/(vector3D left, float value);

		bool operator==(const vector3D& other) const;
		bool operator!=(const vector3D& other) const;
		bool operator>(const vector3D& other) const;
		bool operator<(const vector3D& other) const;
		bool operator>=(const vector3D& other) const;
		bool operator<=(const vector3D& other) const;

		vector3D operator+=(const vector3D& other);
		vector3D operator-=(const vector3D& other);
		vector3D operator*=(const vector3D& other);
		vector3D operator/=(const vector3D& other);

		vector3D operator+=(float value);
		vector3D operator-=(float value);
		vector3D operator*=(float value);
		vector3D operator/=(float value);


		float Magnitude() const;
		vector3D Normalize() const;
		float Dot(const vector3D& other)const;


		friend std::ostream& operator<<(std::ostream& stream, const vector3D& other);


	};


}
