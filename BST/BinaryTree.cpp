// Binary Search Tree, Jack Porter, C++ Data Structures April 2022

#include "BinaryTree.h"


using namespace std;

void BinaryTree::printRec(Node* n, int space) {
	if (!n) return;
	
	// Increase distance between levels by 10 spaces
	space += 10;
	
	//Print right child tree first
	printRec(n->right, space);
	
	// Print current value after space
	for (int i = 10; i < space; i++)
        	cout<<" ";
    	cout<<n->value<<"\n";

	//Print left child tree
	printRec(n->left, space);
}

void BinaryTree::print(){
	cout << endl;
	printRec(head, 0); //print starting at the head
}

BinaryTree::BinaryTree(){
	head = NULL;
}

BinaryTree::addAfter(Node* val, Node* &n){ //recursively add node to binary tree
	if (n) {
		if (val->value >= n) {
			addAfter(val, n->right); //add it to the right because it is greater than or equal to n
		}
		else if (val->value < n){ //add it to the left because it less than n
			addAfter(val, n->left);
		}
	}
	else n = val;
}

BinaryTree::add(int val){
	Node* newNode = new Node(val);
	addAfter(newNode, head);
}
