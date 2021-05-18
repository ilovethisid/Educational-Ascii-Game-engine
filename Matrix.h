#pragma once

#include <vector>

using namespace std;

class Matrix
{
public:
	int width;
	int height;
	int** element;

	Matrix();
	Matrix(const Matrix& _matrix);
	Matrix(int _width, int _height);

	void fillElement(int** ary);
};

