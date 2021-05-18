#include <iostream>

#include "GraphicEngine.h"

using namespace std;

int main(void) {

	Console demo;
	demo.make_console(160, 100, 8, 8);

	int x = 0;
	int y = 0;
	int x1 = 100;
	int y1 = 100;
	Object obj1 = Object(1, 1);
	Object obj2 = Object(50, 50);
	

	Matrix matrix1 = demo.make_circle(10);
	Matrix matrix2 = demo.make_circle(20);
	obj1.makeRigidbody();
	obj2.makeRigidbody();
	obj1.makeImage(matrix1);
	obj2.makeImage(matrix2);
	obj1.rigidbody.setVelocity(1, 1);
	obj1.rigidbody.makeMatrixCollider(matrix1);
	obj2.rigidbody.makeMatrixCollider(matrix2);
	vector<Object*> objects;

	objects.push_back(&obj1);
	objects.push_back(&obj2);
	while (1) {
		demo.set_tmpbufScreen();
		demo.tmp_draw_Object(obj1);
		demo.tmp_draw_Object(obj2);
		obj1.move(objects);
		demo.update();
		Sleep(100);

	}

}


//#include <iostream>
//using namespace std;
//#include "GraphicEngine.h"
//
//int main() {
//
//	Console demo;
//	demo.make_console(160, 100, 8, 8);
//	demo.draw_triangle(1, 1, 10, 10, 3, 40);
//
//	int x = 0;
//	int y = 0;
//	int x1 = 100;
//	int y1 = 100;
//	while (1) {
//		demo.set_tmpbufScreen();
//		//MATRIX* pnt_circle = demo.make_circle(10);
//		//demo.tmp_draw_matrix(x++, y++, *pnt_circle);
//		//MATRIX* pnt_square = demo.make_square(6,10);
//		//demo.tmp_draw_matrix(x1--, y1--, *pnt_square);
//		demo.update();
//		Sleep(100);
//
//	}
//}