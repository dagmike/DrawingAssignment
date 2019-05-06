#include "GraphicsTool.h"
#include <string>

GraphicsTool::GraphicsTool(HINSTANCE hInstance)
{
	this->isLButtonDown = false;
	this->setImmediateDrawMode(false);

	// Create the window
	create(hInstance, 800, 864, 40, true);
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
	controls.push_back(new Control(L"Select", 0, 150, L"icons/select.bmp"));
	controls.push_back(new Control(L"Move", 0, 200, L"icons/move.bmp"));
	controls.push_back(new Control(L"Delete", 0, 250, L"icons/delete.bmp"));

	// Add line colour controls
	controls.push_back(new ColourControl(L"LineRed", 0, 325, L"icons/colours/redLine.bmp", EasyGraphics::clRed, false));
	controls.push_back(new ColourControl(L"LineGreen", 0, 375, L"icons/colours/greenLine.bmp", EasyGraphics::clGreen, false));
	controls.push_back(new ColourControl(L"LineBlue", 0, 425, L"icons/colours/blueLine.bmp", EasyGraphics::clBlue, false));

	// Add fill colour controls
	controls.push_back(new ColourControl(L"FillRed", 0, 500, L"icons/colours/redFill.bmp", EasyGraphics::clRed, true));
	controls.push_back(new ColourControl(L"FillGreen", 0, 550, L"icons/colours/greenFill.bmp", EasyGraphics::clGreen, true));
	controls.push_back(new ColourControl(L"FillBlue", 0, 600, L"icons/colours/blueFill.bmp", EasyGraphics::clBlue, true));
	controls.push_back(new ColourControl(L"FillNone", 0, 650, L"icons/colours/noFill.bmp", NULL, true));

	// Add file controls
	controls.push_back(new OpenFileControl(L"OpenFile", 0, 725, L"icons/openFile.bmp"));
	controls.push_back(new SaveFileControl(L"SaveFile", 0, 775, L"icons/saveFile.bmp"));

	// Set default control to rectangle
	this->currentControl = controls.front();
	this->currentControl->handleClick();

	// Set default colours
	this->lineColour = dynamic_cast<ColourControl*>(controls[6]);
	this->lineColour->handleClick();
	this->fillColour = dynamic_cast<ColourControl*>(controls[9]);
	this->fillColour->handleClick();


	this->controlsMargin = 50;
}

void GraphicsTool::drawShape(Shape* shape)
{
	shape->draw(this);
}

void GraphicsTool::drawControl(Control* control)
{
	control->draw(this);
}

void GraphicsTool::onDraw()
{
	// Create a white screen
	clrscr(clWhite);
	
	// Draw the controls
	std::for_each(controls.begin(), controls.end(), std::bind1st(std::mem_fun(&GraphicsTool::drawControl), this));

	// Draw the shapes
	std::vector<Shape*> shapes = DrawingSingleton::GetInstance()->getShapes();
	std::for_each(shapes.begin(), shapes.end(), std::bind1st(std::mem_fun(&GraphicsTool::drawShape), this));

	if (this->errMessage != NULL) {
		// Draw the error message
		this->selectTextColour(EasyGraphics::clDarkRed);
		this->drawText(this->errMessage, 55, 0);
	}

	EasyGraphics::onDraw();
}

