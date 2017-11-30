#pragma once
#include <windows.h>
#include <windowsx.h>
#include <fstream>
#include <iostream>
#include <string>

// Класс фигуры 'Круг'.
// Позволяет рисовать фигуру в контексте отображения.
// А так же сохранять и загружать данные о фигуре.
//
// Обязательные данные: centerX, centerY, radius
//
// Пример использования:
//	 MyCircle* figure = new MyCircle(130, 200, 100);
//	 figure->save("input.txt");
//	 figure->drowUnpainted(hdc, &rt);
class MyCircle {

private:
	// Центр круга.
	int centerX;
	int centerY;

	// Радиус круга
	int radius;

	// Цвет фигуры
	int r = 255,
		g = 0,
		b = 255;

	// Цвет заливки
	int rFill = 0,
		gFill = 0,
		bFill = 0;

public:
	// Конструктор класса
	MyCircle(int centerX, int centerY, int radius);

	// Загрузка данных о фигуре в файл
	void load(const std::string &fileName);

	// Сохранение данных о фигуре в файл
	void save(const std::string &fileName) const;

	// Рисование незакрашенной фигуры
	void drowUnpainted(HDC hdc, const RECT* rt) const;

	// Рисование закрашенной фигуры
	void drowPainted(HDC hdc, const RECT* rt) const;

	// Проверка, лежит ли фигура в пределе контекста отображения
	int isValid(const RECT* rt) const;

	// Геттеры/сеттеры
	void setCenter(int x, int y);
	void setRadius(int radius);
	void setColor(int r, int g, int b);

	int getCenterX() const;
	int getCenterY() const;
	int getRadius() const;
};