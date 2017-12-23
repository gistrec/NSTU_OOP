#pragma once

class Painted {

protected:
	// У каждой фигуры есть цвет заливки
	// У незакрашенной - все по нулям
	int redFill,
		greenFill,
		blueFill;

public:
	Painted(int redFill, int greenFill, int blueFill) {
		this->redFill = redFill;
		this->greenFill = greenFill;
		this->blueFill = blueFill;
	}

	// У каждой фигуры можно установить цвет контура и заливки
	void setFillColor(int red, int green, int blue) {
		this->redFill = red;
		this->greenFill = green;
		this->blueFill = blue;
	}

	// Получаем цвет фигуры через ссылку на цвета
	void getFillColor(int &red, int &green, int &blue) const {
		red = this->redFill;
		green = this->greenFill;
		blue = this->blueFill;
	}
};