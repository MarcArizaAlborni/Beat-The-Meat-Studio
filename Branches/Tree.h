
class Tree {

public:
	~Tree()
	{
		clear();
	}

	void print_tree_pre_order() {

	}
	void print_tree_in_order() {
		print_In_order_Recursive(root);
	}
	void print_tree_post_order() {
		print_Post_order_Recursive(root);
	}
	void clear() {
		clear_Recursive(root);
	}
	void insert(int value) {


	}
	

	void  mergesort(int* array, int begin, int end) {


		if (begin < end) {


			int mid = (begin + end) / 2;
			mergesort(array, begin, mid);
			mergesort(array, mid + 1, end);
			merge(array, begin, mid, end);

		}


	}

	void merge(int*array, int begin, int mid, int end) {





	}
	
private:
	struct Node {
		int value;
		Node* left = nullptr;
		Node* right = nullptr;
	};
	
	Node* root = nullptr;
	void print_Pre_orde_Recursive(Node* n) {

		if (n != nullptr)
		{
			std::cout << n->value << "-";
			print_Pre_orde_Recursive(n->left);
			print_Pre_orde_Recursive(n->right);
		}

	}
	void print_In_order_Recursive(Node* n) {

		if (n != nullptr)
		{
			print_In_order_Recursive(n->left);
			std::cout << n->value << "-";
			print_In_order_Recursive(n->right);
		}

	}

	void print_Post_order_Recursive(Node* n) {

		if (n != nullptr)
		{
			print_Post_order_Recursive(n->left);
			print_Post_order_Recursive(n->right);
			std::cout << n->value << "-";
		}
	}

	void clear_Recursive(Node* n) {

		if (n != nullptr) {
			clear_Recursive(n->left);
			clear_Recursive(n->right);
			delete n;
		}
	}
};
