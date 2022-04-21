// Binary Search Tree, Jack Porter, C++ Data Structures April 2022

#include "BinaryTree.h"
#include <iostream>
#include <cstring>

using namespace std;


//function to print branches of the binary tree
void BinaryTree::showBranches(Branch* p){
	if (p) {
		//cout << *p->str << "+";
		showBranches(p->prev); //print the previous branch (in this line)
		cout << p->str;
	}
}
//function to print binary tree with branches from https://www.techiedelight.com/c-program-print-binary-tree/
void BinaryTree::printTree(Node* n, Branch* prev, bool isLeft) {
    if (!n) {
        return;
    }

    char prev_str[10];
    strcpy(prev_str, "    ");
    Branch* branch = new Branch(); //new branch for this node
    branch->prev = prev;
    strcpy(branch->str, prev_str);
    //cout << "node value = " << n->value << endl;
    //cout << "branch->str = " << branch->str << endl;
    //printf ("branch->prev = %d\n", branch->prev);
    //cout << 1 << endl;
    //if (branch->prev == NULL) cout << "1.4" << endl;
    //if (branch->prev) printf ("branch->prev->str = %d\n", branch->prev->str);
    //cout << 1.5 << endl;
    //if (branch->prev) if (branch->prev->str) cout << "first branch (prev != NULL) ->prev->str: " << branch->prev->str << endl;
    //cout << 2 << endl;
    printTree(n->right, branch, true); //print the tree for the right most branch
    //cout << 3 << endl;

    if (!prev) {
	//cout << "!prev" << endl;
	strcpy(branch->str, "———");
    }
    else if (isLeft){
	//cout << "isleft" << endl;
	strcpy(branch->str, ".———");
        strcpy(prev_str, "    |");
	//cout << "prev_str = " << prev_str << endl;
    }
    else {
	//cout << "else" << endl;
	strcpy(branch->str, "`———");
        strcpy(prev->str, prev_str);
    }
    //cout << n->value << endl;
    //cout << "branch->str = " << branch->str << endl;
    /*if (branch->prev){
	    cout << "branch->prev: " << branch->prev << endl;
	    cout << "branch->prev->str = " << branch->prev->str << endl;
    }*/
    //cout << 4 << endl;
    showBranches(branch);
    cout << " " << n->value << endl;
    
    //cout << 5 << endl;
    if (prev) {	
	//cout << "prev" << endl;
        strcpy(prev->str, prev_str);
    }
    //cout << 6 << endl;
    strcpy(branch->str, "    |");
    //cout << 7 << endl;
    printTree(n->left, branch, false);
    //cout << 8 << endl;
}


void BinaryTree::printRec(Node* n, int space) {
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

void BinaryTree::print(){
	cout << endl;
	printRec(head, 0); //print starting at the head
	
	cout << "with branches:\n\n" << endl; 
	cout << endl;
	printTree(head, NULL, false);
}

BinaryTree::BinaryTree(){
	head = NULL;
}

void deleteRec(Node* n){
	if (n) {
		deleteRec(n->right);
		deleteRec(n->left);
		delete n;
	}
}

BinaryTree::~BinaryTree(){
	deleteRec(head);
}

void BinaryTree::addAfter(Node* val, Node* &n){ //recursively add node to binary tree
	if (n) {
		if (val->value >= n->value) {
			addAfter(val, n->right); //add it to the right because it is greater than or equal to n
		}
		else if (val->value < n->value){ //add it to the left because it less than n
			addAfter(val, n->left);
		}
	}
	else n = val;
}

void BinaryTree::push(int val){
	Node* newNode = new Node(val);
	addAfter(newNode, head);
}

int BinaryTree::search(int val){


}

int BinaryTree::remove(int val){


}
