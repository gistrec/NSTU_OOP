#pragma once
#include <windows.h>
#include <windowsx.h>
#include <fstream>

class MyFigure {

private:
	// У каждой фигуры есть цвет контура
	int red   = 245,
		green = 255,
		blue  = 51;

	// У каждой фигуры есть цвет заливки
	int redFill   = 255,
		greenFill = 153,
		blueFill  = 51;

public:
	// Каждую фигуру можно сохранить и загрузить
	// Параметры функции - название файла
	virtual void load(const std::string &fileName);
	virtual void save(const std::string &fileName) const;

	// Каждую фигуру можно нарисовать
	// Параметры функции: hdc и rt
	virtual void drowPainted(HDC hdc, const RECT* rt) const;
	virtual void drowUnpainted(HDC hdc, const RECT* rt) const;

	// У каждой фигуры можно проверить корректность данных
	virtual bool isValid(const RECT* rt) const;

	// У каждой фигуры можно установить цвет контура и заливки
	virtual void setColor(int red, int green, int blue) final;
	virtual void setFillColor(int red, int green, int blue) final;

	// Получаем цвет фигуры через ссылку на цвета
	virtual void getColor(int &red, int &green, int &blue) const final;
	virtual void getFillColor(int &red, int &green, int &blue) const final;
};