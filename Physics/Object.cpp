
#define _CRT_SECURE_NO_WARNINGS

#include "Object.h"

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

	if (checkObjectsCollision(objects)) {
		return;
	}

	while (abs(xVelocity) > 0) {
		rigidbody.collider->move(sign(xVelocity), 0);

		if (checkObjectsCollision(objects)) {
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

			if (checkObjectsCollision(objects)) {
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

		if (checkObjectsCollision(objects)) {
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

Matrix& Object::getImage()
{
	return image;
}

vector<Object*>& Object::getCollidingObjects(vector<Object*>& objects)
{
	for (int i = 0; i < colliding_objects.size(); i++) {
		colliding_objects.pop_back();
	}

	for (int i = 0; i < objects.size(); i++) {
		/* there is object right next to current object (they are bordered) */
		for (int j = -1; j <= 1; j += 2) {
			rigidbody.collider->move(j, 0);
			if ((objects[i] != this) && (this->rigidbody.checkCollision(*objects[i]) == 2)) {
				// by moving collider, complete collision occurs
				this->collision_flg = 1;
				objects[i]->collision_flg = 1;
				colliding_objects.push_back(objects[i]);
				rigidbody.collider->move(-j, 0);
				break;
			}
			rigidbody.collider->move(-j, 0);

			rigidbody.collider->move(0, j);
			if ((objects[i] != this) && (this->rigidbody.checkCollision(*objects[i]) == 2)) {
				// by moving collider, complete collision occurs
				this->collision_flg = 1;
				objects[i]->collision_flg = 1;
				colliding_objects.push_back(objects[i]);
				rigidbody.collider->move(0, -j);
				break;
			}
			rigidbody.collider->move(0, -j);
		}
	}

	return colliding_objects;
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

bool Object::checkObjectsCollision(vector<Object*>& objects) {
	bool is_colliding = false;

	for (int i = 0; i < objects.size(); i++) {
		if ((objects[i] != this) && (this->rigidbody.checkCollision(*objects[i]) == 2)) {
			// by moving collider, complete collision occurs
			this->collision_flg = 1;
			objects[i]->collision_flg = 1;
			//colliding_objects.push_back(objects[i]);
			
			is_colliding = true;
		}
	}

	return is_colliding;
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
	delete[] name;
}