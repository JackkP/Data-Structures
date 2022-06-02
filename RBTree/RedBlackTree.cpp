// Red Black Tree, Jack Porter, C++ Data Structures April 2022

#include "RedBlackTree.h"
#include <iostream>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;

#define RIGHT true
#define LEFT false

//CONSTRUCTOR:
//Public function:
RedBlackTree::RedBlackTree(){
	root = NULL;
}

//DESTRUCTOR:
//Helper function:
void RedBlackTree::deleteRec(Node* n){ //recursively delete all nodes from tree with root n
	if (n) {
		deleteRec(n->right);
		deleteRec(n->left);
		delete n;
	}
}

//Public function:
RedBlackTree::~RedBlackTree(){
	deleteRec(root);
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

    if (!prev) { //root of the tree
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
    cout << " " << n->data;
    //if (n->parent) cout << " p=" << n->parent->data;
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
	
	// Print current data after space
	for (int i = 10; i < space; i++)
        	cout<<" ";
    	cout<<n->data<<"\n\n";

	//Print left child tree
	printRec(n->left, space);
}

//Public function:
void RedBlackTree::print(){
	//cout << endl;
	//printRec(root, 0); //print starting at the root
	
	//cout << "with branches:\n\n" << endl; 
	cout << endl;
	printTree(root, NULL, false);
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
		if (N->right) N->right->parent = P;
		N->right = P;
	}
	else{
		N = P->right;
		P->parent = N;
		P->right = N->left;
		if (N->left) N->left->parent = P;
		N->left = P;
	}
	
	N->parent = G;
	if(!G) root = N;
	else if (G->right == P) G->right = N;
	else G->left = N;
}


Node* RedBlackTree::uncle(Node* n){ //return the uncle or NULL if there is no uncle
	if (n->parent && n->parent->parent){ //n has a grandparent
		if (n->parent == n->parent->parent->left) return n->parent->parent->right;
		else if (n->parent = n->parent->parent->right) return n->parent->parent->left;
	}
	else return NULL;
}

Node* RedBlackTree::sibling(Node* n){ //return the sibling
	if (n->parent && n == n->parent->right) return n->parent->left;
	else if (n->parent && n == n->parent->left) return n->parent->right;
	else return NULL;
}

