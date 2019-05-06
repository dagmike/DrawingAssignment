#pragma once
#include "EasyGraphics.h"
#include <string>

class Control
{
public:
	Control(const wchar_t* name, int x, int y, const wchar_t* iconFilename = NULL);
	~Control();

	void draw(EasyGraphics* canvas) const;
	const wchar_t* getName() const;
	bool isClicked(int clickX, int clickY) const;
	virtual void handleClick();
	void deselect();

private:
	// Position
	int x, y;
	// Size
	static int width, height;
	// Icon
	const wchar_t* iconFilename;
	// Name
	const wchar_t* name;
	// Is the control selected
	bool selected;
};

// Check if the control has been clicked
inline bool Control::isClicked(int clickX, int clickY) const
{
	return (clickX >= x && clickX <= x + width)
		&& (clickY >= y && clickY <= y + height);
}

// Get the name of the control
inline const wchar_t* Control::getName() const
{
	return this->name;
}
