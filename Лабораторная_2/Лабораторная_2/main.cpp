#include "Circle.h"
#include <iostream>

// ѕроверка на принадлежность круга little кругу big
//  ак пон€тно из названи€ - big должен включать little
//
// ¬ыходные данные: true - включает, false - нет
boolean isInclude(const Circle* big, const Circle* little) {
	// ≈сли радиус маленького круга равен или больше, чем радиус большого - то точно не включает
	if (little->getRadius() >= big->getRadius()) return false;

	// distance - рассто€ние между центрами двух кругов
	double distance = sqrt((little->getCenterX() - big->getCenterX()) * (little->getCenterX() - big->getCenterX()) +
	                       (little->getCenterY() - big->getCenterY()) * (little->getCenterY() - big->getCenterY()));
	// “ут лучше нарисовать - € не знаю как описать эту проверку
	if (big->getRadius() < (little->getRadius() + distance)) return false;
	// ≈сли проверки все пройдены - возвращаем true
	return true;
}

void main() {
	setlocale(LC_ALL, "Russian");
	// получаем идентификатор окна
	HWND hwnd = GetConsoleWindow();
	// получаем контекст отображени€
	HDC hdc = GetDC(hwnd);
	RECT rt;
	// получаем размер окна
	GetClientRect(hwnd, &rt);

	// ¬от тут начало области, куда нужно вставл€ть рабочий код //
	//////////////////////////////////////////////////////////////
	//
	try {
		Circle* figure1 = new Circle();
		figure1->init(130, 200, 100);

		Circle* figure2 = new Circle();
		figure2->init(-150, 230, 25);

		//isInclude(figure1, figure2);
		figure1->drawPaintedCircle(hdc, &rt);
		figure2->drawUnpaintedCircle(hdc, &rt);
	} catch (std::string &error) {
		std::cout << error.c_str() << std::endl;
	}
	//
	/////////////////////////////////////////////////////////////
	// ¬от тут конец области, куда нужно вставл€ть рабочий код //

	system("pause");
	// освобождаем контекст отображени€
	ReleaseDC(hwnd, hdc);
}