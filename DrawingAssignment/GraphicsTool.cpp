#include "GraphicsTool.h"

GraphicsTool::GraphicsTool(HINSTANCE hInstance)
{
	// Create the window
	create(hInstance, 800, 800, 40, true);
}


GraphicsTool::~GraphicsTool()
{

}

void GraphicsTool::onCreate()
{
	EasyGraphics::onCreate();

	// Set the title of the window
	::SetWindowText(getHWND(), L"Graphics Tool");
}

void GraphicsTool::onDraw()
{
	// Create a white screen
	clrscr(clWhite);
}