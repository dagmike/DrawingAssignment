#pragma once
#include "EasyGraphics.h"

class Control
{
public:
	Control(int x, int y, wchar_t* iconFilename = NULL);
	~Control();

	void draw(EasyGraphics* canvas) const;
	inline bool isClicked(int clickX, int clickY) const;

private:
	// Position
	int x, y;
	// Size
	static int width, height;
	// Icon
	wchar_t* iconFilename;
};

bool Control::isClicked(int clickX, int clickY) const
{
	return (clickX >= x && clickX <= x + width)
		&& (clickY >= y && clickY <= y + height);
}

