
// ����������� windows.h � windowsx.h ���������  ������������ � ����� ���������
// ����������, ��������������� ������������ �������� Windows
#include <windows.h>
#include <windowsx.h>
// ���������� ��� �����-������
#include <fstream>
// ���������� ����� ��� �������� ��������� ����������
#include <string>


// ��������� �����
struct Circle {
	int centerX, centerY; // ����� �����
	int radius; // ������ �����

	int r = 0, g = 255, b = 0; // ���� ����������
	int rFill = 0, gFill = 255, bFill = 0; // ���� ������ ������
	
	// ����������� ��������� - �����, ����� ����� � ������ ��������� ���������
	// �� ����� ������ ��� �� ����� ������ �� centerX, centerY, radius
	Circle(int centerX, int centerY, int radius) {
		this->centerX = centerX;
		this->centerY = centerY;
		this->radius = radius;
	};
};


// �������� �� ������������ ������
// � ������ �� ������� ������ � �������������� ����
//
// ������� ������: ��������� �� ��������� RECT, e�������� �� ��������� �����
// ��������� �����������, �.�. �� �� ������ �� ����������
// P.S. ��������� RECT ���������� ���������� ��������������. � ����� ������ - ��������� �����������
//
// �������� ������: true - ���� ������ ���������, ����� false
boolean isCorrect(const RECT* rt, const Circle* circle) {
	// �������� �� '������� ������'
	if (circle->radius <= 0) {
		printf_s("������, � ����� ������������� ������");
		return false;
	}
	// �������� �� �������������� ����
	// ���� ���� ��� ���� ����� '�������' �� �������� �����������
	if ((circle->centerX - circle->radius) < 0 || (circle->centerY - circle->radius) < 0 ||
		// ���� ��� ��� ����� '�������' �� �������� �����������
		(circle->centerX + circle->radius > rt->right) || (circle->centerY + circle->radius) > rt->bottom) {
		printf_s("������, ���� ������� �� ������� �����������");
		return false;
	}
	// ���� ��� �������� �������� - ���������� true
	return true;
}


// ��������� �������������� �����, �.�. ����� ����� ����� �������� RGB(0,0,0)
// 
// ������� ������: HDC - ����������, �.�. ����� �����, ������������� ��������� �����������
// ����������� ��������� �� ��������� RECT � Circle
void drawUnpaintedCircle(HDC hdc, const RECT* rt, const Circle* circle) {
	// ���� ������ � ����� ����������� - ������� �� �������
	if (!isCorrect(rt, circle)) return;
	// ������� ���� � �����
	HPEN pen = SelectPen(hdc, CreatePen(PS_SOLID, 1, RGB(circle->r, circle->g, circle->b)));
	HBRUSH brush = SelectBrush(hdc, CreateSolidBrush(RGB(0, 0, 0))); // ��� � ��� RGB(0,0,0) �.�. ������������� ������
	// �������� ������� ��� ��������� �����
	// ������� ������ - hdc, ��� ��������������� ����� � �������
	Ellipse(hdc, circle->centerX - circle->radius, circle->centerY - circle->radius,
		    circle->centerX + circle->radius, circle->centerY + circle->radius);
	// ������� ����� � ����, ����� ���������� ������
	DeletePen(pen);
	DeleteBrush(brush);
}


// ��������� ������������ �����
// ������� ���������� ����������, �� ����������� ����� �����
void drawPaintedCircle(HDC hdc, const RECT* rt, const Circle* circle) {
	// ���� ������ � ����� ����������� - ������� �� �������
	if (!isCorrect(rt, circle)) return;
	// ������� ���� � �����
	HPEN pen = SelectPen(hdc, CreatePen(PS_SOLID, 1, RGB(circle->r, circle->g, circle->b)));
	HBRUSH brush = SelectBrush(hdc, CreateSolidBrush(RGB(circle->rFill, circle->gFill, circle->bFill)));
	// ������ ������ (� ����� ������ ����)
	Ellipse(hdc, circle->centerX - circle->radius, circle->centerY - circle->radius,
		circle->centerX + circle->radius, circle->centerY + circle->radius);
	// ������� ����� � ����, ����� ���������� ������
	DeletePen(pen);
	DeleteBrush(brush);
}


