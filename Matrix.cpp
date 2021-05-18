#include "Matrix.h"

Matrix::Matrix()
{
	width = 0;
	height = 0;
	element = NULL;
}

Matrix::Matrix(const Matrix& _matrix)
{
	width = _matrix.width;
	height = _matrix.height;
	
	element = new short* [height];
	for (int i = 0; i < height; i++) {
		element[i] = new short[width];
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			element[i][j] = _matrix.element[i][j];
		}
	}
}

Matrix::Matrix(int _width, int _height)
{
	width = _width;
	height = _height;
	element = new short* [height];
	for (int i = 0; i < height; i++) {
		element[i] = new short[width];
		memset(element[i], 0, sizeof(short) * width);
	}
}

void Matrix::fillElement(short** ary)
{
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			element[i][j] = ary[i][j];
		}
	}
}

