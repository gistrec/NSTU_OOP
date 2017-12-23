#pragma once
#include "UnpaintedFigure.h"
#include "Painted.h"

class PaintedFigure : public UnpaintedFigure, public Painted {
public:
	PaintedFigure(int centerX, int centerY, int radius,
				  int redFill = 245, int greenFill = 255, int blueFill = 51) :
						UnpaintedFigure(centerX, centerY, radius),
						Painted(redFill, greenFill, blueFill) {
	}

	// Рисование закрашенной фигуры
	void draw(HDC hdc, const RECT* rt) const override {
		if (!isValid(rt)) throw std::string("Ошибка: Фигура лежит вне границ экрана");
		// Создаем перо и говорим, что будем рисовать этим пером
		int red, green, blue;
		// Получаем цвет контура фигуры
		getColor(red, green, blue);
		HPEN pen = SelectPen(hdc, CreatePen(PS_SOLID, 3, RGB(red, green, blue)));
		getFillColor(red, green, blue);
		HBRUSH brush = SelectBrush(hdc, CreateSolidBrush(RGB(redFill, greenFill, blueFill))); // Фон
		Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
		// удаляем красное перо
		DeletePen(pen);
		// удаляем зеленую кисть
		DeleteBrush(brush);
	}

	virtual void load(const std::string &fileName) {
		std::ifstream input(fileName);
		if (!input.is_open()) throw std::string("Ошибка: Файл не найден");
		input >> centerX >> centerY >> radius;

		int red, green, blue;
		// Получаем цвет контура фигуры
		input >> red >> green >> blue;
		setColor(red, green, blue);
		input >> red >> green >> blue;
		setFillColor(red, green, blue);
	}

	// Сохраняем в три строки
	virtual void save(const std::string &fileName) const {
		std::ofstream output(fileName);
		output << getCenterX() << " " << getCenterY() << " " << getRadius() << "\n";

		int red, green, blue;
		// Получаем цвет контура фигуры
		getColor(red, green, blue);
		output << red << " " << green << " " << blue << "\n";
		getFillColor(red, green, blue);
		output << red << " " << green << " " << blue << "\n";
	}


};