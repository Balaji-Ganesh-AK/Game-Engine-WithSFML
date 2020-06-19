#pragma once
#include <iostream>

namespace  Engine
{
	struct  vector2D
	{
		float x, y;
		vector2D();
		vector2D(float x, float y);


		static vector2D Down();
		static vector2D Zero();
		static vector2D Up();
		static vector2D Right();
		static vector2D Left();
		
		vector2D& Add(const vector2D &other);
		vector2D& Subtract(const vector2D &other);
		vector2D& Multiply(const vector2D &other);
		vector2D& Divide(const vector2D &other);

		vector2D& Add(float value);
		vector2D& Subtract(float value);
		vector2D& Multiply(float value);
		vector2D& Divide(float value);

		friend vector2D operator+(vector2D left, const vector2D& right);
		friend vector2D operator-(vector2D left, const vector2D& right);
		friend vector2D operator*(vector2D left, const vector2D& right);
		friend vector2D operator/(vector2D left, const vector2D& right);

		friend vector2D operator+(vector2D left, float value);
		friend vector2D operator-(vector2D left, float value);
		friend vector2D operator*(vector2D left, float value);
		friend vector2D operator/(vector2D left, float value);

		bool operator==(const vector2D&other ) const ;
		bool operator!=(const vector2D& other) const;
		bool operator>(const vector2D& other) const;
		bool operator<(const vector2D& other) const;
		bool operator>=(const vector2D& other) const;
		bool operator<=(const vector2D& other) const;

		vector2D operator+=(const vector2D &other);
		vector2D operator-=(const vector2D& other);
		vector2D operator*=(const vector2D& other);
		vector2D operator/=(const vector2D& other);

		vector2D operator+=(float value);
		vector2D operator-=(float value);
		vector2D operator*=(float value);
		vector2D operator/=(float value);


		float Magnitude() const;
		vector2D Normalize() const;
		float Dot(const vector2D &other)const;

		
		friend std::ostream& operator<<(std::ostream& stream, const vector2D& other);

		
	};


}
