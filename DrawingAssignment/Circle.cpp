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
	canvas->drawCircle(startX, startY, (startX - endX), false);
}