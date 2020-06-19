#pragma once
#include <iostream>
namespace vec2
{

	class Point2D
	{
		//float x, y;
	public:

		Point2D();
		~Point2D();
		int x, y;
		//operations
		//Point2D(const float & x, const float & y);
		Point2D zero();
		Point2D(const int & x, const int & y);
		Point2D& Random(const int & other);
		Point2D& addition(const Point2D& other); // reference , just reads the values and doesnt not store them
		Point2D & subtraction(const Point2D & other);
		Point2D & division(const Point2D & other);
		Point2D & multiplication(const Point2D & other);
		Point2D & operator+=(const Point2D & other);
		Point2D & operator+(const Point2D & other);
		
		Point2D & operator-=(const Point2D & other);
		Point2D & operator-(const Point2D & other);
		Point2D  &operator-();
		Point2D & operator/=(const Point2D & other);
		friend Point2D operator/(Point2D left, const Point2D & right);
		bool operator==(const Point2D & other);
		bool operator!=(const Point2D & other);
		Point2D & operator*=(const Point2D & other);

		Point2D & operator+=(const float & other);

		Point2D & operator+(const float & other);

		Point2D & operator-=(const float & other);
		Point2D & operator-(const float & other);

		Point2D & operator*(const float & other);

		Point2D & operator*=(const float & other);

		Point2D & operator/=(const float & other);

		Point2D & operator/(const float & other);

		
		

		//overloading

		

	

		//Printing the values
		friend std::ostream& operator<<(std::ostream& stream, const Point2D& vector2D);

	};
}

