#pragma once
#include <windows.h>
#include <windowsx.h>
#include <fstream>

class Figure {

public:
	// Каждую фигуру можно сохранить и загрузить
	// Параметры функции - название файла
	virtual void load(const std::string &fileName) = 0;
	virtual void save(const std::string &fileName) const = 0;

	// У каждой фигуры можно проверить корректность данных
	virtual bool isValid(const RECT* rt) const = 0;

	// Каждую фигуру можно нарисовать
	virtual void draw(HDC hdc, const RECT* rt) const = 0;
};