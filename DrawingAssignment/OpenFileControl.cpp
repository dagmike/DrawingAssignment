#include "OpenFileControl.h"



OpenFileControl::OpenFileControl(const wchar_t* name, int x, int y, const wchar_t* iconFilename) : Control(name, x, y, iconFilename)
{
}


OpenFileControl::~OpenFileControl()
{
}

void OpenFileControl::handleClick()
{
	std::string line;
	std::ifstream imageFile("drawing.img.csv");

	if (imageFile.is_open())
	{
		// Remove what is already on the screen
		DrawingSingleton::GetInstance()->clearShapes();

		// Get all the elements from the file
		while (getline(imageFile, line))
		{
			std::vector<std::string> tokens;
			std::istringstream iss(line);
			std::string token;
			// Read the partials into a vector
			while (getline(iss, token, ','))
				tokens.push_back(token);

			// Get the shape name
			std::wstring shapeName(tokens.at(0).length(), L' ');
			std::copy(tokens.at(0).begin(), tokens.at(0).end(), shapeName.begin());

			int startX = std::stoi(tokens.at(1));
			int startY = std::stoi(tokens.at(2));
			int endX = std::stoi(tokens.at(3));
			int endY = std::stoi(tokens.at(4));
			int lineColour = std::stoi(tokens.at(5), nullptr, 0);
			int fillColour = std::stoi(tokens.at(6), nullptr, 0);

			DrawingSingleton::GetInstance()->addShape(
				shapeName.c_str(),
				startX,
				startY,
				endX,
				endY,
				lineColour,
				fillColour
			);
		}
	}
	else {
		std::cout << "Failed to open file";
	}
}
