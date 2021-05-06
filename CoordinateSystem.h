#pragma once

class Point
{
private:
	int x;
	int y;

public:
	Point();
	Point(int _x, int _y);

	int getX();
	int getY();

	Point operator+(const Point& other);
	Point operator-(const Point& other);
	Point operator*(const Point& other);
	Point operator/(const Point& other);
	Point operator/(const int number);
};

class Phy_Vector
{
	int x;
	int y;

public:
	Phy_Vector();
};