//(pain) ballance the tree after inserting a node
void RedBlackTree::balanceIns(Node* n){
	if (!n) return;
	//print();
	//cout << "balancing" << endl;
	if (n == root) { //case 1, inserting at the root
		//cout << "case 1" << endl; //set the color to black
		n->color = BLACK;
		return;
	}
	
	else if (n->parent->color == BLACK){ //case 2, parent is black
		//cout << "case 2" << endl; //nothing happens
		return; 
	}
	
	else if (uncle(n) && n->parent->color == RED && uncle(n)->color == RED){ //case 3, parent and uncle are both red
		//cout << "case 3" << endl;
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
		//cout << "case 4" << endl;
		if (n == n->parent->left && n->parent == n->parent->parent->right){ //node is the inside grandchild to the right, case 4 
			//rotate to the right through parent
			//cout << "bkp 1" << endl;
			//cout << "right rotation through " << n->parent->data << endl;
			Node* P = n->parent;
			rotate(P, RIGHT);
			balanceIns(P);
		}
		else if (n == n->parent->right && n->parent == n->parent->parent->left){ //node is the inside grandchild to the left, case 4
			//rotate to the left through parent
			//cout << "bkp 2" << endl;
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
		//cout << "case 5, n=" << n->data;
		//if (n->parent) cout << " p=" << n->parent->data;
		//cout << endl;
		if (n == n->parent->left && n->parent == n->parent->parent->left){ //node is the outside grandchild to the left, case 5 
			//cout << "l-l" << endl;
			
			Node* G = n->parent->parent;
			Node* P = n->parent;

			G->color = RED; //change colors of parent and grandparent
			P->color = BLACK;
			
			//print();

			rotate(G, RIGHT); //rotate right through grandparent
		}
		else if (n == n->parent->right && n->parent == n->parent->parent->right){ //node is the outside grandchild to the right, case 5
			//cout << "r-r" << endl;

			Node* G = n->parent->parent;
			Node* P = n->parent;
			
			G->color = RED; //change colors of parent and grandparent
			P->color = BLACK;
			
			//print();
			
			rotate(G, LEFT); //rotate left through grandparent
		}
	}
}


//PUSHING:
//Helper function:
void RedBlackTree::addAfter(Node* val, Node* &n, Node* parent){ //recursively add node to binary tree
	if (n) {
		if (val->data >= n->data) {
			addAfter(val, n->right, n); //add it to the right because it is greater than or equal to n
		}
		else if (val->data < n->data){ //add it to the left because it less than n
			addAfter(val, n->left, n);
		}
	}
	else {
		n = val;
		n->parent = parent;
		//cout << "Inserting " << val->data << " and balancing" << endl;
		balanceIns(n);
		//cout << "completed tree:" << endl;
		//print();
	}
}

//Public function:
void RedBlackTree::push(int val){ //add a data to the tree
	Node* newNode = new Node(val);
	addAfter(newNode, root, NULL);
}

//SEARCHING:
//Helper function:
int RedBlackTree::searchRec(Node* n, int val){ //search and return number of datas contained in tree with root n
	if(!n) return 0;
	else if (val > n->data) return searchRec(n->right, val);
	else if (val < n->data) return searchRec(n->left, val);
	else if (val == n->data) return 1 + searchRec(n->left, val) + searchRec(n->right, val);
}

//Public function:
int RedBlackTree::search(int val){ //return number of a data that exist in the tree
	return searchRec(root, val);
}


Node* RedBlackTree::inorderSuccessor(Node* n, bool right){ //pull the leftmost node out and return it
	if(!n) return NULL;
	//cout << "n->data = " << n->data << endl;
	if (right) { //searching the right side so will be traversing left (next highest)
		if (n->left) return inorderSuccessor(n->left, RIGHT);
		else return n;
	}
	else { //searching left tree so traversing right (next lowest)
		if (n->right) return inorderSuccessor(n->right, LEFT);
		else return n;
	}
}

void RedBlackTree::balanceRem(Node* n){
	Node* S = sibling(n);
	Node* P;
	if (n->parent) P = N->parent;
	
	//case 4: parent is red and sibling is black with two black children
	if (P && P->color == RED && S && S->color == BLACK &&
			((!S->right || S->right->color == BLACK) &&  (!S->left || S->left->color == BLACK))) {
		cout << "case 4" << endl;
		S->color = RED;
		P->color = BLACK;
		return;
	}
	
	//case 6: Sibling is black and outer child is red
	else if (S->color == BLACK && P && ((S == P->right && S->right && S->right->color == RED)
				|| (S == P->left && S->left && S->left->color == RED))){
		cout << "case 6" << endl;
		Node* outer;
		//right
		if (S == P->right){
			outer = S->right;
			rotate(P, LEFT);
		}
		//left
		else { 
			outer = S->left;
			rotate(P, RIGHT);
		}
		P->color = BLACK;
		outer->color = BLACK;
	}
	//case 3: Parent and Sibling are black, Sibling's children are black
	else if (P && P->color == BLACK && S && S->color == BLACK &&
			((!S->right || S->right->color == BLACK) &&  (!S->left || S->left->color == BLACK))){
		S->color = RED;
		balanceRem(P);
	}
	//case 5: Parent and Sibling are black, Sibling's outer child is black and inner child is red
	else if(P && P->color == BLACK && S->color == BLACK &&
			((S = P->right && (!S->right || S->right->color == BLACK) && S->left && S->left->color == RED)
			|| (S = P->left && (!S->left || S->left->color == BLACK) && S->right && S->right->color == RED))) {
		
		S->color = RED;

		if (S == P->right) {
			S->left->color = BLACK;
			rotate(S, RIGHT);
		}
		else {
			S->right->color = BLACK;
			rotate(S, LEFT);
		}
		balanceRem(N);
	}

}

int RedBlackTree::removeN(Node* n, int val){ //remove the first of a certain data in the tree
	if(!n) return 0;
	if (n->data == val){ //node to delete
		cout << "deleting" << endl;
		
		//simple cases:
		
		//simple case 1: n is the root and has two null children
		if (n == root && !n->left && !n->right){
			root = NULL;
		}

		//find the inorder successor
		Node* N;
		if (n->left) N = inorderSuccessor(n->left, LEFT);
		else if (n->right) N = inorderSuccessor(n->right, RIGHT);
		else N = n;

		//copy data from node to be deleted into n
		n->data = N->data;
		
		//N is red and has no children (simple case 2)
		if (N->color == RED && !N->left && !N->right){
			cout << "Delete Simple Case 2" << endl;
			
			//set parent pointer to NULL and delete it
			if (N == N->parent->right) N->parent->right = NULL;
			else N->parent->left = NULL;
			delete N;
			return 1;
		}

		//black node with one child and child is red, move the child to its place and delete (simple case 3)
		else if (N->color == BLACK && ((N->left && N->left->color == RED) || (N->right && N->right->color == RED))){
			cout << "Delete Simple Case 3" << endl;

			//delete N and move C into its place, change C to black
			Node* C;
			if (N->left){
				C = N->left;
				if (N == N->parent->right) N->parent->right = C;
				else N->parent->left = C;
			}
			else {
				C = N->right;
				if (N == N->parent->right) N->parent->right = C;
				else N->parent->left = C;
			}
			C->parent = N->parent;
			delete N;
		}
		
		//complex case:
		//black node with no red child
		else {
			N->data = INT_MIN;
			balanceRem(N);
			cout << "seg fault here" << endl;
			if (N == N->parent->right){ //may cause a seg fault
				N->parent->right = N->left;
			}
			else if (N == N->parent->left){
				N->parent->left = N->right;
			}
			cout << "wtf, no seg fault?" << endl;
		}

		//M is the node to be deleted from the tree
		
		return 1;
	}
	else if (n->data > val) return removeN(n->left, val);
	else return removeN(n->right, val);
}

//Public function:
int RedBlackTree::remove(int val){ //return the number of removed datas in the tree
	//cout << "ptr loc of 5 is " << root->left->left->right->left << endl;
	return removeN(root, val);
}
