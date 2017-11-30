#pragma once
#include "OwnIterator.h"
#include "MyCircle.h"
#include <memory>


// Класс реализует понятие таблицы для хранения классов
// Позволяет добавлять, удалять и искать классы по их id
class Container {

private:
	// Структура элемента списка
	static struct Element {
		int id;
		std::shared_ptr<MyCircle> figure;
		std::shared_ptr<Element> previous;
		std::shared_ptr<Element> next;
	};

	using iterator = OwnIterator<MyCircle, Element>;
	using const_iterator = OwnIterator<const MyCircle, Element>;

	// Двунаправленный список указатель на начало и конец
	std::shared_ptr<Element> start;
	std::shared_ptr<Element> tail;

	// Получаем указатель на первый или последний элемент
	std::shared_ptr<Element> getFirstElement() const;
	std::shared_ptr<Element> getLastElement() const;

public:
	// Конструктор класса
	Container();


	iterator begin();
	iterator end();

	const_iterator begin() const;
	const_iterator end() const;

	// Добавить фигуру с заданным id вначало списка
	void addFigure(std::shared_ptr<MyCircle> figure, int id);

	// Получаем указатель на класс фигуры
	// Если фигуры с таким id нет - создается исключение
	std::shared_ptr<MyCircle> getFigure(int id) const;

	// Проверяет есть ли фигура в конейнере
	bool isInContainer(int id) const;

	// Удалить фигуру с заданным id
	void deleteFigure(int id);

	// Загрузка набора фигур в контейнер
	void load(const std::string &fileName);

	// Сохраняем набор фигур в файл
	void save(const std::string &fileName) const;

	// Деструктор нужен для освобождения памяти
	~Container();
};