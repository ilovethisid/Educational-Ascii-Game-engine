#pragma once

#include <vector>

using namespace std;

class Matrix
{
public:
	int width;
	int height;
	short** element;

	Matrix();
	Matrix(const Matrix& _matrix);
	Matrix(int _width, int _height);

	void fillElement(short** ary);
};

