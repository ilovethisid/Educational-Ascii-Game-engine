#include "Object.h"

Object::Object()
{

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
	rigidbody = Rigidbody();
}

void Object::move(Object objects[])
{
	rigidbody.collider.move(rigidbody.velocity.getX(), rigidbody.velocity.getY());

	int num_objects = sizeof(objects) / sizeof(Object);
	bool collision = false;

	printf("test:%d\n", num_objects);

	for (int i = 0; i < num_objects; i++) {
		if (rigidbody.checkCollision(objects[i]) == 2) {
			// by moving collider, complete collision occurs
			collision = true;
		}
	}

	if (!collision) {
		x = x + rigidbody.velocity.getX();
		y = y + rigidbody.velocity.getY();
	}
	else {
		rigidbody.collider.move(-rigidbody.velocity.getX(), -rigidbody.velocity.getY());
		// since object didn't move, restore collider
	}
}
