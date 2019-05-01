#pragma once
#include "Shape.h"
class Circle :
	public Shape
{
public:
	Circle(int startX, int startY, int endX, int endY, int lineColour, int fillColour = NULL);
	~Circle();

	void draw(EasyGraphics* canvas);
};

