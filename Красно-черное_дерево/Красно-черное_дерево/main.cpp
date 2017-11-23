#include "Tree.h"
#include <iostream>

void print_Tree(Node * p, int level) {
	if (p) {
		print_Tree(p->left, level + 1);
		for (int i = 0; i< level; i++) std::cout << "   ";
		std::cout << p->data << std::endl;
		print_Tree(p->right, level + 1);
	}
}

void main() {
	std::cout << "Test" << std::endl;
	int a, maxnum, ct;
	Node *t;

	maxnum = 10;

	for (ct = maxnum; ct; ct--) {
		a = rand() % 9 + 1;
		if ((t = findNode(a)) != NULL) {
			deleteNode(t);
		} else {
			insertNode(a);
		}
	}

	print_Tree(root, 0);


	system("pause");
}