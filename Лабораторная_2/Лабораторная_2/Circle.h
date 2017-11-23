#pragma once
#include <windows.h>
#include <windowsx.h>
#include <fstream>

// Класс Circle, в котором содержатся данные о круге
// Тоже самое что в первой лабе, только теперь в 'структуре' есть функции
//
// В заголовочном файле мы только описываем функции, реализация идет в .cpp
class Circle {

// Приватные переменные
// Доступны только из функций класса
// Извне использовать только геттеры и сеттеры
private:
	int centerX, centerY; // Центр круга
	int radius; // Радиус круга

	int r = 0, g = 255, b = 0; // Цвет окружности
	int rFill = 0, gFill = 255, bFill = 0; // Цвет заливки

public:
	// Функция для быстрого создания круга - инициализация
	void init(int centerX, int centerY, int radius);

	void load(const std::string &fileName);

	// Если после функции идет const
	// То эта функция не изменяет никаких переменных в этом классе
	void save(const std::string &fileName) const;

	void drawUnpaintedCircle(HDC hdc, const RECT* rt) const;

	void drawPaintedCircle(HDC hdc, const RECT* rt) const;

	boolean isCorrect(const RECT* rt) const;

	// Получить центр или радиус
	int getCenterX() const;
	int getCenterY() const;
	int getRadius() const;

	// Установка центра и радиуса
	void setCenter(int centerX, int centerY);
	void setRadius(int radius);

	// Установка цвета и заливки круга
	void setColor(int r, int g, int b);
	void setFillColor(int rFill, int gFill, int bFill);
};