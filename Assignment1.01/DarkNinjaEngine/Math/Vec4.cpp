//#include "stdafx.h"
#include "../DarkNinjaEngine/Math/Vec4.h"


namespace Engine
{
	//vector4D::vector4D() :x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	//{
	//}

	vector4D::vector4D(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
	{
		
	}

	vector4D vector4D::Down()
	{
		vector4D temp;
		temp.x = 0.0;
		temp.y = -1.0;
		temp.z = 0.0;
		temp.w = 0.0;
		return temp;
	}

	vector4D vector4D::Zero()
	{
		vector4D temp;
		temp.x = 0.0;
		temp.y = 0.0;
		temp.z = 0.0;
		temp.w = 0.0;
		return temp;
	}

	vector4D vector4D::Up()
	{
		vector4D temp;
		temp.x = 0;
		temp.y = 1;
		temp.z = 0;
		temp.w = 0.0;
		return temp;
	}

	vector4D vector4D::Right()
	{
		vector4D temp;
		temp.x = 1;
		temp.y = 0;
		temp.z = 0;
		temp.w = 0.0;
		return temp;
	}

	vector4D vector4D::Left()
	{
		vector4D temp;
		temp.x = -1;
		temp.y = 0;
		temp.z = 0;
		temp.w = 0.0; 
		return temp;
	}

	vector4D& vector4D::Add(const vector4D& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	vector4D& vector4D::Subtract(const vector4D& other)
	{
		y -= other.y;
		x -= other.x;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	vector4D& vector4D::Multiply(const vector4D& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	}

	vector4D& vector4D::Divide(const vector4D& other)
	{
		x /= other.x;
		y /= other.y;
		y /= other.z;
		w /= other.w;
		return *this;
	}

	vector4D& vector4D::Add(float value)
	{
		x += value;
		y += value;
		z -= value;
		w -= value;
		return *this;
	}

	vector4D& vector4D::Subtract(float value)
	{
		x -= value;
		y -= value;
		z -= value;
		w -= value;
		return *this;
	}

	vector4D& vector4D::Multiply(float value)
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;
		return *this;
	}

	vector4D& vector4D::Divide(float value)
	{
		x /= value;
		y /= value;
		z /= value;
		w /= value;
		return *this;
	}

	bool vector4D::operator==(const vector4D& other) const
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}

	bool vector4D::operator!=(const vector4D& other) const
	{
		return !(*this == other);
	}

	bool vector4D::operator>(const vector4D& other) const
	{
		return x > other.x && y > other.y && z > other.z && w > other.w;
	}

	bool vector4D::operator<(const vector4D& other) const
	{
		return x < other.x && y < other.y && z < other.z && w< other.w;
	}

	bool vector4D::operator>=(const vector4D& other) const
	{
		return x >= other.x && y >= other.y && z >= other.z && w >=other.w;
	}

	bool vector4D::operator<=(const vector4D& other) const
	{
		return x <= other.x && y <= other.y && z <= other.z && w<=other.w;
	}

	vector4D vector4D::operator+=(const vector4D& other)
	{
		return Add(other);
	}

	vector4D vector4D::operator-=(const vector4D& other)
	{
		return Subtract(other);
	}

	vector4D vector4D::operator*=(const vector4D& other)
	{
		return Multiply(other);
	}

	vector4D vector4D::operator/=(const vector4D& other)
	{
		return Divide(other);
	}

	vector4D vector4D::operator+=(float value)
	{
		return Add(value);
	}

	vector4D vector4D::operator-=(float value)
	{
		return Subtract(value);
	}

	vector4D vector4D::operator*=(float value)
	{
		return Multiply(value);
	}

	vector4D vector4D::operator/=(float value)
	{
		return Divide(value);
	}

	float vector4D::Magnitude() const
	{
		return sqrt(x * x + y * y + z * z + w*w);
	}

	vector4D vector4D::Normalize() const
	{
		float temp = Magnitude();
		return vector4D(x / temp, y / temp, z / temp, w/temp);
	}

	float vector4D::Dot(const vector4D& other) const
	{
		return x * other.x + y * other.y + z * other.z + w*other.w;
	}

	vector4D operator+(vector4D left, const vector4D& right)
	{
		return left.Add(right);
	}

	vector4D operator-(vector4D left, const vector4D& right)
	{
		return left.Subtract(right);
	}

	vector4D operator*(vector4D left, const vector4D& right)
	{
		return left.Multiply(right);
	}

	vector4D operator/(vector4D left, const vector4D& right)
	{
		return left.Divide(right);
	}

	vector4D operator+(vector4D left, float value)
	{
		return  vector4D(left.x + value, left.y + value, left.z + value, left.w+value);
	}

	vector4D operator-(vector4D left, float value)
	{
		return  vector4D(left.x - value, left.y - value, left.z - value, left.w - value);
	}

	vector4D operator*(vector4D left, float value)
	{
		return  vector4D(left.x * value, left.y * value, left.z * value , left.w* value);
	}

	vector4D operator/(vector4D left, float value)
	{
		return  vector4D(left.x / value, left.y / value, left.z / value, left.z / value);
	}

	std::ostream& operator<<(std::ostream& stream, const vector4D& other)
	{
		stream << "(" << other.x << "," << other.y << "," << other.z << ","<<other.w <<")";
		return stream;
	}
}
