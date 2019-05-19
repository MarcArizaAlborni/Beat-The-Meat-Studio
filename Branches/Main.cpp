#include <iostream>
#include "Tree.h"

/*struct Node {
	int value = 0;
	Node *left = nullptr;
	Node *right = nullptr;
};

void print_tree_pre_order(Node* n) {

	if (n != nullptr)
	{
		std::cout << n->value << "-";
		print_tree_pre_order(n->left);
		print_tree_pre_order(n->right);
	}
}

void print_tree_in_order(Node* n) {

	if (n != nullptr)
	{
		print_tree_in_order(n->left);
		std::cout << n->value << "-";
		print_tree_in_order(n->right);
	}
}

void print_tree_post_order(Node* n) {

	if (n != nullptr)
	{
		print_tree_post_order(n->left);
		print_tree_post_order(n->right);
		std::cout << n->value << "-";
	}
}

void clear(Node *n) {

	if (n != nullptr) {
		clear(n->left);
		clear(n->right);
		delete n;
	}
}

int main() {

	Node* a = new Node; a->value = 3;
	Node* b = new Node; b->value = 4;
	Node* c = new Node; c->value = 5;
	Node* d = new Node; d->value = 6;
	Node* e = new Node; e->value = 10;
	Node* f = new Node; f->value = 0;
	Node* g = new Node; g->value = 2;

	a->left = b;
	a->right = e;
	b->left = c;
	b->right = d; 
	e->left = f;
	e->right = g;

	Tree traversal :

	       a

		b     c

		1.Pre - order: Antes de "hacer" un nodo voy ha "hacer" todo lo del propio nodo, despues la izquierda y po ultimo la derecha. a->b->c;
	2.In - order: Antes de "hacer" un nodo voy ha "hacer" todo lo de la izquierda, despues el propio nodo y ultimo el de la derecha. b->a->c;
	3.Post - order: Antes de "hacer" un nodo voy ha "hacer" todo lo de la izquierda, despues el de la derecha y despues el propio nodo. b->c->a;


	//Pre-order 5-4-6-3-0-10-2;
	//In-order
	//Post-order 

	print_tree_pre_order(a);
	std::cout << std::endl;
	print_tree_in_order(a);
	std::cout << std::endl;
	print_tree_post_order(a);
	std::cout << std::endl;

	clear(a); 

	system("pause");
	return 0;
} */

int mai() {


	system("pause");
	return 0;
}