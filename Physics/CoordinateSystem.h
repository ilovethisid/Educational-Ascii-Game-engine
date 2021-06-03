#pragma once

class Phy_Vector
{
private:
	int x;
	int y;

public:
	Phy_Vector();
	Phy_Vector(int _x, int _y);

	void changeValue(int _x, int _y);
	int getX();
	int getY();

	Phy_Vector operator+(const Phy_Vector& other);
	Phy_Vector operator-(const Phy_Vector& other);
	Phy_Vector operator*(const Phy_Vector& other);
	Phy_Vector operator/(const Phy_Vector& other);
	Phy_Vector operator/(const int number);
};

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
	Point operator+(Phy_Vector& other);
	Point operator-(const Point& other);
	Point operator*(const Point& other);
	Point operator/(const Point& other);
	Point operator/(const int number);
	bool operator>=(const Point& other);
	bool operator<=(const Point& other);
};


