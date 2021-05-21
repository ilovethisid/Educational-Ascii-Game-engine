#include "Rigidbody.h"
#include "Object.h"

// Collider

Rigidbody::Collider::Collider()
{
	type = "\0";
}

void Rigidbody::Collider::move(int delta_x, int delta_y)
{

}


// BoxCollider

Rigidbody::BoxCollider::BoxCollider() :Collider()
{
	type = "BoxCollider";
	topLeft = Point();
	botRight = Point();
	center = Point();
}

Rigidbody::BoxCollider::BoxCollider(int x1, int y1, int x2, int y2) :Collider() {
	type = "BoxCollider";
	topLeft = Point(x1, y1);
	botRight = Point(x2, y2);
	center = (topLeft + botRight) / 2;
}

Rigidbody::BoxCollider::BoxCollider(int width, int height)
{

}

void Rigidbody::BoxCollider::move(int delta_x, int delta_y)
{
	topLeft = topLeft + Point(delta_x, delta_y);
	botRight = botRight + Point(delta_x, delta_y);
	center = center + Point(delta_x, delta_y);
}


// MatrixCollider

Rigidbody::MatrixCollider::MatrixCollider()
{
	type = "MatrixCollider";
	matrix = Matrix();
	x = 0;
	y = 0;
	width = 0;
	height = 0;
}

Rigidbody::MatrixCollider::MatrixCollider(Matrix _matrix, int _x, int _y)
{
	type = "MatrixCollider";
	matrix = Matrix(_matrix);
	x = _x;
	y = _y;
	width = _matrix.width;
	height = _matrix.height;
}

void Rigidbody::MatrixCollider::move(int delta_x, int delta_y)
{
	x = x + delta_x;
	y = y + delta_y;
}


// Rigidbody

Rigidbody::Rigidbody() {
	collider = NULL;
	velocity = Phy_Vector();
	x = 0;
	y = 0;
}

Rigidbody::Rigidbody(int _x, int _y)
{
	collider = NULL;
	velocity = Phy_Vector();
	x = _x;
	y = _y;
}

void Rigidbody::makeBoxCollider(int x1, int y1, int x2, int y2)
{
	int minX, minY;
	int maxX, maxY;

	if (x1 > x2) {
		minX = x2;
		maxX = x1;
	}
	else {
		minX = x1;
		maxX = x2;
	}
	
	if (y1 > y2) {
		minY = y2;
		maxY = y1;
	}
	else {
		minY = y1;
		maxY = y2;
	}

	collider = new BoxCollider(minX, minY, maxX, maxY);
}

void Rigidbody::makeBoxCollider(int width, int height)
{
	makeBoxCollider(x, y, x + width, y + height);
}

void Rigidbody::makeMatrixCollider(Matrix matrix)
{
	collider = new MatrixCollider(matrix, x, y);
}

void Rigidbody::setVelocity(int x, int y)
{
	velocity = Phy_Vector(x, y);
}

void Rigidbody::move()
{
	x = x + velocity.getX();
	y = y + velocity.getY();
}

int Rigidbody::checkCollision(Object& obj)
{
	if (this->collider->type == "BoxCollider" && obj.rigidbody.collider->type == "BoxCollider") {
		return checkAABBCollision(obj);
	}
	else if (this->collider->type == "MatrixCollider" && obj.rigidbody.collider->type == "MatrixCollider") {
		return checkMatrixCollision(obj);
	}
	else {
		return -1;
	}
}

int Rigidbody::checkAABBCollision(Object& obj)
{
	BoxCollider* collider1 = (BoxCollider*)collider;
	BoxCollider* collider2 = (BoxCollider*)obj.rigidbody.collider;

	Point TL2 = collider2->topLeft;
	Point BR2 = collider2->botRight;

	int distX1 = collider1->topLeft.getX() - BR2.getX();
	int distY1 = collider1->topLeft.getY() - BR2.getY();
	int distX2 = TL2.getX() - collider1->botRight.getX();
	int distY2 = TL2.getY() - collider1->botRight.getY();

	if ((distX1 > 1) || (distX2 > 1)) {
		// collider's x coordinates are distinct( > 1) : they cannot meet
		return 0;
	}
	if ((distY1 > 1) || (distY2 > 1)) {
		// collider's y coordinates are distinct( > 1) : they cannot meet
		return 0;
	}

	if ((distX1 == 1) || (distX2 == 1)) {
		// collider's x coordinates are close( = 1) : they are bordered
		return 1;
	}
	if ((distY1 == 1) || (distY2 == 1)) {
		// collider's y coordinates are close( = 1) : they are bordered
		return 1;
	}

	return 2;
	// complete collision
}

int Rigidbody::checkMatrixCollision(Object& obj)
{
	MatrixCollider* collider1 = (MatrixCollider*)collider;
	MatrixCollider* collider2 = (MatrixCollider*)obj.rigidbody.collider;

	Matrix overlapping_matrix;

	Point topLeft1 = Point(collider1->x, collider1->y);
	Point botRight1 = Point(collider1->x + collider1->width - 1, collider1->y + collider1->height - 1);
	Point topLeft2 = Point(collider2->x, collider2->y);
	Point botRight2 = Point(collider2->x + collider2->width - 1, collider2->y + collider2->height - 1);

	if (((topLeft1 <= topLeft2) && (topLeft2 <= botRight1)) || ((topLeft1 <= botRight2) && (botRight2 <= botRight1))) {
		// colliders overlap

		int overlap_topLeft_x = max(topLeft1.getX(), topLeft2.getX());
		int overlap_topLeft_y = max(topLeft1.getY(), topLeft2.getY());
		int overlap_botRight_x = min(botRight1.getX(), botRight2.getX());
		int overlap_botRight_y = min(botRight1.getY(), botRight2.getY());

		int width = overlap_botRight_x - overlap_topLeft_x + 1;
		int height = overlap_botRight_y - overlap_topLeft_y + 1;

		overlapping_matrix = Matrix(width, height);

		int** element = new int* [height];
		for (int i = 0; i < height; i++) {
			element[i] = new int[width];
		}
		// make 2d array element

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				element[i][j] = collider1->matrix.element[overlap_topLeft_y - topLeft1.getY() + i][overlap_topLeft_x - topLeft1.getX() + j]
					& collider2->matrix.element[overlap_topLeft_y - topLeft2.getY() + i][overlap_topLeft_x - topLeft2.getX() + j];
			}
		}
		// compute element[i][j]

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (element[i][j]) {
					return 2;
				}
			}
		}
		// if element[i][j] = 1 (collision is true)
		// return 2

		return 0;
	}
}



int min(int a, int b) {
	if (a < b) {
		return a;
	}
	else {
		return b;
	}
}

int max(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}




