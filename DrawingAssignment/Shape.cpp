#include "Shape.h"



Shape::Shape(int startX, int startY, int endX, int endY, int lineColour, int fillColour) : startX(startX), startY(startY), endX(endX), endY(endY), lineColour(lineColour), fillColour(fillColour)
{
}


Shape::~Shape()
{
}

void Shape::moveTo(int x, int y)
{
	// Get diff from original
	int xDiff = x - startX;
	int yDiff = y - startY;

	this->startX = x;
	this->startY = y;

	this->endX = this->endX + xDiff;
	this->endY = this->endY + yDiff;
}