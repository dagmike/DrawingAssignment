#pragma once
#include "Control.h"
class ShapeControl :
	public Control
{
public:
	ShapeControl(const wchar_t* name, int x, int y, const wchar_t* iconFilename);
	~ShapeControl();
};

