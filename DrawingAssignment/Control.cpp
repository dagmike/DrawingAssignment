#include "Control.h"

int Control::width = 50;
int Control::height = 50;

Control::Control(const wchar_t* name, int x, int y, const wchar_t* iconFilename) : name(name), x(x), y(y), iconFilename(iconFilename)
{
	this->selected = false;
}


Control::~Control()
{
}

// Draw the control
void Control::draw(EasyGraphics* canvas) const
{
	canvas->setPenColour(this->selected ? EasyGraphics::clRed : EasyGraphics::clBlack, 2);
	// Draw a rectangle
	canvas->drawRectangle(this->x, this->y, width, height, false);

	// Draw the bitmap inside
	canvas->drawBitmap(iconFilename, x + 5, y + 5, width - 10, height - 10);
}

void Control::handleClick()
{
	this->selected = !this->selected;
}

void Control::deselect()
{
	this->selected = false;
}