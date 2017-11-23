#pragma once
#include <windows.h>
#include <windowsx.h>
#include <fstream>
#include <iostream>
#include <string>

// ����� ������ '����'.
// ��������� �������� ������ � ��������� �����������.
// � ��� �� ��������� � ��������� ������ � ������.
//
// ������������ ������: centerX, centerY, radius
//
// ������ �������������:
//	 MyCircle* figure = new MyCircle(130, 200, 100);
//	 figure->save("input.txt");
//	 figure->drowUnpainted(hdc, &rt);
class MyCircle {

private:
	// ����� �����.
	int centerX;
	int centerY;

	// ������ �����
	int radius;

	// ���� ������
	int r = 255,
		g = 0,
		b = 255;

	// ���� �������
	int rFill = 0,
		gFill = 0,
		bFill = 0;

public:
	// ����������� ������
	MyCircle(int centerX, int centerY, int radius);

	// �������� ������ � ������ � ����
	void load(const std::string &fileName);

	// ���������� ������ � ������ � ����
	void save(const std::string &fileName) const;

	// ��������� ������������� ������
	void drowUnpainted(HDC hdc, const RECT* rt) const;

	// ��������� ����������� ������
	void drowPainted(HDC hdc, const RECT* rt) const;

	// ��������, ����� �� ������ � ������� ��������� �����������
	int isValid(const RECT* rt) const;

	// �������/�������
	void setCenter(int x, int y);
	void setRadius(int radius);
	void setColor(int r, int g, int b);

	int getCenterX() const;
	int getCenterY() const;
	int getRadius() const;
};