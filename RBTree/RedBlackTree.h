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
		
		void balanceIns(Node* n); //Ballance the tree with head N
		Node* uncle(Node* n); //Return the uncle or NULL if no uncle


		void addAfter(Node* val, Node* &n, Node* parent); //helper function for push
		
		//printing:
		void printRec(Node* n, int space); //helper function for print, recursive print (no lines)
		void showBranches(Branch* p); //helper function for printTree
		void printTree(Node* n, Branch* p, bool isRight); //helper function for print, recursive print (with lines)
		
		void deleteRec(Node* n); //helper function for destructor, recursive delete (all nodes)

		int searchRec(Node* n, int val);
		
		Node* replacewith(Node* &n); //helper function for removing, returns a pointer to the node that the removed node is replaced with
		int removeRec(Node* &n, int val); //helper function for remove, removes nodes with value == val
};
