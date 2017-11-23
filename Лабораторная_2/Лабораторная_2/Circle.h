#pragma once
#include <windows.h>
#include <windowsx.h>
#include <fstream>

// ����� Circle, � ������� ���������� ������ � �����
// ���� ����� ��� � ������ ����, ������ ������ � '���������' ���� �������
//
// � ������������ ����� �� ������ ��������� �������, ���������� ���� � .cpp
class Circle {

// ��������� ����������
// �������� ������ �� ������� ������
// ����� ������������ ������ ������� � �������
private:
	int centerX, centerY; // ����� �����
	int radius; // ������ �����

	int r = 0, g = 255, b = 0; // ���� ����������
	int rFill = 0, gFill = 255, bFill = 0; // ���� �������

public:
	// ������� ��� �������� �������� ����� - �������������
	void init(int centerX, int centerY, int radius);

	void load(const std::string &fileName);

	// ���� ����� ������� ���� const
	// �� ��� ������� �� �������� ������� ���������� � ���� ������
	void save(const std::string &fileName) const;

	void drawUnpaintedCircle(HDC hdc, const RECT* rt) const;

	void drawPaintedCircle(HDC hdc, const RECT* rt) const;

	boolean isCorrect(const RECT* rt) const;

	// �������� ����� ��� ������
	int getCenterX() const;
	int getCenterY() const;
	int getRadius() const;

	// ��������� ������ � �������
	void setCenter(int centerX, int centerY);
	void setRadius(int radius);

	// ��������� ����� � ������� �����
	void setColor(int r, int g, int b);
	void setFillColor(int rFill, int gFill, int bFill);
};