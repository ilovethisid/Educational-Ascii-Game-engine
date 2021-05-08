#pragma once

#include "CoordinateSystem.h"

class Object;

class Rigidbody 
{
private:

	class BoxCollider
	{
	public:
		Point topLeft;
		Point botRight;
		Point center;

		BoxCollider();
		BoxCollider(int x1, int y1, int x2, int y2);

		void move(int delta_x, int delta_y);
		// move according to velocity
	};

	Phy_Vector velocity;

	friend Object;

public:
	BoxCollider collider;
	
	Rigidbody();

	void makeCollider(int x1, int y1, int x2, int y2);
	void setVelocity(int x, int y);

	int checkCollision(Object& obj);
};

