// Red Black Tree Class for Red Black Tree Project
// Jack P, C++ Data Structures, April 2022

#include "Node.h"
#include "Branch.h"

#include <cstring>

using namespace std;

class RedBlackTree {
	public:
		RedBlackTree();
		~RedBlackTree();
		void push(int val);
		int remove(int val);
		void print();
		int search(int val);
	private:
		Node* head;
		
		void balance(Node* n); //Ballance the tree with head N

		void addAfter(Node* val, Node* &n, Node* parent); //helper function for push
		
		//printing:
		void printRec(Node* n, int space); //helper function for print, recursive print (no lines)
		void showBranches(Branch* p); //helper function for printTree
		void printTree(Node* n, Branch* p, bool isRight); //helper function for print, recursive print (with lines)
		
		void deleteRec(Node* n); //helper function for destructor, recursive delete (all nodes)
		
		int searchRec(Node* n, int val); //helper function for searhc, recursive search
		
		//removing nodes
		Node* replacewith(Node* &n); //helper function for removeRec, find the bottom node to the left, remove it and return;
		int removeRec(Node* &n, int val); //helper function for remove, recursive remove (specified nodes)
};
