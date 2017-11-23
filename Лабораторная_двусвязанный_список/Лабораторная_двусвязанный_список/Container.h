#pragma once
#include "OwnIterator.h"
#include "MyCircle.h"
#include <memory>


// ����� ��������� ������� ������� ��� �������� �������
// ��������� ���������, ������� � ������ ������ �� �� id
class Container {

private:
	// ��������� �������� ������
	static struct Element {
		int id;
		std::shared_ptr<MyCircle> figure;
		std::shared_ptr<Element> previous;
		std::shared_ptr<Element> next;
	};

	using iterator = OwnIterator<MyCircle, Element>;
	using const_iterator = OwnIterator<const MyCircle, Element>;

	// ��������������� ������ ��������� �� ������ � �����
	std::shared_ptr<Element> start;
	std::shared_ptr<Element> tail;

	// �������� ��������� �� ������ ��� ��������� �������
	std::shared_ptr<Element> getFirstElement() const;
	std::shared_ptr<Element> getLastElement() const;

public:
	// ����������� ������
	Container();


	iterator begin();
	iterator end();

	const_iterator begin() const;
	const_iterator end() const;

	// �������� ������ � �������� id ������� ������
	void addFigure(std::shared_ptr<MyCircle> figure, int id);

	// �������� ��������� �� ����� ������
	// ���� ������ � ����� id ��� - ���������� NULL
	std::shared_ptr<MyCircle> getFigure(int id) const;

	// ��������� ��������� �� ������ c �������� id � ����������
	bool isInContainer(int id) const;

	// ������� ������ � �������� id
	void deleteFigure(int id);

	// ������� id ���� �����
	void printAllId() const;

	// �������� ������ ����� � ���������
	void load(const std::string &fileName);

	// ��������� ����� ����� � ����
	void save(const std::string &fileName) const;

	// ���������� ����� ��� ������������ ������
	~Container();
};