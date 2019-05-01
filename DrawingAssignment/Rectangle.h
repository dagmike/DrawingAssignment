#pragma once
#include "Shape.h"
class Rectangle :
	public Shape
{
public:
	Rectangle(int startX, int startY, int endX, int endY, int lineColour, int fillColour = NULL);
	~Rectangle();

	void draw(EasyGraphics* canvas);	
};

