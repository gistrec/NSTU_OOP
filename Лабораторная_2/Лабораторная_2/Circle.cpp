#include "Circle.h"


void Circle::init(int centerX, int centerY, int radius) {
	this->centerX = centerX;
	this->centerY = centerY;
	this->radius = radius;
}


void Circle::load(const std::string &fileName) {
	// ������ �����
	std::ifstream input(fileName);
	// ���� ���� �� ������ (�� ������) - ���������� NULL
	if (!input.is_open()) throw std::string("������, ���� �� ������");
	// ��������� ��� ������
	// �� ������ ������ - ����� � ������, �� ������ - ���� ����������, �� ������� - ���� �������
	input >> centerX >> centerY >> radius;
	input >> r >> g >> b;
	input >> rFill >> gFill >> bFill;
}


void Circle::save(const std::string &fileName) const {
	std::ofstream output(fileName); // ������� ����
	// ��������� ��� ������
	// �� ������ ������ - ����� � ������, �� ������ - ���� ����������, �� ������� - ���� �������
	output << centerX << " " << centerY << " " << radius << "\n";
	output << r << " " << g << " " << b << "\n";
	output << rFill << " " << gFill << " " << bFill;
}

boolean Circle::isCorrect(const RECT* rt) const {
	// �������� �� '������� ������'
	if (radius <= 0) throw std::string("������, � ����� ������������� ������");
	// �������� �� �������������� ����
	// ���� ���� ��� ���� ����� '�������' �� �������� �����������
	if ((centerX - radius) < 0 || (centerY - radius) < 0 ||
		// ���� ��� ��� ����� '�������' �� �������� �����������
		(centerX + radius > rt->right) || (centerY + radius) > rt->bottom) {
		throw std::string("������, ���� ������� �� ������� �����������\n");
	}
	// ���� ��� �������� �������� - ���������� true
	return true;
}





void Circle::drawUnpaintedCircle(HDC hdc, const RECT* rt) const {
	// ���� ������ � ����� ����������� - ������� �� �������
	if (!isCorrect(rt)) return;
	// ������� ���� � �����
	HPEN pen = SelectPen(hdc, CreatePen(PS_SOLID, 1, RGB(r, g, b)));
	HBRUSH brush = SelectBrush(hdc, CreateSolidBrush(RGB(0, 0, 0))); // ��� � ��� RGB(0,0,0) �.�. ������������� ������
	// �������� ������� ��� ��������� �����
	// ������� ������ - hdc, ��� ��������������� ����� � �������
	Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
	// ������� ����� � ����, ����� ���������� ������
	DeletePen(pen);
	DeleteBrush(brush);
}

void Circle::drawPaintedCircle(HDC hdc, const RECT* rt) const {
	// ���� ������ � ����� ����������� - ������� �� �������
	if (!isCorrect(rt)) return;
	// ������� ���� � �����
	HPEN pen = SelectPen(hdc, CreatePen(PS_SOLID, 1, RGB(r, g, b)));
	HBRUSH brush = SelectBrush(hdc, CreateSolidBrush(RGB(rFill, gFill, bFill))); // ���
	Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
	// ������� ����� � ����, ����� ���������� ������
	DeletePen(pen);
	DeleteBrush(brush);
}

//
// ������ ���� ������� - � ������� ��� ����� �������� �������� ���������� � ������ �����
//
int Circle::getCenterX() const {
	return centerX;
}

int Circle::getCenterY() const {
	return centerY;
}

int Circle::getRadius() const	{
	return radius;
}

//
// ������ ���� ������� - � ������� ��� ������������� �������� � ������ �����
//
void Circle::setCenter(int centerX, int centerY) {
	this->centerX = centerX;
	this->centerY = centerY;
}

void Circle::setRadius(int radius) {
	this->radius = radius;
}

void Circle::setColor(int r, int g, int b) {
	this->r = r;
	this->g = g;
	this->b = b;
}

void Circle::setFillColor(int rFill, int gFill, int bFill) {
	this->rFill = rFill;
	this->gFill = gFill;
	this->bFill = bFill;
}