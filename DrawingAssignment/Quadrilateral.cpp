#include "Quadrilateral.h"

Quadrilateral::Quadrilateral(int startX, int startY, int endX, int endY, int lineColour, int fillColour) : Shape(startX, startY, endX, endY, lineColour, fillColour)
{
}


Quadrilateral::~Quadrilateral()
{
}

void Quadrilateral::draw(EasyGraphics* canvas)
{
	canvas->setPenColour(lineColour, 1);
	canvas->selectBackColour(fillColour);
	canvas->drawRectangle(startX, startY, (endX - startX), (endY - startY), fillColour != NULL);

	if (this->selected) {
		// Draw a rectangle around it to show it is selected
		canvas->setPenColour(EasyGraphics::clDarkGrey, 2);
		canvas->drawRectangle(startX - 5, startY - 5, (endX - startX) + 10, (endY - startY) + 10, false);
	}
}

bool Quadrilateral::isClicked(int x, int y)
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