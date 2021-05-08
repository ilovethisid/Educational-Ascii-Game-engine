#pragma once

#include <stdio.h>

#include "Rigidbody.h"

class Object
{
private:
	int x;
	int y;

public:
	Rigidbody rigidbody;

	Object();
	Object(int _x, int _y);

	int getX();
	int getY();

	void makeRigidbody();
	void move(Object objects[]);
	// move according to velocity
};

