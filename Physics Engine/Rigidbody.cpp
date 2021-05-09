#include "Rigidbody.h"
#include "Object.h"

Rigidbody::BoxCollider::BoxCollider()
{
	topLeft = Point();
	botRight = Point();
	center = Point();
}

Rigidbody::BoxCollider::BoxCollider(int x1, int y1, int x2, int y2) {
	topLeft = Point(x1, y1);
	botRight = Point(x2, y2);
	center = (topLeft + botRight) / 2;
}

void Rigidbody::BoxCollider::move(int delta_x, int delta_y)
{
	topLeft = topLeft + Point(delta_x, delta_y);
	botRight = botRight + Point(delta_x, delta_y);
	center = center + Point(delta_x, delta_y);
}

Rigidbody::Rigidbody() {
	velocity = Phy_Vector();
}

void Rigidbody::makeCollider(int x1, int y1, int x2, int y2)
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

	collider = BoxCollider(minX, minY, maxX, maxY);
}

void Rigidbody::setVelocity(int x, int y)
{
	velocity = Phy_Vector(x, y);
}

int Rigidbody::checkCollision(Object& obj)
{
	Point TL2 = obj.rigidbody.collider.topLeft;
	Point BR2 = obj.rigidbody.collider.botRight;

	int distX1 = collider.topLeft.getX() - BR2.getX();
	int distY1 = collider.topLeft.getY() - BR2.getY();
	int distX2 = TL2.getX() - collider.botRight.getX();
	int distY2 = TL2.getY() - collider.botRight.getY();

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
