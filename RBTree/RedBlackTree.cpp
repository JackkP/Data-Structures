// Red Black Tree, Jack Porter, C++ Data Structures April 2022

#include "RedBlackTree.h"
#include <iostream>
#include <cstring>

using namespace std;

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


void RedBlackTree::Balance(Node* &n){
	
	
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
	
	Node* next = n->left;
	if (val >= n->value) next = n->right;
	if (val == n->value) return 1 + searchRec(next, val);
	else return searchRec(next, val);
}

//Public function:
int RedBlackTree::search(int val){ //return number of a value that exist in the tree
	return searchRec(head, val);
}



//REMOVING:
//Helper functions:
Node* RedBlackTree::replacewith(Node* &n){ //pull the leftmost node out and return it
	if(!n) return NULL;
	cout << "n->value = " << n->value << endl;
	if (n->left) return replacewith(n->left); //left tree
	else if (n->right) return replacewith(n->right); //if no left tree, use right tree
	else { //no node to the left or right
		Node* tmp = n;
		n = NULL;
		return tmp;
	}
}

int RedBlackTree::removeRec(Node* &n, int val){ //recursively remove all of a certain value in the tree
	if(!n) return 0;
	if (n->value == val){
		if (n->right){ //delete n and replace with the lowest value on the right
			Node* tmp = replacewith(n->right); //pointer to replacement value
			Node* right = n->right; //store the right tree to n
			Node* left = n->left; //store the left tree to n
			delete n; //delete the node
			n = tmp; //place the new node
			if (right) n->right = right; //make sure not to overwrite left and right trees
			if (left) n->left = left;
		}
		else { //replace with the head of the left (still applies if null)
			Node* tmp = n->left; //
			delete n;
			n = tmp;
		}
		return 1 + removeRec(n, val); //add 1 and continue searching from this location
	}
	else {
		if (val >= n->value) return removeRec(n->right, val); //look to the right of this node
		else return removeRec(n->left, val); //look to the left of this node
	}

}

//Public function:
int RedBlackTree::remove(int val){ //return the number of removed values in the tree
	//cout << "ptr loc of 5 is " << head->left->left->right->left << endl;
	return removeRec(head, val);
}
