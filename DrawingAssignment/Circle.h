#pragma once
#include "Shape.h"
#include <math.h>
class Circle :
	public Shape
{
public:
	Circle(int startX, int startY, int endX, int endY, int lineColour, int fillColour = NULL);
	~Circle();

	void draw(EasyGraphics* canvas);
	bool isClicked(int x, int y);

private:
	int radius;
};

