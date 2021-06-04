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
	char* name;
	Matrix image; 
public:
	Rigidbody rigidbody;
	char collision_flg=0;
	Object();
	~Object();
	Object(int _x, int _y);

	void makeRigidbody();
	void makeImage(Matrix& _image);
	void move(vector<Object*>& objects);
	// move according to velocity
	// get vector of all objects to check collision
	void setName(const char* name);

	int getX();
	int getY();
	char* getName();
	Matrix getImage(); //복사한 image값을 주게 바꿈

	static Object* findByName(vector<Object*>& objects, const char* name);
};

