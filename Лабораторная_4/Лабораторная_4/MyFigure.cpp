#include "MyFigure.h"

void MyFigure::load(const std::string & fileName) {}
void MyFigure::save(const std::string & fileName) const {}

void MyFigure::drowPainted(HDC hdc, const RECT * rt) const {}
void MyFigure::drowUnpainted(HDC hdc, const RECT * rt) const {}

bool MyFigure::isValid(const RECT * rt) const {
	return false;
}


void MyFigure::setColor(int red, int green, int blue) {
	this->red = red;
	this->green = green;
	this->blue = blue;
}


void MyFigure::setFillColor(int redFill, int greenFill, int blueFill) {
	this->redFill = redFill;
	this->greenFill = greenFill;
	this->blueFill = blueFill;
}


void MyFigure::getColor(int &red, int &green, int &blue) const {
	red = this->red;
	green = this->green;
	blue = this->blue;
}


void MyFigure::getFillColor(int &red, int &green, int &blue) const {
	red = this->redFill;
	green = this->greenFill;
	blue = this->blueFill;
}