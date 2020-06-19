//#include "stdafx.h"
#include "../DarkNinjaEngine/Math/Vec3.h"


namespace vector3D
{
	vector3D::vector3D() :x(0.0f), y(0.0f), z(0.0f)
	{
	}

	vector3D::vector3D(float x, float y, float z) : x(x), y(y),z(z)
	{
	}

	vector3D vector3D::Down()
	{
		vector3D temp;
		temp.x = 0.0;
		temp.y = 1.0;
		temp.z = 0.0;
		return temp;
	}

	vector3D vector3D::Zero()
	{
		vector3D temp;
		temp.x = 0.0;
		temp.y = 0.0;
		temp.z = 0.0;
		return temp;
	}

	vector3D vector3D::Up()
	{
		vector3D temp;
		temp.x = 0;
		temp.y = -1;
		temp.z = 0;
		return temp;
	}

	vector3D vector3D::Right()
	{
		vector3D temp;
		temp.x = 1;
		temp.y = 0;
		temp.z = 0;
		return temp;
	}

	vector3D vector3D::Left()
	{
		vector3D temp;
		temp.x = -1;
		temp.y = 0;
		temp.z = 0;
		return temp;
	}

	vector3D& vector3D::Add(const vector3D& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	vector3D& vector3D::Subtract(const vector3D& other)
	{
		y -= other.y;
		x -= other.x;
		z -= other.z;
		return *this;
	}

	vector3D& vector3D::Multiply(const vector3D& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	vector3D& vector3D::Divide(const vector3D& other)
	{
		x /= other.x;
		y /= other.y;
		y /= other.z;
		return *this;
	}

	vector3D& vector3D::Add(float value)
	{
		x += value;
		y += value;
		z -= value;
		return *this;
	}

	vector3D& vector3D::Subtract(float value)
	{
		x -= value;
		y -= value;
		z -= value;
		return *this;
	}

	vector3D& vector3D::Multiply(float value)
	{
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}

	vector3D& vector3D::Divide(float value)
	{
		x /= value;
		y /= value;
		z /= value;
		return *this;
	}

	bool vector3D::operator==(const vector3D& other) const
	{
		return x == other.x && y == other.y && z ==other.z;
	}

	bool vector3D::operator!=(const vector3D& other) const
	{
		return !(*this == other);
	}

	bool vector3D::operator>(const vector3D& other) const
	{
		return x > other.x && y > other.y && z > other.z;
	}

	bool vector3D::operator<(const vector3D& other) const
	{
		return x < other.x && y < other.y && z< other.z;
	}

	bool vector3D::operator>=(const vector3D& other) const
	{
		return x >= other.x && y >= other.y && z>= other.z;
	}

	bool vector3D::operator<=(const vector3D& other) const
	{
		return x <= other.x && y <= other.y && z<= other.z;
	}

	vector3D vector3D::operator+=(const vector3D& other)
	{
		return Add(other);
	}

	vector3D vector3D::operator-=(const vector3D& other)
	{
		return Subtract(other);
	}

	vector3D vector3D::operator*=(const vector3D& other)
	{
		return Multiply(other);
	}

	vector3D vector3D::operator/=(const vector3D& other)
	{
		return Divide(other);
	}

	vector3D vector3D::operator+=(float value)
	{
		return Add(value);
	}

	vector3D vector3D::operator-=(float value)
	{
		return Subtract(value);
	}

	vector3D vector3D::operator*=(float value)
	{
		return Multiply(value);
	}

	vector3D vector3D::operator/=(float value)
	{
		return Divide(value);
	}

	float vector3D::Magnitude() const
	{
		return sqrt(x * x + y * y + z*z);
	}

	vector3D vector3D::Normalize() const
	{
		float temp = Magnitude();
		return vector3D(x / temp, y / temp , z/temp);
	}

	float vector3D::Dot(const vector3D& other) const
	{
		return x * other.x + y * other.y + z*other.z;
	}

	vector3D operator+(vector3D left, const vector3D& right)
	{
		return left.Add(right);
	}

	vector3D operator-(vector3D left, const vector3D& right)
	{
		return left.Subtract(right);
	}

	vector3D operator*(vector3D left, const vector3D& right)
	{
		return left.Multiply(right);
	}

	vector3D operator/(vector3D left, const vector3D& right)
	{
		return left.Divide(right);
	}

	vector3D operator+(vector3D left, float value)
	{
		return  vector3D(left.x + value, left.y + value , left.z + value);
	}

	vector3D operator-(vector3D left, float value)
	{
		return  vector3D(left.x - value, left.y - value ,left.z - value);
	}

	vector3D operator*(vector3D left, float value)
	{
		return  vector3D(left.x * value, left.y * value, left.z *value);
	}

	vector3D operator/(vector3D left, float value)
	{
		return  vector3D(left.x / value, left.y / value, left.z /value);
	}

	std::ostream& operator<<(std::ostream& stream, const vector3D& other)
	{
		stream << "(" << other.x << "," << other.y << "," <<other.z <<")";
		return stream;
	}
}
