#pragma once
#include "MyFigure.h"

class MyRectangle : private MyFigure {

private:
	// Две точки
	int x1, y1;
	int x2, y2;
public:
	// Конструктор класса
	MyRectangle(int x1, int y1, int x2, int y2);

	// Загрузка данных о фигуре в файл
	void load(const std::string &fileName) override;

	// Сохранение данных о фигуре в файл
	void save(const std::string &fileName) const override;

	// Рисование незакрашенной фигуры
	void drowPainted(HDC hdc, const RECT* rt) const override;

	// Рисование закрашенной фигуры
	void drowUnpainted(HDC hdc, const RECT* rt) const override;

	// Проверка, лежит ли фигура в пределе контекста отображения
	bool isValid(const RECT* rt) const override;

	// Геттеры/сеттеры
	void setPoints(int x1, int y1, int x2, int y2);
	void getPoints(int &x1, int &y1, int &x2, int &y2) const;
};