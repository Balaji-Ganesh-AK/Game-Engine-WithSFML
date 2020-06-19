#include "stdafx.h"
#include "Point2D.h"

namespace vec2
{
	Point2D::Point2D()
	{
			x = 0;
			y = 0;
	}
	Point2D::Point2D(const int& x, const int& y)
	{
		this->x = x;
		this->y = y;
	}
 	Point2D& Point2D::Random(const int& other)
	{
		this->x = rand() % 100;
		this->y = rand() % 100;
		return *this;
		

	}
	Point2D& Point2D::addition(const Point2D& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}
	Point2D& Point2D::subtraction(const Point2D& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}
	Point2D& Point2D::division(const Point2D& other)
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}
	Point2D& Point2D::multiplication(const Point2D& other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}
	//operator overloading
	Point2D& Point2D::operator+=(const Point2D&other)
	{
		return addition(other);
	}
	Point2D& Point2D::operator+(const Point2D&other)
	{
		return addition(other);
	}
	Point2D& Point2D::operator-=(const Point2D&other)
	{
		return subtraction(other);
	}
	Point2D& Point2D::operator-(const Point2D&other)
	{
		return subtraction(other);
	}
	//Negation
	Point2D& Point2D::operator-()
	{
		this->x = -1 * this->x;
		this->y = -1 * this->y;
		return *this;
	}
	Point2D& Point2D::operator/=(const Point2D&other)
	{
		return division(other);
	}
	Point2D operator/(Point2D left, const Point2D &right)
	{
		return left.division(right);
	}
	bool Point2D::operator==(const Point2D & other)
	{
		return x == other.x && y == other.y;
	}
	bool Point2D::operator!=(const Point2D & other)
	{
		return !(*this == other);
	}
	Point2D operator*(Point2D left, const Point2D &right)
	{
		return left.multiplication(right);
	}
	Point2D& Point2D::operator*=(const Point2D&other)
	{
		return multiplication(other);
	}
	Point2D::~Point2D()
	{
	}

	Point2D Point2D::zero()
	{
		this->x = 0;
		this->y = 0;
		return *this;
	}

	//scaler
	Point2D& Point2D::operator+=(const float&other)
	{
		this->x = other + this->x;
		this->y = other + this->y;
		return *this;
	}
	Point2D& Point2D::operator+(const float&other)
	{
		this->x = other + this->x;
		this->y = other + this->y;
		return *this;
	}
	Point2D& Point2D::operator-=(const float&other)
	{
		this->x = other - this->x;
		this->y = other - this->y;
		return *this;
	}

	Point2D& Point2D::operator-(const float&other)
	{
		this->x = other - this->x;
		this->y = other - this->y;
		return *this;
	}
	Point2D& Point2D::operator*(const float&other)
	{
		this->x = other * this->x;
		this->y = other * this->y;
		return *this;
	}
	Point2D& Point2D::operator*=(const float&other)
	{
		this->x = other * this->x;
		this->y = other * this->y;
		return *this;
	}
	Point2D& Point2D::operator/=(const float&other)
	{
		this->x = other / this->x;
		this->y = other / this->y;
		return *this;
	}
	Point2D& Point2D::operator/(const float&other)
	{
		this->x = other / this->x;
		this->y = other / this->y;
		return *this;
	}

	// Printing overloading
	std::ostream & operator<<(std::ostream & stream, const Point2D & vector2D)
	{
		stream << "("<<vector2D.x <<","<< vector2D.y <<")";
		return stream;
	}
}
