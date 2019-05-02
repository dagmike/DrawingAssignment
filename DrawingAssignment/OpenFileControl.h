#pragma once
#include "Control.h"
#include "DrawingSingleton.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class OpenFileControl :
	public Control
{
public:
	OpenFileControl(const wchar_t* name, int x, int y, const wchar_t* iconFilename = NULL);
	~OpenFileControl();

	void handleClick();
};

