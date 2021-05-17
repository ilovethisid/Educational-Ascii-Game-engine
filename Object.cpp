#include "Object.h"

Object::Object()
{
	x = 0;
	y = 0;
}

Object::Object(int _x, int _y)
{
	x = _x;
	y = _y;
}

int Object::getX()
{
	return x;
}

int Object::getY()
{
	return y;
}

void Object::makeRigidbody()
{
	rigidbody = Rigidbody(x, y);
}

void Object::move(vector<Object*>& objects)
{
	rigidbody.collider->move(rigidbody.velocity.getX(), rigidbody.velocity.getY());

	bool collision = false;

	for (int i = 0; i < objects.size(); i++) {
		if (objects[i] != this && rigidbody.checkCollision(*objects[i]) == 2) {
			// by moving collider, complete collision occurs
			collision = true;
		}
	}

	if (!collision) {
		x = x + rigidbody.velocity.getX();
		y = y + rigidbody.velocity.getY();
		rigidbody.move();
	}
	else {
		rigidbody.collider->move(-rigidbody.velocity.getX(), -rigidbody.velocity.getY());
		// since object didn't move, restore collider
	}
}
