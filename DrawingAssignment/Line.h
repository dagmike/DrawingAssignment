#pragma once
#include "Shape.h"
class Line :
	public Shape
{
public:
	Line(int startX, int startY, int endX, int endY, int lineColour, int fillColour = NULL);
	~Line();

	void draw(EasyGraphics* canvas);
};

