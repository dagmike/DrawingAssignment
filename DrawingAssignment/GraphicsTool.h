#pragma once
#include "EasyGraphics.h"
#include "Control.h"
#include <vector>

class GraphicsTool
	: public EasyGraphics
{
public:
	GraphicsTool(HINSTANCE hInstance);
	~GraphicsTool();

	void onCreate();
	void onDraw();
};

