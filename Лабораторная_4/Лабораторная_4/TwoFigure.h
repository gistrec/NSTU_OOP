#pragma once
#include "PaintedFigure.h"

class TwoFigure : public PaintedFigure {
private:
	Figure* figure;	

public:
	TwoFigure(Figure* figure, int centerX, int centerY, int radius) :
		PaintedFigure(centerX, centerY, radius) {
		this->figure = figure;
	}

	Figure* getFigure() {
		return figure;
	}

	void draw(HDC hdc, const RECT* rt) {
		if (!isValid(rt)) throw std::string("������: ������ ����� ��� ������ ������");
		// ������� ���� � �������, ��� ����� �������� ���� �����
		int red, green, blue;
		// �������� ���� ������� ������
		getColor(red, green, blue);
		HPEN pen = SelectPen(hdc, CreatePen(PS_SOLID, 3, RGB(255, 241, 0)));
		HBRUSH brush = SelectBrush(hdc, CreateSolidBrush(RGB(255, 255, 0))); // ���
		Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
		// ������� ������� ����
		DeletePen(pen);
		// ������� ������� �����
		DeleteBrush(brush);
		figure->draw(hdc, rt);
	}

};