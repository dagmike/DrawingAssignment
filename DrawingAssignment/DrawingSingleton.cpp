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

void DrawingSingleton::addShape(std::string shapeName, int startX, int startY, int endX, int endY, int lineColour, int fillColour)
{
	if (shapeName == "Rectangle") {
		shapes.push_back(new Rectangle(startX, startY, endX, endY, lineColour, fillColour));
	}
	else if (shapeName == "Circle") {

	}
	else if (shapeName == "Line") {

	}
}