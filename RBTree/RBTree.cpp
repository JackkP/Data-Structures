// Red Black Tree, Jack Porter, C++ Data Structures April 2022

#include "RBTree.h"
#include <iostream>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;

#define RIGHT true
#define LEFT false

//CONSTRUCTOR:
//Public function:
RBTree::RBTree(){
	root = NULL;
}

//DESTRUCTOR:
//Helper function:
void RBTree::deleteRec(Node* n){ //recursively delete all nodes from tree with root n
	if (n) {
		deleteRec(n->right);
		deleteRec(n->left);
		delete n;
	}
}

//Public function:
RBTree::~RBTree(){
	deleteRec(root);
}



//PRINTING:
//Helper functions:
//function to print branches of the binary tree
void RBTree::showBranches(Branch* p){
	if (p) {
		showBranches(p->prev); //print the previous branch (in this line)
		cout << p->str;
	}
}

//function to print binary tree with branches based on (almost identical to) https://www.techiedelight.com/c-program-print-binary-tree/
void RBTree::printTree(Node* n, Branch* prev, bool isRight) {
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
	
	//debug code to show parent value
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

//Public function:
void RBTree::print(){
	cout << endl;
	printTree(root, NULL, false);
	cout << endl;
}


//MANIPULATION:
//function to rotate a tree through P
void RBTree::rotate(Node* P, bool right){
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

//function to return the uncle of a node
Node* RBTree::uncle(Node* n){
	if (n->parent && n->parent->parent){ //n has a grandparent
		if (n->parent == n->parent->parent->left) return n->parent->parent->right;
		else if (n->parent = n->parent->parent->right) return n->parent->parent->left;
	}
	else return NULL;
}

//function to return the sibling
Node* RBTree::sibling(Node* n){ //return the sibling
	if (n->parent && n == n->parent->right) return n->parent->left;
	else if (n->parent && n == n->parent->left) return n->parent->right;
	else return NULL;
}


//PUSHING:
//ballance the tree after inserting a node
void RBTree::balanceIns(Node* n){
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

//Helper function:
void RBTree::addAfter(Node* val, Node* &n, Node* parent){ //recursively add node to binary tree
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
void RBTree::push(int val){ //add a data to the tree
	Node* newNode = new Node(val);
	addAfter(newNode, root, NULL);
}


//SEARCHING:
//Helper function:
int RBTree::searchRec(Node* n, int val){ //search and return number of datas contained in tree with root n
	if(!n) return 0;
	else if (val > n->data) return searchRec(n->right, val);
	else if (val < n->data) return searchRec(n->left, val);
	else if (val == n->data) return 1 + searchRec(n->left, val) + searchRec(n->right, val);
}

//Public function:
int RBTree::search(int val){ //return number of a data that exist in the tree
	return searchRec(root, val);
}


//VERIFICATION (used for debugging):
//Helper function:
//returns the number of black nodes in the sub tree or a very large negative number if the rb tree is not valid
int RBTree::verR(Node* n){
	if (!n) return 0;
	int countL = verR(n->left);
	int countR = verR(n->right);
	
	//n is root it must be black
	if (n == root && n->color == RED){
		cout << "root is red" << endl;
		return INT_MIN;
	}
	//number of black nodes must be the same
	if (countR != countL){
		cout << "unequal counts" << endl;
		return INT_MIN;
	}
	//if n is red it must have two black children
	if (n->color == RED && !((!n->left || n->left->color == BLACK) && (!n->right || n->right->color == BLACK))) {
		cout << "red with one non-black child" << endl;
		return INT_MIN;
	}
	//left must be smaller or equal and right must be greater or equal
	if ((n->right && n->right->data < n->data) || (n->left && n->left->data > n->data)){
		cout << "Violates bst" << endl;
		return INT_MIN;
	}
	if (n->color == BLACK) return 1 + countL;
	else return 0 + countL;
}

//Public function:
//returns true if the tree is a valid red black tree
bool RBTree::verify(){
	int count = verR(root);
	if (count < 0) {
		return false;
	}
	else {
		return true;
	}
}


//DELETION:
//Helper function:
//Return the inorder successor to a node to be deleted
Node* RBTree::inorderSuccessor(Node* n, bool right){
	if(!n) return NULL;
	//cout << "n->data = " << n->data << endl;
	
	//searching the right side so will be traversing left (next highest)
	if (right) {
		if (n->left) return inorderSuccessor(n->left, RIGHT);
		else return n;
	}
	
	//searching left tree so traversing right (next lowest)
	else {
		if (n->right) return inorderSuccessor(n->right, LEFT);
		else return n;
	}
}

//Helper function:
//Balance the tree before removing n
void RBTree::balanceRem(Node* n){
	Node* S = sibling(n);
	Node* P;
	if (n->parent) P = n->parent;
	
	//case 4: parent is red and sibling is black with two black children
	if (P && P->color == RED && S && S->color == BLACK &&
			((!S->right || S->right->color == BLACK) &&  (!S->left || S->left->color == BLACK))) {
		//cout << "Complex case 4" << endl;
		S->color = RED;
		P->color = BLACK;
		//print();
		return;
	}
	
	//case 6: Sibling is black and outer child is red
	else if (S && S->color == BLACK && P && ((S == P->right && S->right && S->right->color == RED)
				|| (S == P->left && S->left && S->left->color == RED))){
		//cout << "Complex case 6" << endl;
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
		S->color = P->color;
		P->color = BLACK;
		outer->color = BLACK;
		//print();
		return;
	}

	//case 3: Parent and Sibling are black, Sibling's children are black
	else if (P && P->color == BLACK && S && S->color == BLACK &&
			((!S->right || S->right->color == BLACK) &&  (!S->left || S->left->color == BLACK))){
		//cout << "Complex case 3" << endl;
		S->color = RED;
		//print();
		balanceRem(P);
	}
	
	//case 5: Parent and Sibling are black, Sibling's outer child is black and inner child is red
	else if(S && S->color == BLACK &&
			((S == P->right && (!S->right || S->right->color == BLACK) && S->left && S->left->color == RED)
			|| (S == P->left && (!S->left || S->left->color == BLACK) && S->right && S->right->color == RED))) {
		
		//cout << "Complex case 5" << endl;

		S->color = RED;

		if (S == P->right) {
			S->left->color = BLACK;
			rotate(S, RIGHT);
		}
		else {
			S->right->color = BLACK;
			rotate(S, LEFT);
		}
		//print();
		balanceRem(n);
	}
	
	//case 2: Parent is black, Sibling is red with 2 black children
	//else 
	else if(P && P->color == BLACK && S && S->color == RED &&
			(!S->right || S->right->color == BLACK) && (!S->left || S->left->color == BLACK)){
		cout << "Complex case 2" << endl;
		S->color = BLACK;
		P->color = RED;
		if (S == P->right) rotate(P, LEFT);
		else rotate(P, RIGHT);
		//print();
		balanceRem(n);
	}
}

//helper function:
//Removes the first node where n is equal to val
int RBTree::removeN(Node* n, int val){
	if(!n) return 0;
	if (n->data == val){ //node to delete
		//cout << "deleting " << val << endl;
		
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

		//cout << "inorder successor = " << N->data << endl;

		//copy data from node to be deleted into n
		n->data = N->data;
		
		//N is red and has no children (simple case 2)
		if (N->color == RED && !N->left && !N->right){
			//cout << "Delete Simple Case 2" << endl;
			
			//set parent pointer to NULL and delete it
			if (N == N->parent->right) N->parent->right = NULL;
			else N->parent->left = NULL;
			delete N;
			return 1;
		}

		//black node with one child and child is red, move the child to its place and delete (simple case 3)
		else if (N->color == BLACK && ((N->left && N->left->color == RED) || (N->right && N->right->color == RED))){
			//cout << "Delete Simple Case 3" << endl;

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
			C->color = BLACK;
			delete N;
		}
		
		//complex case:
		//black node with no red child
		else {
			//cout << "complex case" << endl;
			balanceRem(N);
			if (N->parent && N == N->parent->right){
				N->parent->right = N->left;
			}
			else if (N->parent && N == N->parent->left){
				N->parent->left = N->right;
			}
			else if (N == root) root == NULL;
			delete N;
		}

		//M is the node to be deleted from the tree
		
		return 1;
	}
	else if (n->data > val) return removeN(n->left, val);
	else return removeN(n->right, val);
}

//Public function:
int RBTree::remove(int val){ //return the number of removed datas in the tree
	return removeN(root, val);
}
