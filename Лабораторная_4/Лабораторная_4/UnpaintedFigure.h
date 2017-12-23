#pragma once
#include "Figure.h"

class UnpaintedFigure : public Figure {

protected:
	int centerX;
	int centerY;

	int radius;

	// � ������ ������ ���� ���� �������
	int red = 245,
		green = 255,
		blue = 51;

public:
	UnpaintedFigure(int centerX, int centerY, int radius) {
		this->centerX = centerX;
		this->centerY = centerY;
		this->radius = radius;
	}

	virtual void draw(HDC hdc, const RECT* rt) const {
		if (!isValid(rt)) throw std::string("������: ������ ����� ��� ������ ������");
		// ������� ���� � �������, ��� ����� �������� ���� �����
		int red, green, blue;
		// �������� ���� ������� ������
		getColor(red, green, blue);
		HPEN pen = SelectPen(hdc, CreatePen(PS_SOLID, 3, RGB(red, green, blue)));
		HBRUSH brush = SelectBrush(hdc, CreateSolidBrush(RGB(0, 0, 0))); // ���
		Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
		// ������� ������� ����
		DeletePen(pen);
		// ������� ������� �����
		DeleteBrush(brush);
	}

	// � ������ ������ ����� ���������� ���� �������
	virtual void setColor(int red, int green, int blue) final {
		this->red = red;
		this->green = green;
		this->blue = blue;
	}

	virtual void getColor(int &red, int &green, int &blue) const final {
		red = this->red;
		green = this->green;
		blue = this->blue;
	}

	virtual void load(const std::string &fileName) override {
		std::ifstream input(fileName);
		if (!input.is_open()) throw std::string("������: ���� �� ������");
		input >> centerX >> centerY >> radius;

		int red, green, blue;
		// �������� ���� ������� ������
		input >> red >> green >> blue;
		setColor(red, green, blue);
	}

	// ��������� � ��� ������
	virtual void save(const std::string &fileName) const override {
		std::ofstream output(fileName);
		output << getCenterX() << " " << getCenterY() << " " << getRadius() << "\n";

		int red, green, blue;
		// �������� ���� ������� ������
		getColor(red, green, blue);
		output << red << " " << green << " " << blue << "\n";
	}

	bool isValid(const RECT* rt) const {
		if (centerX - radius < 0 || centerY - radius < 0 ||
			centerX + radius > rt->right || centerY + radius > rt->bottom) {
			return false;
		}
		return true;
	}

	int getCenterX() const {
		return this->centerX;
	}

	int getCenterY() const {
		return this->centerY;
	}

	void setCenter(int x, int y) {
		this->centerX = x;
		this->centerY = y;
	}

	int getRadius() const {
		return this->radius;
	}

	void setRadius(int radius) {
		if (radius < 0) throw std::string("������: ������ ������ ���� ������ ����");
		this->radius = radius;
	}
};