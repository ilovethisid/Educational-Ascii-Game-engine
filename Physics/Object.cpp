
#define _CRT_SECURE_NO_WARNINGS

#include "Object.h"

bool checkObjectsCollision(Object* current_obj, vector<Object*>& objects);
int sign(int x);

Object::Object()
{
	x = 0;
	y = 0;
	name = NULL;
}

Object::Object(int _x, int _y)
{
	x = _x;
	y = _y;
	name = NULL;
}

void Object::makeRigidbody()
{
	rigidbody = Rigidbody(x, y);
}

void Object::makeImage(Matrix& _image)
{
	image = Matrix(_image);
	
}

void Object::move(vector<Object*>& objects)
{
	int xVelocity = rigidbody.velocity.getX();
	int yVelocity = rigidbody.velocity.getY();

	if (checkObjectsCollision(this, objects)) {
		return;
	}

	while (abs(xVelocity) > 0) {
		rigidbody.collider->move(sign(xVelocity), 0);

		if (checkObjectsCollision(this, objects)) {
			rigidbody.collider->move(-sign(xVelocity), 0);
		}
		else {
			x = x + sign(xVelocity);
			y = y;
			rigidbody.move(sign(xVelocity), 0);
		}

		xVelocity -= sign(xVelocity);
		// decrease xVelocity

		if (abs(yVelocity) > 0) {
			rigidbody.collider->move(0, sign(yVelocity));

			if (checkObjectsCollision(this, objects)) {
				rigidbody.collider->move(0, -sign(yVelocity));
			}
			else {
				x = x;
				y = y + sign(yVelocity);
				rigidbody.move(0, sign(yVelocity));
			}

			yVelocity -= sign(yVelocity);
			// decrease yVelocity
		}
	}

	/* if yVelocity is left */
	while (abs(yVelocity) > 0) {
		rigidbody.collider->move(0, sign(yVelocity));

		if (checkObjectsCollision(this, objects)) {
			rigidbody.collider->move(0, -sign(yVelocity));
		}
		else {
			x = x;
			y = y + sign(yVelocity);
			rigidbody.move(0, sign(yVelocity));
		}

		yVelocity -= sign(yVelocity);
		// decrease yVelocity
	}
}

void Object::setName(const char* name)
{
	this->name = new char[20];
	strcpy(this->name, name);
}

int Object::getX()
{
	return x;
}

int Object::getY()
{
	return y;
}

char* Object::getName()
{
	return name;
}

Matrix Object::getImage()
{
	return  Matrix(image);
}

Object* Object::findByName(vector<Object*>& objects, const char* name)
{
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getName()) {
			if (!strcmp(objects[i]->getName(), name)) {
				return objects[i];
			}
		}
	}

	return nullptr;
}

bool checkObjectsCollision(Object* current_obj, vector<Object*>& objects) {
	for (int i = 0; i < objects.size(); i++) {
		if ((objects[i] != current_obj) && (current_obj->rigidbody.checkCollision(*objects[i]) == 2)) {
			// by moving collider, complete collision occurs
			current_obj->collision_flg = 1;
			objects[i]->collision_flg = 1;
			return true;
		}
	}

	return false;
}

int sign(int x) {
	if (x > 0) {
		return 1;
	}
	else if (x < 0) {
		return -1;
	}
	else {
		return 0;
	}
}

Object::~Object() {
	delete(this->name);
}