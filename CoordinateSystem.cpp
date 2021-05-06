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

Point Point::operator+(const Point& other)
{
	return Point(x + other.x, y + other.y);
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

int Point::getX()
{
	return x;
}

int Point::getY()
{
	return y;
}

Phy_Vector::Phy_Vector()
{
	x = 0;
	y = 0;
}
