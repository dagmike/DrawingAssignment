#include "Control.h"

int Control::width = 50;
int Control::height = 50;

Control::Control(int x, int y, wchar_t* iconFilename) : x(x), y(y), iconFilename(iconFilename)
{
}


Control::~Control()
{
}

void Control::draw(EasyGraphics* canvas) const
{

}
