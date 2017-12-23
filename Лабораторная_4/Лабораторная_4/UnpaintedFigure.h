#pragma once
#include "Figure.h"

class UnpaintedFigure : public Figure {

protected:
	int centerX;
	int centerY;

	int radius;

	// У каждой фигуры есть цвет контура
	int red = 245,
		green = 255,
		blue = 51;

public:
	UnpaintedFigure(int centerX, int centerY, int radius) {
		this->centerX = centerX;
		this->centerY = centerY;
		this->radius = radius;
	}

	virtual void draw(HDC hdc, const RECT* rt) const {
		if (!isValid(rt)) throw std::string("Ошибка: Фигура лежит вне границ экрана");
		// Создаем перо и говорим, что будем рисовать этим пером
		int red, green, blue;
		// Получаем цвет контура фигуры
		getColor(red, green, blue);
		HPEN pen = SelectPen(hdc, CreatePen(PS_SOLID, 3, RGB(red, green, blue)));
		HBRUSH brush = SelectBrush(hdc, CreateSolidBrush(RGB(0, 0, 0))); // Фон
		Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
		// удаляем красное перо
		DeletePen(pen);
		// удаляем зеленую кисть
		DeleteBrush(brush);
	}

	// У каждой фигуры можно установить цвет контура
	virtual void setColor(int red, int green, int blue) final {
		this->red = red;
		this->green = green;
		this->blue = blue;
	}

	virtual void getColor(int &red, int &green, int &blue) const final {
		red = this->red;
		green = this->green;
		blue = this->blue;
	}

	virtual void load(const std::string &fileName) override {
		std::ifstream input(fileName);
		if (!input.is_open()) throw std::string("Ошибка: Файл не найден");
		input >> centerX >> centerY >> radius;

		int red, green, blue;
		// Получаем цвет контура фигуры
		input >> red >> green >> blue;
		setColor(red, green, blue);
	}

	// Сохраняем в три строки
	virtual void save(const std::string &fileName) const override {
		std::ofstream output(fileName);
		output << getCenterX() << " " << getCenterY() << " " << getRadius() << "\n";

		int red, green, blue;
		// Получаем цвет контура фигуры
		getColor(red, green, blue);
		output << red << " " << green << " " << blue << "\n";
	}

	bool isValid(const RECT* rt) const {
		if (centerX - radius < 0 || centerY - radius < 0 ||
			centerX + radius > rt->right || centerY + radius > rt->bottom) {
			return false;
		}
		return true;
	}

	int getCenterX() const {
		return this->centerX;
	}

	int getCenterY() const {
		return this->centerY;
	}

	void setCenter(int x, int y) {
		this->centerX = x;
		this->centerY = y;
	}

	int getRadius() const {
		return this->radius;
	}

	void setRadius(int radius) {
		if (radius < 0) throw std::string("Ошибка: Радиус должен быть больше нуля");
		this->radius = radius;
	}
};