#include "SaveFileControl.h"



SaveFileControl::SaveFileControl(const wchar_t* name, int x, int y, const wchar_t* iconFilename) : Control(name, x, y, iconFilename)
{
}


SaveFileControl::~SaveFileControl()
{
}

void SaveFileControl::handleClick()
{
	// Open a file
	std::ofstream drawingFile;
	drawingFile.open("drawing.img.csv");

	if (drawingFile) {
		for (Shape* shape : DrawingSingleton::GetInstance()->getShapes()) {
			// Get the shape name as a string
			std::string shapeName("Rectangle");
			if (Circle* circle = dynamic_cast<Circle*>(shape)) {
				shapeName = "Circle";
			}
			else if (Line* line = dynamic_cast<Line*>(shape)) {
				shapeName = "Line";
			}

			// Get hex string of the line colour
			std::stringstream lineStream;
			lineStream << std::hex << shape->getLineColour();

			std::stringstream fillStream;
			fillStream << std::hex << shape->getFillColour();

			drawingFile << shapeName << "," << shape->getStartX() << "," << shape->getStartY() << "," << shape->getEndX() << "," << shape->getEndY() << "," << lineStream.str() << "," << fillStream.str();
			drawingFile << "\n";
		}

		drawingFile.close();
	}
	else {
		throw "Unable to open file.";
	}
	

}