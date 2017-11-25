#pragma once

#include <algorithm>
#include <iostream>
#include "MyCircle.h"
#include "Container.h"

#define _CRT_SECURE_NO_WARNINGS = false;


void main() {
	setlocale(LC_ALL, "Russian");
	HWND hwnd = GetConsoleWindow(); // Получаем идентификатор окна
	HDC hdc = GetDC(hwnd);  // Получаем контекст отображения
	RECT rt;
	GetClientRect(hwnd, &rt); // Получаем размер окна

	try {
		std::shared_ptr<Container> container = std::make_shared<Container>();

		std::shared_ptr<MyCircle> figure1 = std::make_shared<MyCircle>(130, 200, 100);
		container->addFigure(figure1, 0);

		std::shared_ptr<MyCircle> figure2 = std::make_shared<MyCircle>(150, 230, 40);
		container->addFigure(figure2, 1);

		//list->getElementById(0)->figure->drowPainted(hdc, &rt);
		//list->getElementById(1)->figure->drowUnpainted(hdc, &rt);

		for (auto iter = container->begin(); iter != container->end(); ++iter) {
			std::cout << (*iter).getRadius() << ", ";
		}
		
		//std::sort(list->begin(), list->end(), [](MyCircle a, MyCircle b) { return a.getRadius() < b.getRadius(); });

		//for (auto iter = list->begin(); iter != list->end(); ++iter) {
		//	std::cout << (*iter).getRadius() << ",";
		//}
	}catch (std::string &error) {
		std::cout << error << std::endl;
	}


	std::cout << "\n";
	system("pause");
	ReleaseDC(hwnd, hdc); // освобождаем контекст отображения
}