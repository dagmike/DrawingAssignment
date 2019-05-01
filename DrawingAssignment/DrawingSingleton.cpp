#include "DrawingSingleton.h"

DrawingSingleton* DrawingSingleton::inst = nullptr;

DrawingSingleton* DrawingSingleton::GetInstance()
{
	// If instance doesn't already exist
	if (inst == nullptr) {
		// Create the instance and store it
		inst = new DrawingSingleton();
	}

	// Return the instance
	return inst;
}

DrawingSingleton::~DrawingSingleton()
{

}

void DrawingSingleton::DeleteInstance()
{
	for (Shape* shape : inst->getShapes())
	{
		delete shape;
	}

	delete inst;
}

void DrawingSingleton::addShape(const wchar_t* shapeName, int startX, int startY, int endX, int endY, int lineColour, int fillColour)
{
	if (shapeName == L"Rectangle") {
		shapes.push_back(new Quadrilateral(startX, startY, endX, endY, lineColour, fillColour));
	}
	else if (shapeName == L"Circle") {

	}
	else if (shapeName == L"Line") {

	}
}