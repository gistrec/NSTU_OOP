#include <iostream>

#include "PaintedFigure.h"
#include "UnpaintedFigure.h"
#include "TwoFigure.h"


void main() {
	setlocale(LC_ALL, "Russian");
	HWND hwnd = GetConsoleWindow(); // Получаем идентификатор окна
	HDC hdc = GetDC(hwnd);  // Получаем контекст отображения
	RECT rt;
	GetClientRect(hwnd, &rt); // Получаем размер окна

	try {
		
		PaintedFigure* figure1 = new PaintedFigure(130, 200, 40);
		figure1->setFillColor(255, 255, 255);

		system("color F0");
		figure1->draw(hdc, &rt);
		//TwoFigure* twoFigure = new TwoFigure(figure1, 150, 230, 100);
		//twoFigure->draw(hdc, &rt);

	} catch (std::string &error) {
		std::cout << error.c_str() << std::endl;
	}

	std::cout << "\n";
	system("pause");
	ReleaseDC(hwnd, hdc); // освобождаем контекст отображения
}