#include "Matrix.h"

Matrix::Matrix()
{
	width = 0;
	height = 0;
	element = NULL;
	color = NULL;
}

Matrix::Matrix(const Matrix& _matrix)
{
	width = _matrix.width;
	height = _matrix.height;
	

	color = new unsigned char [width * height];


	element = new short* [height];
	for (int i = 0; i < height; i++) {
		element[i] = new short[width];
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			element[i][j] = _matrix.element[i][j];
			color[i * width + j] = _matrix.color[i * width + j];
		}
	}
}

Matrix::Matrix(short _width, short _height)
{
	width = _width;
	height = _height;
	element = new short* [height];
	for (int i = 0; i < height; i++) {
		element[i] = new short[width];
		memset(element[i], 0, sizeof(short) * width);
	}
	color = new unsigned char[width * height];
}

void Matrix::fillElement(int** ary,char* c_arr)
{
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			element[i][j] = ary[i][j];
			color[i * width + j] = c_arr[i * width + j];
		}
	}
}

