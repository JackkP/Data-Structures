// Red Black Tree, Jack Porter, C++ Data Structures April 2022

#include "RedBlackTree.h"
#include <iostream>
#include <cstring>

using namespace std;

#define RIGHT true
#define LEFT false

//CONSTRUCTOR:
//Public function:
RedBlackTree::RedBlackTree(){
	head = NULL;
}

//DESTRUCTOR:
//Helper function:
void RedBlackTree::deleteRec(Node* n){ //recursively delete all nodes from tree with head n
	if (n) {
		deleteRec(n->right);
		deleteRec(n->left);
		delete n;
	}
}

//Public function:
RedBlackTree::~RedBlackTree(){
	deleteRec(head);
}



//PRINTING:
//Helper functions:
//function to print branches of the binary tree
void RedBlackTree::showBranches(Branch* p){
	if (p) {
		showBranches(p->prev); //print the previous branch (in this line)
		cout << p->str;
	}
}

//function to print binary tree with branches based on (almost identical to) https://www.techiedelight.com/c-program-print-binary-tree/
void RedBlackTree::printTree(Node* n, Branch* prev, bool isRight) {
    if (!n) { //dont print this node
        return;
    }

    char prev_str[10];
    strcpy(prev_str, "         "); //start with a space precceding (horizontally)
    Branch* branch = new Branch(); //new branch for this node
    branch->prev = prev; //building linked list of horzontal branches
    strcpy(branch->str, prev_str);
    printTree(n->right, branch, true); //print the tree for the right most branch

    if (!prev) { //head of the tree
	strcpy(branch->str, "———");
    }
    else if (isRight){
	strcpy(branch->str, ".———"); //right node
        strcpy(prev_str, "        |");
    }
    else {
	strcpy(branch->str, "`———"); //left node
        strcpy(prev->str, prev_str);
    }
    showBranches(branch); //print the linked list of preceeding branches on this line
    cout << " " << n->value;
    if (n->color == RED) cout << " (R)" << endl;
    else if (n->color == BLACK) cout << " (B)" << endl;
    
    if (prev) {	//add space or vertical line depending on left/right
        strcpy(prev->str, prev_str);
    }
    strcpy(branch->str, "        |");
    printTree(n->left, branch, false);
    delete branch; //get rid of the branch when finished
}

void RedBlackTree::printRec(Node* n, int space) { //print without lines between
	if (!n) return;
	
	// Increase distance between levels by 10 spaces
	space += 10;
	
	//Print right child tree first
	printRec(n->right, space);
	
	// Print current value after space
	for (int i = 10; i < space; i++)
        	cout<<" ";
    	cout<<n->value<<"\n\n";

	//Print left child tree
	printRec(n->left, space);
}

//Public function:
void RedBlackTree::print(){
	//cout << endl;
	//printRec(head, 0); //print starting at the head
	
	//cout << "with branches:\n\n" << endl; 
	cout << endl;
	printTree(head, NULL, false);
	cout << endl;
}

//function to a tree through P
void RedBlackTree::rotate(Node* P, bool right){
	Node* G = P->parent;
	Node* N;
	if(right){
		N = P->left;
		P->parent = N;
		P->left = N->right;
		N->right = P;
	}
	else{
		N = P->right;
		P->parent = N;
		P->right = N->left;
		N->left = P;
	}
	
	N->parent = G;
	if(!G) head = N;
	else if (G->right == P) G->right = N;
	else G->left = N;
}


Node* RedBlackTree::uncle(Node* n){ //return the uncle or NULL if there is no uncle
	if (n->parent){ //n has a parent
		if (n->parent->parent){ //n has a grandparent
			if (n->parent == n->parent->parent->left) return n->parent->parent->right;
			else if (n->parent = n->parent->parent->right) return n->parent->parent->left;
		}
		else return NULL;
	}
	else return NULL;
}

