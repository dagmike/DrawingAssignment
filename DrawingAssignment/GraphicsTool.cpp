#include "GraphicsTool.h"
#include <string>

GraphicsTool::GraphicsTool(HINSTANCE hInstance)
{
	// Create the window
	create(hInstance, 800, 800, 40, true);
	this->isLButtonDown = false;
	this->setImmediateDrawMode(true);
}


GraphicsTool::~GraphicsTool()
{

}

void GraphicsTool::onCreate()
{
	EasyGraphics::onCreate();

	// Set the title of the window
	::SetWindowText(getHWND(), L"Graphics Tool");

	// Create the controls
	controls.push_back(new Control(L"Rectangle", 0, 0, L"icons/rectangle.bmp", true));
	controls.push_back(new Control(L"Circle", 0, 50, L"icons/circle.bmp", true));
	controls.push_back(new Control(L"Line", 0, 100, L"icons/line.bmp", true));
	controls.push_back(new Control(L"Move", 0, 150, L"icons/move.bmp"));
	controls.push_back(new Control(L"Delete", 0, 200, L"icons/delete.bmp"));

	// Add line colour controls
	controls.push_back(new ColourControl(L"LineRed", 0, 275, L"icons/colours/redLine.bmp", EasyGraphics::clRed, false));
	controls.push_back(new ColourControl(L"LineGreen", 0, 325, L"icons/colours/greenLine.bmp", EasyGraphics::clGreen, false));
	controls.push_back(new ColourControl(L"LineBlue", 0, 375, L"icons/colours/blueLine.bmp", EasyGraphics::clBlue, false));
	// Add fill colour controls
	controls.push_back(new ColourControl(L"FillRed", 0, 450, L"icons/colours/redFill.bmp", EasyGraphics::clRed, true));
	controls.push_back(new ColourControl(L"FillGreen", 0, 500, L"icons/colours/greenFill.bmp", EasyGraphics::clGreen, true));
	controls.push_back(new ColourControl(L"FillBlue", 0, 550, L"icons/colours/blueFill.bmp", EasyGraphics::clBlue, true));
	controls.push_back(new ColourControl(L"FillNone", 0, 600, L"icons/colours/noFill.bmp", NULL, true));


	// Set default control to rectangle
	this->currentControl = controls.front();
	this->currentControl->handleClick();

	// Set default colours
	this->lineColour = dynamic_cast<ColourControl*>(controls[5]);
	this->lineColour->handleClick();
	this->fillColour = dynamic_cast<ColourControl*>(controls[8]);
	this->fillColour->handleClick();


	this->controlsMargin = 50;
}

void GraphicsTool::onDraw()
{
	// Create a white screen
	clrscr(clWhite);

	// Draw the controls
	for (Control* control : controls) {
		control->draw(this);
	}

	// Draw the current drawing
	for (Shape* shape : DrawingSingleton::GetInstance()->getShapes()) {
		shape->draw(this);
	}
}

void GraphicsTool::onLButtonDown(UINT nFlags, int x, int y)
{
	this->isLButtonDown = true;
	
	// Set starting position in case of drag
	this->startX = x;
	this->startY = y;

	// Figure out if the controls are touched or not
	if (x <= this->controlsMargin) {
		for (Control* control : controls) {
			if (control->isClicked(x, y)) {
				// See if it is a colour control
				ColourControl* colourControl = dynamic_cast<ColourControl*>(control);
				
				if (colourControl == NULL && control != this->currentControl) {
					// Not a colour control
					control->handleClick();
					// Deselect old control
					this->currentControl->deselect();
					// Set current control
					this->currentControl = control;
				}
				else if (colourControl != NULL) {
					int colour = colourControl->getColour();
					

					if (colourControl->isFill()) {
						this->fillColour->deselect();
						this->fillColour = colourControl;
					}
					else {
						this->lineColour->deselect();
						this->lineColour = colourControl;
					}

					control->handleClick();
				}
			}
		}
	}
	else {
		// Check if any of the shapes have been clicked
		for (Shape* shape : DrawingSingleton::GetInstance()->getShapes()) {
			if (shape->isClicked(x, y)) {
				// This is the selected shape
				this->selectedShape = shape;
			}
		}
	}

	this->onDraw();
}

void GraphicsTool::onLButtonUp(UINT nFlags, int x, int y)
{
	this->isLButtonDown = false;

	// Set the ending position
	this->endX = x;
	this->endY = y;

	// Figure out if the drawable area is clicked or not
	if (x >= this->controlsMargin) {
		// If the control is a shape
		if (this->currentControl->isShapeControl()) {
			// Save the shape in storage
			DrawingSingleton::GetInstance()->addShape(
				this->currentControl->getName(),
				this->startX,
				this->startY,
				this->endX,
				this->endY,
				this->lineColour->getColour(),
				this->fillColour->getColour()
			);
		}
		else if (this->currentControl->getName() == L"Move" && this->selectedShape != NULL) {
			// Move that shape to a diff position
			this->selectedShape->moveTo(x, y);
			this->selectedShape = NULL;
		}
		else if (this->currentControl->getName() == L"Delete" && this->selectedShape != NULL) {
			// Check if any of the shapes have been clicked
			DrawingSingleton* data = DrawingSingleton::GetInstance();

			for (int i = 0; i < data->getShapes().size(); i++) {
				if (this->selectedShape == data->getShape(i)) {
					data->removeShape(i);
				}
			}
		}
	}
	
	this->startX = NULL;
	this->startY = NULL;
	this->endX = NULL;
	this->endY = NULL;

	this->onDraw();
}