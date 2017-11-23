#pragma once
#include <stdio.h>
#include <iostream>

template <class Type, class TypeNext>
struct Node {
	Type value;
	Node<TypeNext, TypeNext>* next = NULL;

	Node(Type value) {
		this->value = value;
	}
};

void main() {
	Node<int, char>* first = new Node<int, char>(2);
	Node<char, char>* second = new Node<char, char>('c');
	first->next = second;

	std::cout << "Int " << first->value << std::endl;
	std::cout << "Char " << second->value << std::endl;

	system("pause");
}