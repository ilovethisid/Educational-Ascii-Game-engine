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
	Matrix image;

public:
	Rigidbody rigidbody;

	Object();
	Object(int _x, int _y);

	void makeRigidbody();
	void makeImage(Matrix _image);
	void move(vector<Object*>& objects);
	// move according to velocity
	// get vector of all objects to check collision

	int getX();
	int getY();
	Matrix getImage();
};

