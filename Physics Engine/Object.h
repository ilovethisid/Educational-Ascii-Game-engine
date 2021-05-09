#pragma once

#include <iostream>
#include <vector>

#include "Rigidbody.h"

using namespace std;

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
	void move(vector<Object*>& objects);
	// move according to velocity
	// get vector of all objects to check collision
};

