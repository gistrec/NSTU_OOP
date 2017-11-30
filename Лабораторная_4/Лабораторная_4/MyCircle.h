#pragma once
#include "MyFigure.h"

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
class MyCircle : public MyFigure {

private:
	// Центр круга.
	int centerX;
	int centerY;

	// Радиус круга
	int radius;

public:
	// Конструктор класса
	MyCircle(int centerX, int centerY, int radius);

	// Загрузка данных о фигуре в файл
	void load(const std::string &fileName) override;

	// Сохранение данных о фигуре в файл
	void save(const std::string &fileName) const override;

	// Рисование закрашенной фигуры
	void drowPainted(HDC hdc, const RECT* rt) const override;

	// Рисование незакрашенной фигуры
	void drowUnpainted(HDC hdc, const RECT* rt) const override;

	// Проверка, лежит ли фигура в пределе контекста отображения
	bool isValid(const RECT* rt) const override;

	// Геттеры/сеттеры
	void setCenter(int x, int y);
	void setRadius(int radius);

	int getCenterX() const;
	int getCenterY() const;
	int getRadius() const;
};