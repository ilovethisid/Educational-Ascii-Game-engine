#pragma once

#include <string>

#include "CoordinateSystem.h"
#include "Matrix.h"

using namespace std;

class Object;

class Rigidbody 
{
private:
	Phy_Vector velocity;
	int x;
	int y;
	
	class Collider
	{
		friend Rigidbody;

	protected:
		string type;

	public:
		Collider();
		virtual ~Collider(){};
		virtual void move(int delta_x, int delta_y);
		// move according to velocity
		virtual void print();
	};

	class BoxCollider :private Collider
	{
		friend Rigidbody;

	private:
		Point topLeft;
		Point botRight;
		Point center;
		
	public:
		BoxCollider();
		~BoxCollider() {};
		BoxCollider(int x1, int y1, int x2, int y2);
		BoxCollider(int width, int height);

		virtual void move(int delta_x, int delta_y);
		// move according to velocity
	};

	class MatrixCollider :private Collider
	{
		friend Rigidbody;

	private:
		Matrix matrix;
		int x;
		int y;
		int width;
		int height;

	public:
		MatrixCollider();
		~MatrixCollider(){};
		MatrixCollider(Matrix& _matrix, int _x, int _y);
		virtual void move(int delta_x, int delta_y);
		// move according to velocity
	};

public:
	friend Object;

	Collider* collider;
	
	Rigidbody();
	~Rigidbody(){
		delete collider;
	}
	Rigidbody(int _x, int _y);

	void makeBoxCollider(int x1, int y1, int x2, int y2);
	void makeBoxCollider(int width, int height);
	void makeMatrixCollider(Matrix& matrix);
	void setVelocity(int x, int y);
	void move();
	void move(int delta_x, int delta_y);

	int checkCollision(Object& obj);
	int checkAABBCollision(Object& obj);
	int checkMatrixCollision(Object& obj);
};

