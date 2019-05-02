#pragma once
#include "EasyGraphics.h"
#include "Control.h"
#include "ColourControl.h"
#include "ShapeControl.h"
#include "Shape.h"
#include <vector>
#include <algorithm>
#include "DrawingSingleton.h"

class GraphicsTool
	: public EasyGraphics
{
public:
	GraphicsTool(HINSTANCE hInstance);
	~GraphicsTool();

	void onCreate();
	void onDraw();
	void onLButtonDown(UINT nFlags, int x, int y);
	void onLButtonUp(UINT nFlags, int x, int y);
	void onMouseMove(UINT nFlags, int x, int y);
private:
	std::vector<Shape*> shapes;
	std::vector<Control*> controls;
	int controlsMargin;
	bool isLButtonDown;
	Control* currentControl;
	Shape* selectedShape;

	ColourControl* lineColour;
	ColourControl* fillColour;

	int startX, startY;
	int endX, endY;
};