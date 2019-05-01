#include "Rectangle.h"

Rectangle::Rectangle(int startX, int startY, int endX, int endY, int lineColour, int fillColour) : Shape(startX, startY, endX, endY, lineColour, fillColour)
{
}


Rectangle::~Rectangle()
{
}

void Rectangle::draw(EasyGraphics* canvas)
{
	canvas->drawRectangle(startX, startY, (endX - startX), (endY - startY), false);
}