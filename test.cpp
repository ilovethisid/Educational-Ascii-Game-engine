#include <iostream>
using namespace std;
#include "GraphicEngine.h"

int main() {

	Console demo;
	demo.make_console(160, 100, 8, 8);
	demo.draw_circle(10, 10, 5);
	demo.draw_circle(10, 10, 5);
	int x = 0;
	int y = 0;
	int x1 = 100;
	int y1 = 100;
	while (1) {
		demo.set_tmpbufScreen();
		MATRIX* pnt_circle = demo.make_circle(10);
		demo.tmp_draw_matrix(x++, y++, *pnt_circle);
		MATRIX* pnt_square = demo.make_square(6,10);
		demo.tmp_draw_matrix(x1--, y1--, *pnt_square);
		demo.update();
		Sleep(100);


	}
}