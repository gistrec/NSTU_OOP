#include "MyRectangle.h"

MyRectangle::MyRectangle(int x1, int y1, int x2, int y2) {
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}

void MyRectangle::load(const std::string & fileName) {
	std::ifstream input(fileName);
	if (!input.is_open()) throw std::string("Ошибка: Файл не найден");
	input >> x1 >> y1 >> x2 >> y2;

	int red, green, blue;
	// Получаем цвет контура фигуры
	input >> red >> green >> blue;
	setColor(red, green, blue);
	// Получаем цвет заливки фигуры
	input >> red >> green >> blue;
	setColor(red, green, blue);
}

void MyRectangle::save(const std::string & fileName) const {
	std::ofstream output(fileName);
	output << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";

	int red, green, blue;
	// Получаем цвет контура фигуры
	getColor(red, green, blue);
	output << red << " " << green << " " << blue << "\n";
	// Получаем цвет заливки фигуры
	getFillColor(red, green, blue);
	output << red << " " << green << " " << blue;
}

void MyRectangle::drowPainted(HDC hdc, const RECT * rt) const {
	if (!isValid(rt)) throw std::string("Ошибка: Фигура лежит вне границ экрана");
	// Создаем перо и говорим, что будем рисовать этим пером
	int red, green, blue;
	// Получаем цвет контура фигуры
	getColor(red, green, blue);
	HPEN pen = SelectPen(hdc, CreatePen(PS_SOLID, 3, RGB(red, green, blue)));
	getFillColor(red, green, blue);
	HBRUSH brush = SelectBrush(hdc, CreateSolidBrush(RGB(red, green, blue))); // Фон
	Rectangle(hdc, x1, y1, x2, y2);
	// удаляем красное перо
	DeletePen(pen);
	// удаляем зеленую кисть
	DeleteBrush(brush);
}


void MyRectangle::drowUnpainted(HDC hdc, const RECT * rt) const {
	if (!isValid(rt)) throw std::string("Ошибка: Фигура лежит вне границ экрана");
	int red, green, blue;
	// Получаем цвет контура фигуры
	getColor(red, green, blue);
	HPEN pen = SelectPen(hdc, CreatePen(PS_SOLID, 3, RGB(red, green, blue)));
	HBRUSH brush = SelectBrush(hdc, CreateSolidBrush(RGB(0, 0, 0))); // Фон
	Rectangle(hdc, x1, y1, x2, y2);
	DeletePen(pen);
	DeleteBrush(brush);
}


bool MyRectangle::isValid(const RECT* rt) const {
	return true;
}

void MyRectangle::setPoints(int x1, int y1, int x2, int y2) {
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}

void MyRectangle::getPoints(int &x1, int &y1, int &x2, int &y2) const {
	x1 = this->x1;
	y1 = this->y1;
	x2 = this->x2;
	y2 = this->y2;
}