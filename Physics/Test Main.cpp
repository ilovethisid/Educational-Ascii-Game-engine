/*
#include <iostream>

#include "Object.h"

using namespace std;

int main(void) {
	Object obj1 = Object(1, 1);
	Object obj2 = Object(6, 6);

	obj1.makeRigidbody();
	obj2.makeRigidbody();

	obj1.rigidbody.makeBoxCollider(1, 1);
	obj2.rigidbody.makeBoxCollider(1, 1);

	vector<Object*> objects;
	objects.push_back(&obj1);
	objects.push_back(&obj2);
	// all objects that is defined

	obj1.rigidbody.setVelocity(1, 1);

	printf("obj1 coord : %d %d\n", obj1.getX(), obj1.getY());
	printf("obj2 coord : %d %d\n", obj2.getX(), obj2.getY());

	printf("\nVelocity = 1, 1\n\n");

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

	Object obj3 = Object(1, 1);
	Object obj4 = Object(6, 6);

	obj3.makeRigidbody();
	obj4.makeRigidbody();

	int** ary1;
	int** ary2;

	ary1 = new int* [2];
	ary1[0] = new int[2];
	ary1[1] = new int[2];
	ary1[0][0] = 1;
	ary1[0][1] = 0;
	ary1[1][0] = 0;
	ary1[1][1] = 1;

	ary2 = new int* [2];
	ary2[0] = new int[2];
	ary2[1] = new int[2];
	ary2[0][0] = 1;
	ary2[0][1] = 1;
	ary2[1][0] = 1;
	ary2[1][1] = 1;

	Matrix matrix1 = Matrix(2, 2);
	Matrix matrix2 = Matrix(2, 2);


	matrix1.fillElement(ary1);
	matrix2.fillElement(ary2);

	obj3.rigidbody.makeMatrixCollider(matrix1);
	obj4.rigidbody.makeMatrixCollider(matrix2);

	objects.push_back(&obj3);
	objects.push_back(&obj4);
	// all objects that is defined

	obj3.rigidbody.setVelocity(1, 1);

	printf("\n\nobj3 coord : %d %d\n", obj3.getX(), obj3.getY());
	printf("obj4 coord : %d %d\n", obj4.getX(), obj4.getY());

	printf("\nVelocity = 1, 1\n\n");

	printf("obj3 coord : %d %d\n", obj3.getX(), obj3.getY());
	obj3.move(objects);
	printf("obj3 coord : %d %d\n", obj3.getX(), obj3.getY());
	obj3.move(objects);
	printf("obj3 coord : %d %d\n", obj3.getX(), obj3.getY());
	obj3.move(objects);
	printf("obj3 coord : %d %d\n", obj3.getX(), obj3.getY());
	obj3.move(objects);
	printf("obj3 coord : %d %d\n", obj3.getX(), obj3.getY());
	obj3.move(objects);
	printf("obj3 coord : %d %d\n", obj3.getX(), obj3.getY());
	obj3.move(objects);
	printf("obj3 coord : %d %d\n", obj3.getX(), obj3.getY());
	obj3.move(objects);
	printf("obj3 coord : %d %d\n", obj3.getX(), obj3.getY());
}
*/