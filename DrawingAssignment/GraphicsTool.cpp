#include "GraphicsTool.h"
#include <string>

GraphicsTool::GraphicsTool(HINSTANCE hInstance)
{
	// Create the window
	create(hInstance, 800, 800, 40, true);
	this->isLButtonDown = false;
}


GraphicsTool::~GraphicsTool()
{

}

void GraphicsTool::onCreate()
{
	EasyGraphics::onCreate();

	// Set the title of the window
	::SetWindowText(getHWND(), L"Graphics Tool");

	// Create the controls
	controls.push_back(new Control(L"Rectangle", 0, 0, L"icons/rectangle.bmp", true));
	controls.push_back(new Control(L"Circle", 0, 50, L"icons/circle.bmp", true));
	controls.push_back(new Control(L"Line", 0, 100, L"icons/line.bmp", true));

	this->controlsMargin = 50;

}

void GraphicsTool::onDraw()
{
	// Create a white screen
	clrscr(clWhite);

	// Draw the controls
	for (Control* control : controls) {
		control->draw(this);
	}

	// Draw the current drawing
	for (Shape* shape : DrawingSingleton::GetInstance()->getShapes()) {
		shape->draw(this);
	}
}

void GraphicsTool::onLButtonDown(UINT nFlags, int x, int y)
{
	this->isLButtonDown = true;
	
	// Set starting position in case of drag
	this->startX = x;
	this->startY = y;

	// Figure out if the controls are touched or not
	if (x <= this->controlsMargin) {
		for (Control* control : controls) {
			if (control->isClicked(x, y)) {
				control->handleClick();
				this->currentControl = control;
			}
			else
				control->deselect();
		}
	}
	else {
		// On the drawable area
	}
	

	this->onDraw();
}

void GraphicsTool::onLButtonUp(UINT nFlags, int x, int y)
{
	this->isLButtonDown = false;

	// Set the ending position
	this->endX = x;
	this->endY = y;

	// Figure out if the drawable area is clicked or not
	if (x >= this->controlsMargin) {
		// If the control is a shape
		if (this->currentControl->isShapeControl()) {
			// Get the line colour
			int lineColour = EasyGraphics::clBlack;
			// Get the fill colour
			int fillColour = NULL;
			// Save the shape in storage
			DrawingSingleton::GetInstance()->addShape(
				this->currentControl->getName(),
				this->startX,
				this->startY,
				this->endX,
				this->endY,
				lineColour,
				fillColour
			);
		}
	}
	
	this->startX = NULL;
	this->startY = NULL;
	this->endX = NULL;
	this->endY = NULL;

	this->onDraw();
}