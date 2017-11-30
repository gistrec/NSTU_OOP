#pragma once
#include "Container.h"

Container::iterator Container::begin() {
	return iterator(start);
}

Container::iterator Container::end() {
	return iterator(nullptr);
}

Container::const_iterator Container::begin() const {
	return const_iterator(start);
}

Container::const_iterator Container::end() const {
	return const_iterator(nullptr);
}

std::shared_ptr<Container::Element> Container::getFirstElement() const {
	return start;
}

std::shared_ptr<Container::Element> Container::getLastElement() const {
	return tail;
}


std::shared_ptr<MyCircle> Container::getFigure(int id) const {
	std::shared_ptr<Element> currentElement = getFirstElement();
	while (currentElement != nullptr) {
		if (currentElement->id == id) return currentElement->figure;
		currentElement = currentElement->next;
	}
	if (currentElement == nullptr) return NULL;
	else return currentElement->figure;
}


bool Container::isInContainer(int id) const {
	if (getFigure(id) == nullptr) return false;
	else return true;
}


void Container::addFigure(std::shared_ptr<MyCircle> figure, int id) {
	//Element* newElement = new Element();
	std::shared_ptr<Element> newElement = std::make_shared<Element>();
	newElement->id = id;
	newElement->figure = figure;
	newElement->next = getFirstElement();
	newElement->previous = nullptr;
	if (getFirstElement() != nullptr) {
		getFirstElement()->previous = newElement;
	}
	start = newElement;
}


void Container::deleteFigure(int id) {
	std::shared_ptr<Element> currentElement = getFirstElement();
	while (currentElement != nullptr && currentElement->id != id) {
		currentElement = currentElement->next;
	}
	if (currentElement == nullptr) return;
	*(currentElement->previous->next) = *(currentElement->next);
	*(currentElement->next->previous) = *(currentElement->previous);
}


void Container::load(const std::string &fileName) {
	// Данные для фигуры
	int id = 0;
	int centerX, centerY, radius;

	std::ifstream input(fileName);
	if (!input.is_open()) throw 3;
	while (input >> centerX >> centerY >> radius) {
		// std::cout << centerX << " " << centerY << " " << radius << "\n";
		std::shared_ptr<MyCircle> newFigure = std::make_shared<MyCircle>(centerX, centerY, radius);
		addFigure(newFigure, id++);
	}
}


void Container::save(const std::string &fileName) const {
	std::ofstream output(fileName);

	std::shared_ptr<Element> currentElement = getFirstElement();
	while (currentElement != nullptr) {
		std::shared_ptr<MyCircle> figure = currentElement->figure;
		output << figure->getCenterX() << figure->getCenterY() << figure->getRadius() << "\n";
		currentElement = currentElement->next;
	}
}


Container::~Container() {
	std::shared_ptr<Element> currentElement = getFirstElement();
	while (currentElement != nullptr) {
		std::shared_ptr<Element> deleteElement = currentElement;
		currentElement = currentElement->next;
		deleteElement->next = nullptr;
		deleteElement->previous = nullptr;
	}
}