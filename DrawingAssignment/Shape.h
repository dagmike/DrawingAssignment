#pragma once
#include "EasyGraphics.h"

class Shape
{
public:
	Shape(int startX, int startY, int endX, int endY, int lineColour, int fillColour = NULL);
	~Shape();

	virtual void draw(EasyGraphics* canvas) = 0;
	virtual bool isClicked(int x, int y) = 0;
	void setIsSelected(bool isSelected);
	bool isSelected() const;
	void setEndCoordinates(int endX, int endY);
	void setStartCoordinates(int startX, int startY);
	void moveTo(int x, int y);

	void moveBy(int x, int y);

	int getStartX() const;
	int getStartY() const;
	int getEndX() const;
	int getEndY() const;
	int getLineColour() const;
	int getFillColour() const;
	void setLineColour(int colour);
	void setFillColour(int colour);
protected:
	// Position
	int startX, startY;
	int endX, endY;
	int lineColour;
	int fillColour;
	// State of is selected
	bool selected;
};

inline int Shape::getStartX() const
{
	return startX;
}

inline int Shape::getStartY() const
{
	return startY;
}

inline int Shape::getEndX() const
{
	return endX;
}

inline int Shape::getEndY() const
{
	return endY;
}

inline int Shape::getLineColour() const
{
	return lineColour;
}

inline int Shape::getFillColour() const
{
	return fillColour;
}

inline void Shape::setIsSelected(bool isSelected)
{
	this->selected = isSelected;
}

inline bool Shape::isSelected() const
{
	return this->selected;
}

inline void Shape::setLineColour(int colour)
{
	this->lineColour = colour;
}

inline void Shape::setFillColour(int colour)
{
	this->fillColour = colour;
}