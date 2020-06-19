#pragma once
#include <iostream>

namespace  Engine
{
	struct  vector4D
	{
		float x, y, z, w;
		vector4D()=default;
		vector4D(float x, float y, float z, float w);


		static vector4D Down();
		static vector4D Zero();
		static vector4D Up();
		static vector4D Right();
		static vector4D Left();

		vector4D& Add(const vector4D& other);
		vector4D& Subtract(const vector4D& other);
		vector4D& Multiply(const vector4D& other);
		vector4D& Divide(const vector4D& other);

		vector4D& Add(float value);
		vector4D& Subtract(float value);
		vector4D& Multiply(float value);
		vector4D& Divide(float value);

		friend vector4D operator+(vector4D left, const vector4D& right);
		friend vector4D operator-(vector4D left, const vector4D& right);
		friend vector4D operator*(vector4D left, const vector4D& right);
		friend vector4D operator/(vector4D left, const vector4D& right);

		friend vector4D operator+(vector4D left, float value);
		friend vector4D operator-(vector4D left, float value);
		friend vector4D operator*(vector4D left, float value);
		friend vector4D operator/(vector4D left, float value);

		bool operator==(const vector4D& other) const;
		bool operator!=(const vector4D& other) const;
		bool operator>(const vector4D& other) const;
		bool operator<(const vector4D& other) const;
		bool operator>=(const vector4D& other) const;
		bool operator<=(const vector4D& other) const;

		vector4D operator+=(const vector4D& other);
		vector4D operator-=(const vector4D& other);
		vector4D operator*=(const vector4D& other);
		vector4D operator/=(const vector4D& other);

		vector4D operator+=(float value);
		vector4D operator-=(float value);
		vector4D operator*=(float value);
		vector4D operator/=(float value);


		float Magnitude() const;
		vector4D Normalize() const;
		float Dot(const vector4D& other)const;


		friend std::ostream& operator<<(std::ostream& stream, const vector4D& other);


	};


}
