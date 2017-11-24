#include "Tree.h"
#include <iostream>

void print_Tree(node* p, int level) {
	if (p) {
		print_Tree(p->ll, level + 1);
		for (int i = 0; i< level; i++) std::cout << "   ";
		std::cout << p->Value << std::endl;
		print_Tree(p->rr, level + 1);
	}
}

void main() {
	init();
	//int x;
	//while (cin >> x) {
	//	Root = insert(Root, x, 1);
	//	cout << Root << endl;
	//}
	insert(Root, 2, 1);
	insert(Root, 3, 2);
	insert(Root, 4, 3);
	print_Tree(Root, 0);
}