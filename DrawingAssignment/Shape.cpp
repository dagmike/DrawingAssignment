#include "Shape.h"



Shape::Shape(int startX, int startY, int endX, int endY, int lineColour, int fillColour) : startX(startX), startY(startY), endX(endX), endY(endY), lineColour(lineColour), fillColour(fillColour), selected(false)
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

void Shape::setEndCoordinates(int endX, int endY)
{
	this->endX = endX;
	this->endY = endY;
}

void Shape::moveBy(int x, int y)
{
	this->startX += x;
	this->startY += y;
	this->endX += x;
	this->endY += y;
}

void Shape::setStartCoordinates(int startX, int startY)
{
	this->startX = startX;
	this->startY = startY;
}