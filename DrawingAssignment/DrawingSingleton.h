#pragma once
#include <vector>
#include <string>
#include "Shape.h"
#include "Quadrilateral.h"
#include "Circle.h"
#include "Line.h"

class DrawingSingleton
{
private:
	// Single instance is stored here
	static DrawingSingleton* inst;

	std::vector<Shape*> shapes;

	// Hide so cannot be instantiated
	DrawingSingleton() {}
public:
	~DrawingSingleton();

	void addShape(const wchar_t* shapeName, int startX, int startY, int endX, int endY, int lineColour, int fillColour);
	std::vector<Shape*> getShapes() const;
	Shape* getShape(int i) const;
	void removeShape(int i);

	// Access the single instance
	static DrawingSingleton* GetInstance();


	DrawingSingleton(const DrawingSingleton&) = delete;
	DrawingSingleton& operator=(const DrawingSingleton&) = delete;

	static void DeleteInstance();
};

inline std::vector<Shape*> DrawingSingleton::getShapes() const
{
	return shapes;
}

inline Shape* DrawingSingleton::getShape(int i) const
{
	return shapes[i];
}

inline void DrawingSingleton::removeShape(int i)
{
	delete shapes[i];
	shapes.erase(shapes.begin() + i);
}

