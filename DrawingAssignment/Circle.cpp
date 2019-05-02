#include "Circle.h"

Circle::Circle(int startX, int startY, int endX, int endY, int lineColour, int fillColour) : Shape(startX, startY, endX, endY, lineColour, fillColour)
{
}


Circle::~Circle()
{
}

void Circle::draw(EasyGraphics* canvas)
{
	canvas->setPenColour(lineColour, 1);
	canvas->selectBackColour(fillColour);

	// Calculate radius
	// a^2 + b^2 = c^2 (radius)
	int horizontal = endX - startX;
	int vertical = endY - startY;

	// Get the absolute values
	if (horizontal < 0)
		horizontal *= -1;

	if (vertical < 0)
		vertical *= -1;

	this->radius = floor(sqrt(pow(horizontal, 2) + pow(vertical, 2)));

	canvas->drawCircle(startX, startY, radius, fillColour != NULL);
}

bool Circle::isClicked(int x, int y)
{
	// Image square around the circle
	int leftBoundX = startX - this->radius;
	int rightBoundX = startX + this->radius;
	int downBoundY = startY + this->radius;
	int upBoundY = startY - this->radius;

	return (x >= leftBoundX && x <= rightBoundX)
		&& (y >= upBoundY && y <= downBoundY);
}