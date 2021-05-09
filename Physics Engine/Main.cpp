#include <iostream>

#include "Object.h"

using namespace std;

int main(void) {
	Object obj1 = Object(1, 1);
	Object obj2 = Object(4, 1);

	obj1.makeRigidbody();
	obj2.makeRigidbody();

	Object objects[2];
	objects[0] = obj1;
	objects[1] = obj2;

	

	obj1.rigidbody.makeCollider(1, 1, 2, 2);
	obj2.rigidbody.makeCollider(4, 1, 5, 2);

	obj1.rigidbody.setVelocity(1, 0);

	obj1.move(objects);
	printf("%d\n", obj1.rigidbody.checkCollision(obj2));
	obj1.move(objects);
	printf("%d\n", obj1.rigidbody.checkCollision(obj2));
	obj1.move(objects);
	printf("%d\n", obj1.rigidbody.checkCollision(obj2));
	obj1.move(objects);
	printf("%d\n", obj1.rigidbody.checkCollision(obj2));
	obj1.move(objects);
	printf("%d\n", obj1.rigidbody.checkCollision(obj2));

	printf("%d %d\n", obj1.getX(), obj1.getY());
}