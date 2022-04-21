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
		void addAfter(Node* val, Node* &n); //helper function for push
		void printRec(Node* n, int space); //helper function for print, recursive print (no lines)
		void showBranches(Branch* p); //helper function for printTree
		void printTree(Node* n, Branch* p, bool isRight); //helper function for print, recursive print (with lines)
		void deleteRec(Node* n); //helper function for destructur, recursive delete (all nodes)
		int searchRec(Node* n, int val); //helper function for searhc, recursive search
		Node* replacewith(Node* &n); //helper function for removeRec, find the bottom node to the left, remove it and return;
		int removeRec(Node* &n, int val); //helper function for remove, recursive remove (specified nodes)
};
