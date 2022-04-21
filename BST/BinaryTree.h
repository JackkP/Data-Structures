// Binary Tree for Binary Search Tree Project
// Jack P, C++ Data Structures, April 2022

#include "Node.h"
#include <cstring>

using namespace std;

//struct for printing trees based on https://www.techiedelight.com/c-program-print-binary-tree/
struct Branch {
	Branch* prev;
	char* str;

	Branch(){
		str = new char[10];
	}
    
	~Branch(){
		delete prev;
		delete str;
	}

};

class BinaryTree {
	public:
		BinaryTree();
		~BinaryTree();
		void push(int val);
		int remove(int val);
		void print();
		int search(int val);
	private:
		Node* head;
		void addAfter(Node* val, Node* &n);
		void printRec(Node* n, int space);
		void showBranches(Branch* p);
		void printTree(Node* n, Branch* p, bool isLeft);

};
