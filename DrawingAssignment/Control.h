#pragma once
#include "EasyGraphics.h"
#include <string>

class Control
{
public:
	Control(const wchar_t* name, int x, int y, const wchar_t* iconFilename = NULL, bool shapeControl = false);
	~Control();

	void draw(EasyGraphics* canvas) const;
	inline const wchar_t* getName() const;
	inline bool isClicked(int clickX, int clickY) const;
	virtual void handleClick();
	void deselect();
	inline bool isShapeControl() const;


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
	// Is it a shape control
	bool shapeControl;
};

bool Control::isClicked(int clickX, int clickY) const
{
	return (clickX >= x && clickX <= x + width)
		&& (clickY >= y && clickY <= y + height);
}

bool Control::isShapeControl() const
{
	return shapeControl;
}

inline const wchar_t* Control::getName() const
{
	return this->name;
}
