#pragma once
#include "Control.h"
#include "DrawingSingleton.h"
#include "Shape.h"
#include "Circle.h"
#include "Line.h"
#include <iostream>
#include <fstream>
class SaveFileControl :
	public Control
{
public:
	SaveFileControl(const wchar_t* name, int x, int y, const wchar_t* iconFilename = NULL);
	~SaveFileControl();

	void handleClick();
};

