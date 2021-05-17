#include "CoordinateSystem.h"

Point::Point()
{
	x = 0;
	y = 0;
}

Point::Point(int _x, int _y)
{
	x = _x;
	y = _y;
}

int Point::getX()
{
	return x;
}

int Point::getY()
{
	return y;
}

Point Point::operator+(const Point& other)
{
	return Point(x + other.x, y + other.y);
}

Point Point::operator+(Phy_Vector& other)
{
	return Point(x + other.getX(), y + other.getY());
}

Point Point::operator-(const Point& other)
{
	return Point(x - other.x, y - other.y);
}

Point Point::operator*(const Point& other)
{
	return Point(x * other.x, y * other.y);
}

Point Point::operator/(const Point& other)
{
	return Point(x / other.x, y / other.y);
}

Point Point::operator/(const int number)
{
	return Point(x / number, y / number);
}

bool Point::operator>=(const Point& other)
{
	Point subtraction = *this - other;

	if (subtraction.x >= 0 && subtraction.y >= 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Point::operator<=(const Point& other)
{
	Point subtraction = *this - other;

	if (subtraction.x <= 0 && subtraction.y <= 0) {
		return true;
	}
	else {
		return false;
	}
}

Phy_Vector::Phy_Vector()
{
	x = 0;
	y = 0;
}

Phy_Vector::Phy_Vector(int _x, int _y)
{
	x = _x;
	y = _y;
}

int Phy_Vector::getX()
{
	return x;
}

int Phy_Vector::getY()
{
	return y;
}

Phy_Vector Phy_Vector::operator+(const Phy_Vector& other)
{
	return Phy_Vector(x + other.x, y + other.y);
}

Phy_Vector Phy_Vector::operator-(const Phy_Vector& other)
{
	return Phy_Vector(x - other.x, y - other.y);
}

Phy_Vector Phy_Vector::operator*(const Phy_Vector& other)
{
	return Phy_Vector(x * other.x, y * other.y);
}

Phy_Vector Phy_Vector::operator/(const Phy_Vector& other)
{
	return Phy_Vector(x / other.x, y / other.y);
}

Phy_Vector Phy_Vector::operator/(const int number)
{
	return Phy_Vector(x / number, y / number);
}