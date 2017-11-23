#include "Circle.h"


void Circle::init(int centerX, int centerY, int radius) {
	this->centerX = centerX;
	this->centerY = centerY;
	this->radius = radius;
}


void Circle::load(const std::string &fileName) {
	// Чтение файла
	std::ifstream input(fileName);
	// Если файл не открыт (не найден) - возвразаем NULL
	if (!input.is_open()) throw std::string("Ошибка, файл не найден");
	// Сохраняем все данные
	// На первой строке - центр и радиус, на второй - цвет окружности, на третьей - цвет заливки
	input >> centerX >> centerY >> radius;
	input >> r >> g >> b;
	input >> rFill >> gFill >> bFill;
}


void Circle::save(const std::string &fileName) const {
	std::ofstream output(fileName); // Создаем файл
	// Сохраняем все данные
	// На первой строке - центр и радиус, на второй - цвет окружности, на третьей - цвет заливки
	output << centerX << " " << centerY << " " << radius << "\n";
	output << r << " " << g << " " << b << "\n";
	output << rFill << " " << gFill << " " << bFill;
}

boolean Circle::isCorrect(const RECT* rt) const {
	// Проверка на 'нулевой радиус'
	if (radius <= 0) throw std::string("Ошибка, у круга отрицательный радиус");
	// Проверка на принадлежность окну
	// Если верх или лево круга 'вылазят' за контекст отображения
	if ((centerX - radius) < 0 || (centerY - radius) < 0 ||
		// Если низ или право 'вылазят' за контекст отображения
		(centerX + radius > rt->right) || (centerY + radius) > rt->bottom) {
		throw std::string("Ошибка, круг вылазит за контект отображения\n");
	}
	// Если все проверки пройдены - возвращаем true
	return true;
}





void Circle::drawUnpaintedCircle(HDC hdc, const RECT* rt) const {
	// Если данные у круга неккоректны - выходим из функции
	if (!isCorrect(rt)) return;
	// Создаем перо и кисть
	HPEN pen = SelectPen(hdc, CreatePen(PS_SOLID, 1, RGB(r, g, b)));
	HBRUSH brush = SelectBrush(hdc, CreateSolidBrush(RGB(0, 0, 0))); // Фон у нас RGB(0,0,0) т.к. незакрушенная фигура
	// Вызываем функцию для рисования круга
	// Входные данные - hdc, две противоположные точки у эллипса
	Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
	// удаляем кисть и перо, чтобы освободить память
	DeletePen(pen);
	DeleteBrush(brush);
}

void Circle::drawPaintedCircle(HDC hdc, const RECT* rt) const {
	// Если данные у круга неккоректны - выходим из функции
	if (!isCorrect(rt)) return;
	// Создаем перо и кисть
	HPEN pen = SelectPen(hdc, CreatePen(PS_SOLID, 1, RGB(r, g, b)));
	HBRUSH brush = SelectBrush(hdc, CreateSolidBrush(RGB(rFill, gFill, bFill))); // Фон
	Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
	// удаляем кисть и перо, чтобы освободить память
	DeletePen(pen);
	DeleteBrush(brush);
}

//
// Дальше идет геттеры - с помощью них можно получить значение переменных в классе круга
//
int Circle::getCenterX() const {
	return centerX;
}

int Circle::getCenterY() const {
	return centerY;
}

int Circle::getRadius() const	{
	return radius;
}

//
// Дальше идут сеттеры - с помощью них устанавливаем значения в классе круга
//
void Circle::setCenter(int centerX, int centerY) {
	this->centerX = centerX;
	this->centerY = centerY;
}

void Circle::setRadius(int radius) {
	this->radius = radius;
}

void Circle::setColor(int r, int g, int b) {
	this->r = r;
	this->g = g;
	this->b = b;
}

void Circle::setFillColor(int rFill, int gFill, int bFill) {
	this->rFill = rFill;
	this->gFill = gFill;
	this->bFill = bFill;
}