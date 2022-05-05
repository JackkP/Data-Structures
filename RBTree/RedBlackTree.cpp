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

void RedBlackTree::balance(Node* &n){
	if (!n) return;
	cout << "balancing" << endl;
	if (n == head) { //case 1, inserting at the root
		cout << "case 1" << endl;
		n->color = BLACK;
		return;
	}
	
	else if (n->parent->color == BLACK){ //case 2, parent is black
		cout << "case 1" << endl;
		return; 
	}
	
	else if (uncle(n) && n->parent->color == RED && uncle(n)->color == RED){ //case 3, parent and uncle are both red
		cout << "case 3" << endl;
		n->parent->color = BLACK;
		n->parent->parent->color = RED;
		uncle(n)->color = BLACK;
		balance(n->parent->parent); 
	}
	//case 4, (node left, parent right)||(node right, parent left), uncle is black, parent is red
	else if (n->parent->color == RED && n->parent->parent 
			&& (!uncle(n) || uncle(n)->color == BLACK)
			&& (n == n->parent->left && n->parent == n->parent->parent->right 
				|| n == n->parent->right && n->parent == n->parent->parent->left)){// parent is red and n->grandparent != NULL, uncle is black, node is inside grandchild, case 4
		cout << "case 4";
		if (n == n->parent->left && n->parent == n->parent->parent->right){ //node is the inside grandchild to the right, case 4 
			//rotate to the right through parent
			cout << "p=r, n=l" << endl;
			Node* G = n->parent->parent;
			Node* P = n->parent;
			G->right = n;
			n->parent = G;
			P->left = n->right;
			if (p->left) p->left->parent = P;
			n->right = P;
			P->parent = n;
			balance(P);
		}
		else if (n == n->parent->right && n->parent == n->parent->parent->left){ //node is the inside grandchild to the left, case 4
			//rotate to the left through parent
			cout << "p=l, n=r" << endl;
			Node* G = n->parent->parent;
			Node* P = n->parent;
			G->left = n;
			n->parent = G;
			P->right = n->left;
			if (p->right) p->right->parent = p;
			n->left = P;
			P->parent = n;
			balance(P);
		}
	}
	else if (n->color == RED && n->parent->color == RED && n->parent->parent //n is red, parent is red, has a grandparent
			&& (!uncle(n) || uncle(n)->color == BLACK) //uncle is black
			&& (n == n->parent->left && n->parent == n->parent->parent->left || //left left or right right
				n == n->parent->right && n->parent == n->parent->parent->right)) { //case 5
		cout << "case 4";
		if (n == n->parent->left && n->parent == n->parent->parent->leftt){ //node is the outside grandchild to the left, case 5 
			cout << "p=l, n=l" << endl;
			Node* G = n->parent->parent;
			Node* P = n->parent;
			G->left = P->right;
			if (G->left) G->left->parent = G;
			//todo: finish rotation through grandparent

		}
		else if (n == n->parent->right && n->parent == n->parent->parent->right){ //node is the outside grandchild to the right, case 5
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
		balance(n);
	}
}

//Public function:
void RedBlackTree::push(int val){ //add a value to the tree
	Node* newNode = new Node(val);
	addAfter(newNode, head, NULL);
}

int RedBlackTree::remove(int val){

}

int RedBlackTree::search(int val){

}