// �������� �� �������������� ����� little ����� big
// ��� ������� �� �������� - big ������ �������� little
//
// �������� ������: true - ��������, false - ���
boolean isInclude(const Circle* big, const Circle* little) {
	// ���� ������ ���������� ����� ����� ��� ������, ��� ������ �������� - �� ����� �� ��������
	if (little->radius >= big->radius) return false;

	// distance - ���������� ����� �������� ���� ������
	double distance = sqrt((little->centerX - big->centerX) * (little->centerX - big->centerX) +
		                   (little->centerY - big->centerY) * (little->centerY - big->centerY));
	// ��� ����� ���������� - � �� ���� ��� ������� ��� ��������
	if (big->radius < (little->radius + distance)) return false;
	// ���� �������� ��� �������� - ���������� true
	return true;
}


// ��������� ���� ������, ���� little ����������� ����� big
//		1. ��������� �� ������������ ������ ���� ������
//		2. ��������� ����������� �� ���� little ����� big
//		3. ������ ����������� ���� big
//		4. ������ ������������� ���� little
void drawTwoCircle(HDC hdc, const RECT* rt, const Circle* big, const Circle* little) {
	if (!isCorrect(rt, big)) return;
	if (!isCorrect(rt, little)) return;

	if (!isInclude(big, little)) return;
	drawPaintedCircle(hdc, rt, big);
	drawUnpaintedCircle(hdc, rt, little);
}

// �������� ����� �� ������ �� ����� filename
// �������� ������ - �������� �����
//
// �������� ������ - ��������� �� ���� ��� null, ���� ���� �� ������
Circle* loadCircle(const std::string &fileName) {
	// ������ �����
	std::ifstream input(fileName);
	// ���� ���� �� ������ (�� ������) - ���������� NULL
	if (!input.is_open()) return NULL;
	// ������� ����
	Circle* circle = new Circle(0, 0, 0);
	// ������ ������ ���������� � ����
	input >> circle->centerX >> circle->centerY >> circle->radius;
	input >> circle->r >> circle->g >> circle->b;
	input >> circle->rFill >> circle->gFill >> circle->bFill;
	
	return circle;
}


// ���������� ����� � ���� filename
// �������� ������ - �������� ����� � ����������� ��������� �� ����
void saveCircle(const std::string &fileName, const Circle* circle) {
	std::ofstream output(fileName); // ������� ����
	// ��������� ��� ������
	// �� ������ ������ - ����� � ������, �� ������ - ���� ����������, �� ������� - ���� �������
	output << circle->centerX << " " << circle->centerY << " " << circle->radius << "\n";
	output << circle->r << " " << circle->g << " " << circle->b << "\n";
	output << circle->rFill << " " << circle->gFill << " " << circle->bFill;
}


void main() {
	// ��������� �������� ����� � �������
	setlocale(LC_ALL, "Russian");
	// �������� ������������� ����
	HWND hwnd = GetConsoleWindow();
	// �������� �������� �����������
	HDC hdc = GetDC(hwnd);
	RECT rt;
	// �������� ������ ����
	GetClientRect(hwnd, &rt);


	// ��� ��� ������ �������, ���� ����� ��������� ������� ��� 
	Circle* figure1 = new Circle(200, 200, 100); // ������� ����
	//saveCircle(std::string("output.txt"), figure1);
	Circle* figure2 = loadCircle(std::string("output.txt"));
	drawPaintedCircle(hdc, &rt, figure2);
	//drawPaintedCircle(hdc, &rt, figure1); // ������ ����
	// ��� ��� ����� �������, ���� ����� ��������� ������� ���

	
	system("pause"); // ����� ���������
	// ����������� �������� �����������
	ReleaseDC(hwnd, hdc);
}