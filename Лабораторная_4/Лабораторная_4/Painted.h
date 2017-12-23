#pragma once

class Painted {

protected:
	// � ������ ������ ���� ���� �������
	// � ������������� - ��� �� �����
	int redFill,
		greenFill,
		blueFill;

public:
	Painted(int redFill, int greenFill, int blueFill) {
		this->redFill = redFill;
		this->greenFill = greenFill;
		this->blueFill = blueFill;
	}

	// � ������ ������ ����� ���������� ���� ������� � �������
	void setFillColor(int red, int green, int blue) {
		this->redFill = red;
		this->greenFill = green;
		this->blueFill = blue;
	}

	// �������� ���� ������ ����� ������ �� �����
	void getFillColor(int &red, int &green, int &blue) const {
		red = this->redFill;
		green = this->greenFill;
		blue = this->blueFill;
	}
};