//(pain) ballance the tree after inserting a node
void RedBlackTree::balanceIns(Node* n){
	if (!n) return;
	//print();
	cout << "balancing" << endl;
	if (n == head) { //case 1, inserting at the root
		cout << "case 1" << endl; //set the color to black
		n->color = BLACK;
		return;
	}
	
	else if (n->parent->color == BLACK){ //case 2, parent is black
		//cout << "case 1" << endl; //nothing happens
		return; 
	}
	
	else if (uncle(n) && n->parent->color == RED && uncle(n)->color == RED){ //case 3, parent and uncle are both red
		cout << "case 3" << endl;
		n->parent->color = BLACK; //parent becomes black
		n->parent->parent->color = RED; //grandfateher becomes red
		uncle(n)->color = BLACK; //uncle becomes black
		balanceIns(n->parent->parent); //ballance from the grandparent
	}
	//case 4, (node left, parent right)||(node right, parent left), uncle is black, parent is red
	else if (n->parent->color == RED && n->parent->parent //parent is red (1) and has a grandparent
			&& (!uncle(n) || uncle(n)->color == BLACK) //Uncle is black (2)
			&& (n == n->parent->left && n->parent == n->parent->parent->right //node is the right inside child (3)
				|| n == n->parent->right && n->parent == n->parent->parent->left)){ //node is the left inside child (3)
		cout << "case 4";
		if (n == n->parent->left && n->parent == n->parent->parent->right){ //node is the inside grandchild to the right, case 4 
			//rotate to the right through parent
			Node* P = n->parent;
			rotate(P, RIGHT);
			balanceIns(P);
		}
		else if (n == n->parent->right && n->parent == n->parent->parent->left){ //node is the inside grandchild to the left, case 4
			//rotate to the left through parent
			Node* P = n->parent;
			rotate(P, LEFT);
			balanceIns(P);
		}
	}
	//case 5 n is red, parent is red, uncle is black, (node left, parent left) || (node right, parent right)
	else if (n->color == RED && n->parent->color == RED && n->parent->parent //n is red, parent is red, has a grandparent
			&& (!uncle(n) || uncle(n)->color == BLACK) //uncle is black
			&& (n == n->parent->left && n->parent == n->parent->parent->left || //left left or right right
				n == n->parent->right && n->parent == n->parent->parent->right)) { //case 5
		cout << "case 5 ";
		if (n == n->parent->left && n->parent == n->parent->parent->left){ //node is the outside grandchild to the left, case 5 
			Node* G = n->parent->parent;
			Node* P = n->parent;

			G->color = RED; //change colors of parent and grandparent
			P->color = BLACK;

			rotate(G, RIGHT); //rotate right through grandparent
		}
		else if (n == n->parent->right && n->parent == n->parent->parent->right){ //node is the outside grandchild to the right, case 5
			Node* G = n->parent->parent;
			Node* P = n->parent;
			
			G->color = RED; //change colors of parent and grandparent
			P->color = BLACK;

			rotate(G, LEFT); //rotate left through grandparent
		}
	}
}


//PUSHING:
//Helper function:
void RedBlackTree::addAfter(Node* val, Node* &n, Node* parent){ //recursively add node to binary tree
	if (n) {
		if (val->value >= n->value) {
			addAfter(val, n->right, n); //add it to the right because it is greater than or equal to n
		}
		else if (val->value < n->value){ //add it to the left because it less than n
			addAfter(val, n->left, n);
		}
	}
	else {
		n = val;
		n->parent = parent;
		balanceIns(n);
	}
}

//Public function:
void RedBlackTree::push(int val){ //add a value to the tree
	Node* newNode = new Node(val);
	addAfter(newNode, head, NULL);
}

//SEARCHING:
//Helper function:
int RedBlackTree::searchRec(Node* n, int val){ //search and return number of values contained in tree with head n
	if(!n) return 0;
	else if (val > n->value) return searchRec(n->right, val);
	else if (val < n->value) return searchRec(n->left, val);
	else if (val == n->value) return 1 + searchRec(n->left, val) + searchRec(n->right, val);
}

//Public function:
int RedBlackTree::search(int val){ //return number of a value that exist in the tree
	return searchRec(head, val);
}


Node* RedBlackTree::inorderSuccessor(Node* n, bool right){ //pull the leftmost node out and return it
	if(!n) return NULL;
	cout << "n->value = " << n->value << endl;
	if (right) { //searching the right side so will be traversing left (next highest)
		if (n->left) return replacewith(n->left, RIGHT);
		else return n;
	}
	else { //searching left tree so traversing right (next lowest)
		if (n->right) return replacewith(n->right, LEFT);
		else return n;
	}
}

void RedBlackTree::balanceRem(Node* n){
	
	
}

int RedBlackTree::removeN(Node* n, int val){ //remove the first of a certain value in the tree
	if(!n) return 0;
	if (n->value == val){ //node to delete
		if (n == head && !n->right && !n->left) { //n is head and has no children
			head = NULL;
			delete n;
			return 1;
		}
		
		Node* N; //node to be deleted from the tree

		//find the inorder successor
		if (n->left) N = inorderSuccessor(n->left, LEFT);
		else if (n->right) N = inorderSuccessor(n->right, RIGHT);
		else N = n;
		
		//copy data from node to be deleted into n
		n->data = N->data;

		//simple cases:
		//N is red and has no children
		if (N->color == RED && !N->left && !N->right){
			//set parent pointer to NULL and delete it
			if (N == N->parent->right) N->parent->right = NULL;
			else N->parent->left = NULL;
			delete N;
			return 1;
		}
		else if (N->color == BLACK){
			
		}

		//M is the node to be deleted from the tree
		


		return 1;
	}
	else if (n->value > val) return removeRec(n->left, val);
	else return removeRec(n->right, val);
	balanceRem(n);
}

//Public function:
int RedBlackTree::remove(int val){ //return the number of removed values in the tree
	//cout << "ptr loc of 5 is " << head->left->left->right->left << endl;
	return removeN(head, val);
}
