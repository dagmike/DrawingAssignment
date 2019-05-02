#pragma once
#include "Control.h"
class ColourControl :
	public Control
{
public:
	ColourControl(const wchar_t* name, int x, int y, const wchar_t* iconFilename, int colour, bool isFill);
	~ColourControl();

	int getColour() const;
	bool isFill() const;
private:
	int colour;
	bool fillColour;
};

inline int ColourControl::getColour() const
{
	return colour;
}

inline bool ColourControl::isFill() const
{
	return fillColour;
}

