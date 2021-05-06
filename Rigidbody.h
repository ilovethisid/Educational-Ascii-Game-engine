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
	};

	Phy_Vector velocity;

public:
	BoxCollider collider;
	
	Rigidbody();

	void makeCollider(int x1, int y1, int x2, int y2);

	int checkCollision(Object& obj);
};

