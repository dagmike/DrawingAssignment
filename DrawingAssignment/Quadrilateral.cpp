#include "Quadrilateral.h"

Quadrilateral::Quadrilateral(int startX, int startY, int endX, int endY, int lineColour, int fillColour) : Shape(startX, startY, endX, endY, lineColour, fillColour)
{
}


Quadrilateral::~Quadrilateral()
{
}

void Quadrilateral::draw(EasyGraphics* canvas)
{
	canvas->drawRectangle(startX, startY, (endX - startX), (endY - startY), false);
}