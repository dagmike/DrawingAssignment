#include "Line.h"

Line::Line(int startX, int startY, int endX, int endY, int lineColour, int fillColour) : Shape(startX, startY, endX, endY, lineColour, fillColour)
{
}


Line::~Line()
{
}

void Line::draw(EasyGraphics* canvas)
{
	canvas->setPenColour(lineColour, 1);
	canvas->drawLine(startX, startY, endX, endY);
}

bool Line::isClicked(int x, int y)
{
	return (x >= startX && x <= endX)
		&& (y >= startY && y <= endY);
}