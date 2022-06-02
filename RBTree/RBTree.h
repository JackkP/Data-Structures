// Red Black Tree Class for Red Black Tree Project
// Jack P, C++ Data Structures, April 2022

#include "Node.h"
#include "Branch.h"

#include <cstring>

using namespace std;

class RBTree {
	public:
		RBTree();
		~RBTree();
		void push(int val);
		int remove(int val);
		void print();
		int search(int val);
		bool verify();
		
	private:
		Node* root;
		
		//manipulation
		
		//rotate a tree through node h to the right=true or left=false
		void rotate(Node* P, bool right);
		
		//Return the uncle or NULL if no uncle
		Node* uncle(Node* n);
		
		//Return the sibling of the node or NULL if no sibling
		Node* sibling(Node* n);
		
		
		//insertion
		
		//Ballance the tree with root N
		void balanceIns(Node* n);
		
		//helper function for push
		void addAfter(Node* val, Node* &n, Node* parent);
		
		//printing
		
		//helper function for printTree
		void showBranches(Branch* p);
		
		//helper function for print, recursive print (with lines)
		void printTree(Node* n, Branch* p, bool isRight); 
		
		
		//helper function for destructor, recursive delete (all nodes)
		void deleteRec(Node* n);
		
		
		//helper for search
		int searchRec(Node* n, int val);
		
		
		//deletion
		
		//helper function for deletion, returns a pointer to the inorder successor of a node
		Node* inorderSuccessor(Node* n, bool right);
		
		//helper function for deletion, balances tree after a node is removed
		void balanceRem(Node* n);
		
		//helper function for remove, removes nodes with data == val
		int removeN(Node* n, int val); 
		
		
		//helper function for verification
		int verR(Node* n);
};
