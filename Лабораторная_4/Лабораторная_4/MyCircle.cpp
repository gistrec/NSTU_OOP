#include "MyCircle.h"

MyCircle::MyCircle(int centerX, int centerY, int radius) {
	this->centerX = centerX;
	this->centerY = centerY;
	this->radius = radius;
}

void MyCircle::load(const std::string &fileName) {
	std::ifstream input(fileName);
	if (!input.is_open()) throw std::string("Ошибка: Файл не найден");
	input >> centerX >> centerY >> radius;

	int red, green, blue;
	// Получаем цвет контура фигуры
	input >> red >> green >> blue;
	setColor(red, green, blue);
	// Получаем цвет заливки фигуры
	input >> red >> green >> blue;
	setColor(red, green, blue);
}

// Сохраняем в три строки
void MyCircle::save(const std::string &fileName) const {
	std::ofstream output(fileName);
	output << getCenterX() << " " << getCenterY() << " " << getRadius() << "\n";

	int red, green, blue;
	// Получаем цвет контура фигуры
	getColor(red, green, blue);
	output << red << " " << green << " " << blue << "\n";
	// Получаем цвет заливки фигуры
	getFillColor(red, green, blue);
	output << red << " " << green << " " << blue;
}

void MyCircle::drowUnpainted(HDC hdc, const RECT* rt) const {
	if (!isValid(rt)) throw std::string("Ошибка: Фигура лежит вне границ экрана");
	int red, green, blue;
	// Получаем цвет контура фигуры
	getColor(red, green, blue);
	HPEN pen = SelectPen(hdc, CreatePen(PS_SOLID, 3, RGB(red, green, blue)));
	HBRUSH brush = SelectBrush(hdc, CreateSolidBrush(RGB(0, 0, 0))); // Фон
	Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
	DeletePen(pen);
	DeleteBrush(brush);
}

void MyCircle::drowPainted(HDC hdc, const RECT* rt) const {
	if (!isValid(rt)) throw std::string("Ошибка: Фигура лежит вне границ экрана");
	// Создаем перо и говорим, что будем рисовать этим пером
	int red, green, blue;
	// Получаем цвет контура фигуры
	getColor(red, green, blue);
	HPEN pen = SelectPen(hdc, CreatePen(PS_SOLID, 3, RGB(red, green, blue)));
	getFillColor(red, green, blue);
	HBRUSH brush = SelectBrush(hdc, CreateSolidBrush(RGB(red, green, blue))); // Фон
	Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
	// удаляем красное перо
	DeletePen(pen);
	// удаляем зеленую кисть
	DeleteBrush(brush);
}

bool MyCircle::isValid(const RECT* rt) const {
	if (centerX - radius < 0 || centerY - radius < 0 ||
		centerX + radius > rt->right || centerY + radius > rt->bottom) {
		return false;
	}
	return true;
}

int MyCircle::getCenterX() const {
	return this->centerX;
}

int MyCircle::getCenterY() const {
	return this->centerY;
}

void MyCircle::setCenter(int x, int y) {
	this->centerX = x;
	this->centerY = y;
}

int MyCircle::getRadius() const {
	return this->radius;
}

void MyCircle::setRadius(int radius) {
	if (radius < 0) throw std::string("Ошибка: Радиус должен быть больше нуля");
	this->radius = radius;
}