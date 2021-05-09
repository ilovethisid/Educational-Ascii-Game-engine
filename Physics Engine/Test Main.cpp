#include <iostream>

#include "Object.h"

using namespace std;

int main(void) {
	Object obj1 = Object(1, 1);
	Object obj2 = Object(6, 1);

	obj1.makeRigidbody();
	obj2.makeRigidbody();

	obj1.rigidbody.makeCollider(1, 1, 2, 2);
	obj2.rigidbody.makeCollider(6, 1, 7, 2);

	vector<Object*> objects;
	objects.push_back(&obj1);
	objects.push_back(&obj2);
	// all objects that is defined

	obj1.rigidbody.setVelocity(1, 0);

	printf("obj1 coord : %d %d\n", obj1.getX(), obj1.getY());
	printf("obj2 coord : %d %d\n", obj2.getX(), obj2.getY());

	printf("\nVelocity = 1, 0\n\n");

	printf("obj1 coord : %d %d\n", obj1.getX(), obj1.getY());
	obj1.move(objects);
	printf("obj1 coord : %d %d\n", obj1.getX(), obj1.getY());
	obj1.move(objects);
	printf("obj1 coord : %d %d\n", obj1.getX(), obj1.getY());
	obj1.move(objects);
	printf("obj1 coord : %d %d\n", obj1.getX(), obj1.getY());
	obj1.move(objects);
	printf("obj1 coord : %d %d\n", obj1.getX(), obj1.getY());
	obj1.move(objects);
	printf("obj1 coord : %d %d\n", obj1.getX(), obj1.getY());
	obj1.move(objects);
	printf("obj1 coord : %d %d\n", obj1.getX(), obj1.getY());
}