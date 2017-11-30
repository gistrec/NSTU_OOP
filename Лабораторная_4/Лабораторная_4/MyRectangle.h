#pragma once
#include "MyFigure.h"

class MyRectangle : private MyFigure {

private:
	// ��� �����
	int x1, y1;
	int x2, y2;
public:
	// ����������� ������
	MyRectangle(int x1, int y1, int x2, int y2);

	// �������� ������ � ������ � ����
	void load(const std::string &fileName) override;

	// ���������� ������ � ������ � ����
	void save(const std::string &fileName) const override;

	// ��������� ������������� ������
	void drowPainted(HDC hdc, const RECT* rt) const override;

	// ��������� ����������� ������
	void drowUnpainted(HDC hdc, const RECT* rt) const override;

	// ��������, ����� �� ������ � ������� ��������� �����������
	bool isValid(const RECT* rt) const override;

	// �������/�������
	void setPoints(int x1, int y1, int x2, int y2);
	void getPoints(int &x1, int &y1, int &x2, int &y2) const;
};