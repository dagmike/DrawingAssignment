#include "GraphicsTool.h"
#include <string>

GraphicsTool::GraphicsTool(HINSTANCE hInstance)
{
	this->isLButtonDown = false;
	this->setImmediateDrawMode(false);

	// Create the window
	create(hInstance, 800, 800, 40, true);
}


GraphicsTool::~GraphicsTool()
{
	// Tidy up the controls
	for (Control* control : controls) {
		delete control;
	}

	controls.clear();

	DrawingSingleton::DeleteInstance();
}

void GraphicsTool::onCreate()
{
	EasyGraphics::onCreate();

	// Set the title of the window
	::SetWindowText(getHWND(), L"Graphics Tool");

	// Create the controls
	controls.push_back(new ShapeControl(L"Rectangle", 0, 0, L"icons/rectangle.bmp"));
	controls.push_back(new ShapeControl(L"Circle", 0, 50, L"icons/circle.bmp"));
	controls.push_back(new ShapeControl(L"Line", 0, 100, L"icons/line.bmp"));
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

	EasyGraphics::onDraw();
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

				this->shapeStartXDiff = x - shape->getStartX();
				this->shapeStartYDiff = y - shape->getStartY();
				this->shapeEndXDiff = shape->getEndX() - x;
				this->shapeEndYDiff = shape->getEndY() - y;
			}
		}

		ShapeControl* shapeControl = dynamic_cast<ShapeControl*>(this->currentControl);
		if (shapeControl != NULL) {
			// Create a base shape so we can edit it
			DrawingSingleton::GetInstance()->addShape(
				shapeControl->getName(),
				this->startX,
				this->startY,
				this->startX,
				this->startY,
				this->lineColour->getColour(),
				this->fillColour->getColour()
			);
		}
	}
}

void GraphicsTool::onMouseMove(UINT nFlags, int x, int y)
{
	if (this->isLButtonDown && x >= this->controlsMargin) {
		// Dragging something
		ShapeControl* shapeControl = dynamic_cast<ShapeControl*>(this->currentControl);
		// If the control is a shape
		if (shapeControl != NULL) {
			// Get the latest shape
			Shape* latestShape = DrawingSingleton::GetInstance()->getLatestShape();
			// Save the shape in storage
			latestShape->setEndCoordinates(x, y);
		}
		else if (this->currentControl->getName() == L"Move" && this->selectedShape != NULL) {
			int xDiff = 0;
			

			int yDiff = 0;
			
			this->selectedShape->setStartCoordinates(x - this->shapeStartXDiff, y - this->shapeStartYDiff);
			this->selectedShape->setEndCoordinates(x + this->shapeEndXDiff, y + this->shapeEndYDiff);
			// Move that shape to a diff position
			// this->selectedShape->moveBy(xDiff, yDiff);
		}
		this->onDraw();
	}
}

void GraphicsTool::onLButtonUp(UINT nFlags, int x, int y)
{
	this->isLButtonDown = false;
	// Set the ending position
	this->endX = x;
	this->endY = y;

	// Figure out if the drawable area is clicked or not
	if (x >= this->controlsMargin) {
		ShapeControl* shapeControl = dynamic_cast<ShapeControl*>(this->currentControl);
		// If the control is a shape
		if (shapeControl != NULL) {
			Shape* latestShape = DrawingSingleton::GetInstance()->getLatestShape();
			latestShape->setEndCoordinates(this->endX, this->endY);
		}
		else if (this->currentControl->getName() == L"Move" && this->selectedShape != NULL) {
			// Move that shape to a diff position
			this->selectedShape->setStartCoordinates(x - this->shapeStartXDiff, y - this->shapeStartYDiff);
			this->selectedShape->setEndCoordinates(x + this->shapeEndXDiff, y + this->shapeEndYDiff);
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

	this->onDraw();
	
	this->startX = NULL;
	this->startY = NULL;
	this->endX = NULL;
	this->endY = NULL;
}