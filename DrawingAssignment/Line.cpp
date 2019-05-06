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

	if (this->selected) {
		canvas->setPenColour(EasyGraphics::clDarkGrey, 2);
		canvas->drawLine(startX + 5, startY, endX + 5, endY);
		canvas->drawLine(startX - 5, startY, endX - 5, endY);
	}
}

bool Line::isClicked(int x, int y)
{
	bool isBetweenX, isBetweenY;
	if (startX > endX) {
		isBetweenX = (x <= startX && x >= endX);
	}
	else {
		isBetweenX = (x >= startX && x <= endX);
	}

	if (startY > endY) {
		isBetweenY = (y <= startY && y >= endY);
	}
	else {
		isBetweenY = (y >= startY && y <= endY);
	}

	return isBetweenX && isBetweenY;
}