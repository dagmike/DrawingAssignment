#pragma once
#include "EasyGraphics.h"

class Shape
{
public:
	Shape(int startX, int startY, int endX, int endY, int lineColour, int fillColour = NULL);
	~Shape();

	virtual void draw(EasyGraphics* canvas) = 0;	

protected:
	// Position
	int startX, startY;
	int endX, endY;
	int lineColour;
	int fillColour;
};

