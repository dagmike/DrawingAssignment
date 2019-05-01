#pragma once
#include "Shape.h"
class Quadrilateral :
	public Shape
{
public:
	Quadrilateral(int startX, int startY, int endX, int endY, int lineColour, int fillColour = NULL);
	~Quadrilateral();

	void draw(EasyGraphics* canvas);
	bool isClicked(int x, int y);
};