void GraphicsTool::onLButtonDown(UINT nFlags, int x, int y)
{
	this->isLButtonDown = true;
	this->errMessage = NULL;

	// Set starting position in case of drag
	this->startX = x;
	this->startY = y;

	// Figure out if the controls are touched or not
	if (x <= this->controlsMargin) {
	
		// Find the control that is clicked
		std::vector<Control*>::iterator selectedControl = std::find_if(controls.begin(), controls.end(), [&x, &y](Control* control)
			{
				return control->isClicked(x, y);
			}
		);

		// Make sure a control has been clicked
		if (selectedControl != controls.end()) {
			Control* control = (*selectedControl);

			// See if it is a colour control
			ColourControl* colourControl = dynamic_cast<ColourControl*>(control);

			if (colourControl == NULL && control != this->currentControl) {
				// Not a colour control
				try {
					control->handleClick();
				}
				catch (const wchar_t* e) {
					this->errMessage = e;
				}

				if (control->getName() != L"OpenFile" && control->getName() != L"SaveFile") {
					// Deselect old control
					this->currentControl->deselect();
					// Set current control
					this->currentControl = control;
				}

				if (this->currentControl->getName() != L"Select" && this->selectedShape != NULL) {
					this->selectedShape->setIsSelected(false);
				}
			}
			else if (colourControl != NULL) {
				int colour = colourControl->getColour();

				if (colourControl->isFill()) {
					this->fillColour->deselect();
					this->fillColour = colourControl;
					this->fillColour->handleClick();
					// If there is a shape selected
					if (this->selectedShape != NULL) {
						// Alter the colour of the shape
						this->selectedShape->setFillColour(colourControl->getColour());
					}
				}
				else {
					this->lineColour->deselect();
					this->lineColour = colourControl;
					this->lineColour->handleClick();
					// If there is a shape selected
					if (this->selectedShape != NULL) {
						// Alter the colour of the shape
						this->selectedShape->setLineColour(colourControl->getColour());
					}
				}
			}
		}
	}
	else {
		// Check if any of the shapes have been clicked
		for (Shape* shape : DrawingSingleton::GetInstance()->getShapes()) {
			if (shape->isClicked(x, y)) {
				if (this->currentControl->getName() == L"Select") {
					if (this->selectedShape != NULL) {
						if (shape == this->selectedShape) {
							// Select the new shape
							shape->setIsSelected(!this->selectedShape->isSelected());
						}
						else {
							// Deselect the old selected shape
							this->selectedShape->setIsSelected(false);
							// Seleect the new shape
							shape->setIsSelected(true);
						}
					}
					else {
						// Select the new shape (no previous selected)
						shape->setIsSelected(true);
					}
				
					// Set the current colour controls to that of the selected shapes colours
					for (Control* control : controls) {
						ColourControl* colourControl = dynamic_cast<ColourControl*>(control);
						if (colourControl != NULL) {
							if (colourControl->isFill()) {
								if (colourControl->getColour() == shape->getFillColour() && this->fillColour != colourControl) {
									this->fillColour->deselect();
									this->fillColour = colourControl;
									// Select the control
									control->handleClick();
								}
								else if (this->fillColour != colourControl) {
									control->deselect();
								}
							}
							else if (colourControl->getColour() == shape->getLineColour() && this->lineColour != colourControl) {
								this->lineColour->deselect();
								this->lineColour = colourControl;
								// Select the control
								control->handleClick();
							}
							else if (this->lineColour != colourControl) {
								control->deselect();
							}
						}
					}
				}
				else {
					shape->setIsSelected(false);
				}

				if (shape->isSelected() || this->currentControl->getName() == L"Move" || this->currentControl->getName() == L"Delete") {
					// This is the selected shape
					this->selectedShape = shape;
				}
				

				// Get position of cursor in respect to the points of the shape
				// for smooth movement when dragging
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

		this->onDraw();
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
			if (latestShape != NULL) {
				// Save the shape in storage
				latestShape->setEndCoordinates(x, y);
			}
		}
		else if (this->currentControl->getName() == L"Move" && this->selectedShape != NULL) {
			// Move the shape with respect to the cursor
			this->selectedShape->setStartCoordinates(x - this->shapeStartXDiff, y - this->shapeStartYDiff);
			this->selectedShape->setEndCoordinates(x + this->shapeEndXDiff, y + this->shapeEndYDiff);
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
			if (latestShape != NULL) {
				latestShape->setEndCoordinates(this->endX, this->endY);
			}
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
	
	// Reset the movement variables
	this->startX = NULL;
	this->startY = NULL;
	this->endX = NULL;
	this->endY = NULL;
}