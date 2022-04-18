// Binary Tree for Binary Search Tree Project
// Jack P, C++ Data Structures, April 2022

#include "Node.h"

using namespace std;

class BinaryTree {
	public:
		void add(int val);
		int remove(int val);
		bool search(int val);
		void print(Node* n, int space);
	private:
		Node* head;
		void addAfter(int val, Node* &n);
};
