#pragma once
#include "MyCircle.h"

MyCircle::MyCircle(int centerX, int centerY, int radius) {
	this->centerX = centerX;
	this->centerY = centerY;
	this->radius = radius;
}

void MyCircle::load(const std::string &fileName) {
	std::ifstream input(fileName);
	if (!input.is_open()) throw std::string("���� �� ������");
	input >> centerX >> centerY >> radius;
	input >> r >> g >> b;
	input >> rFill >> gFill >> bFill;
}

void MyCircle::save(const std::string &fileName) const {
	std::ofstream output(fileName);
	// ��������� � ��� ������
	output << getCenterX() << " " << getCenterY() << " " << getRadius() << "\n";
	output << r << " " << b << " " << b << "\n";
	output << rFill << " " << gFill << " " << bFill;
}

void MyCircle::drowUnpainted(HDC hdc, const RECT* rt) const {
	if (!isValid(rt)) throw std::string("������ ����� ��� ������ ������");
	HPEN pen = SelectPen(hdc, CreatePen(PS_SOLID, 1, RGB(r, g, b)));
	HBRUSH brush = SelectBrush(hdc, CreateSolidBrush(RGB(0, 0, 0))); // ���
	Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
	DeletePen(pen);
	DeleteBrush(brush);
}

void MyCircle::drowPainted(HDC hdc, const RECT* rt) const {
	if (!isValid(rt)) throw std::string("������ ����� ��� ������ ������");
	// ������� ���� � �������, ��� ����� �������� ���� �����
	HPEN pen = SelectPen(hdc, CreatePen(PS_SOLID, 1, RGB(r, g, b)));
	HBRUSH brush = SelectBrush(hdc, CreateSolidBrush(RGB(rFill, gFill, bFill))); // ���
	Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
	// ������� ������� ����
	DeletePen(pen);
	// ������� ������� �����
	DeleteBrush(brush);
}

int MyCircle::isValid(const RECT* rt) const {
	if (centerX - radius < 0 || centerY - radius < 0 ||
		centerX + radius > rt->right || centerY + radius > rt->bottom) {
		return false;
	}
	return true;
}

int MyCircle::getCenterX() const {
	return this->centerX;
}

int MyCircle::getCenterY() const {
	return this->centerY;
}

void MyCircle::setCenter(int x, int y) {
	this->centerX = x;
	this->centerY = y;
}

void MyCircle::setColor(int r, int g, int b) {
	this->r = r;
	this->g = g;
	this->b = b;
}

int MyCircle::getRadius() const {
	return this->radius;
}

void MyCircle::setRadius(int radius) {
	if (radius < 0) throw std::string("������ ������ ���� ������ ����");
	this->radius = radius;
}