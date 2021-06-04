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
	~Matrix();
	Matrix(const Matrix& _matrix);
	Matrix(short _width, short _height);

	Matrix& operator=(const Matrix& fellow) {
		this->width = fellow.width;
		this->height = fellow.height;
		delete color;
		delete element;
		this->color = new unsigned char[width * height];
		this->element = new short* [height];
		for (int i = 0; i < height; i++) {
			element[i] = new short[width];
		}
		for (int i = 0; i < this->height; i++) {
			for (int j = 0; j < this->width; j++) {
				this->element[i][j] = fellow.element[i][j];
				this->color[i * width + j] = fellow.color[i * width + j];
			}
		}
		return *this;
	}


	void fillElement(int** ary, char* color);
};

