#include "Circle.h"
#include <iostream>

// �������� �� �������������� ����� little ����� big
// ��� ������� �� �������� - big ������ �������� little
//
// �������� ������: true - ��������, false - ���
boolean isInclude(const Circle* big, const Circle* little) {
	// ���� ������ ���������� ����� ����� ��� ������, ��� ������ �������� - �� ����� �� ��������
	if (little->getRadius() >= big->getRadius()) return false;

	// distance - ���������� ����� �������� ���� ������
	double distance = sqrt((little->getCenterX() - big->getCenterX()) * (little->getCenterX() - big->getCenterX()) +
	                       (little->getCenterY() - big->getCenterY()) * (little->getCenterY() - big->getCenterY()));
	// ��� ����� ���������� - � �� ���� ��� ������� ��� ��������
	if (big->getRadius() < (little->getRadius() + distance)) return false;
	// ���� �������� ��� �������� - ���������� true
	return true;
}

void main() {
	setlocale(LC_ALL, "Russian");
	// �������� ������������� ����
	HWND hwnd = GetConsoleWindow();
	// �������� �������� �����������
	HDC hdc = GetDC(hwnd);
	RECT rt;
	// �������� ������ ����
	GetClientRect(hwnd, &rt);

	// ��� ��� ������ �������, ���� ����� ��������� ������� ��� //
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
	// ��� ��� ����� �������, ���� ����� ��������� ������� ��� //

	system("pause");
	// ����������� �������� �����������
	ReleaseDC(hwnd, hdc);
}