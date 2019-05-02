#include "ColourControl.h"



ColourControl::ColourControl(const wchar_t* name, int x, int y, const wchar_t* iconFilename, int colour, bool isFill) : Control(name, x, y, iconFilename), colour(colour), fillColour(isFill)
{
}


ColourControl::~ColourControl()
{
}
