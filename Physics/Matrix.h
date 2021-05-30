#pragma once

#include <vector>

using namespace std;

class Matrix
{
public:
	short width;
	short height;
	short** element;
	unsigned char* color;

	Matrix();
	Matrix(const Matrix& _matrix);
	Matrix(short _width, short _height);

	void fillElement(int** ary, char* color);
};

