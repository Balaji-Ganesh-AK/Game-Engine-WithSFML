//#include "stdafx.h"
#include "../DarkNinjaEngine/HeaderFiles/Engine/Math/Vector2.h"


namespace Engine
{
	vector2D::vector2D():x(0.0f),y(0.0f)
	{
	}

	vector2D::vector2D(float x, float y):x(x),y(y)
	{
	}

	vector2D vector2D::Down()
	{
		vector2D temp;
		temp.x = 0;
		temp.y = -1;
		return temp;
	}

	vector2D vector2D::Zero()
	{
		vector2D temp;
		temp.x = 0;
		temp.y = 0;
		return temp;
	}

	vector2D vector2D::Up()
	{
		vector2D temp;
		temp.x = 0;
		temp.y = 1;
		return temp;
	}

	vector2D vector2D::Right()
	{
		vector2D temp;
		temp.x = 1;
		temp.y = 0;
		return temp;
	}

	vector2D vector2D::Left()
	{
		vector2D temp;
		temp.x = -1;
		temp.y = 0;
		return temp;
	}

	vector2D& vector2D::Add(const vector2D& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	vector2D& vector2D::Subtract(const vector2D& other)
	{
		y -= other.y;
		x -= other.x;
		return *this;
	}

	vector2D& vector2D::Multiply(const vector2D& other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}

	vector2D& vector2D::Divide(const vector2D& other)
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}

	vector2D& vector2D::Add(float value)
	{
		x += value;
		y += value;
		return *this;
	}

	vector2D& vector2D::Subtract(float value)
	{
		x -= value;
		y -= value;
		return *this;
	}

	vector2D& vector2D::Multiply(float value)
	{
		x *= value;
		y *= value;
		return *this;
	}

	vector2D& vector2D::Divide(float value)
	{
		x /= value;
		y /= value;
		return *this;
	}

	bool vector2D::operator==(const vector2D& other) const
	{
		return x == other.x && y == other.y;
	}

	bool vector2D::operator!=(const vector2D& other) const
	{
		return !(*this==other);
	}

	bool vector2D::operator>(const vector2D& other) const
	{
		return x > other.x && y > other.y;
	}

	bool vector2D::operator<(const vector2D& other) const
	{
		return x < other.x&& y < other.y;
	}

	bool vector2D::operator>=(const vector2D& other) const
	{
		return x >= other.x&& y >= other.y;
	}

	bool vector2D::operator<=(const vector2D& other) const
	{
		return x <= other.x&& y <= other.y;
	}

	vector2D vector2D::operator+=(const vector2D& other)
	{
		return Add(other);
	}

	vector2D vector2D::operator-=(const vector2D& other)
	{
		return Subtract(other);
	}

	vector2D vector2D::operator*=(const vector2D& other)
	{
		return Multiply(other);
	}

	vector2D vector2D::operator/=(const vector2D& other)
	{
		return Divide(other);
	}

	vector2D vector2D::operator+=(float value)
	{
		return Add(value);
	}

	vector2D vector2D::operator-=(float value)
	{
		return Subtract(value);
	}

	vector2D vector2D::operator*=(float value)
	{
		return Multiply(value);
	}

	vector2D vector2D::operator/=(float value)
	{
		return Divide(value);
	}

	float vector2D::Magnitude() const
	{
		return sqrt(x *x + y*y);
	}

	vector2D vector2D::Normalize() const
	{
		float temp = Magnitude();
		return vector2D(x/temp, y/temp);
	}

	float vector2D::Dot(const vector2D& other) const
	{
		return x * other.x + y * other.y;
	}

	vector2D operator+(vector2D left, const vector2D& right)
	{
		return left.Add(right);
	}

	vector2D operator-(vector2D left, const vector2D& right)
	{
		return left.Subtract(right);
	}

	vector2D operator*(vector2D left, const vector2D& right)
	{
		return left.Multiply(right);
	}

	vector2D operator/(vector2D left, const vector2D& right)
	{
		return left.Divide(right);
	}

	vector2D operator+(vector2D left, float value)
	{
		return  vector2D(left.x +value, left.y +value);
	}

	vector2D operator-(vector2D left, float value)
	{
		return  vector2D(left.x - value, left.y - value);
	}

	vector2D operator*(vector2D left, float value)
	{
		return  vector2D(left.x * value, left.y * value);
	}

	vector2D operator/(vector2D left, float value)
	{
		return  vector2D(left.x / value, left.y / value);
	}

	std::ostream& operator<<(std::ostream& stream, const vector2D& other)
	{
		stream << "(" << other.x << "," << other.y << ")";
		return stream;
	}
}
