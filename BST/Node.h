// node struct or binary tree
// Jack Porter, C++ Data Structures, April 2022

#ifndef NODE_H
#define NODE_H
#include <cstddef>

struct Node {
	Node* right;
	Node* left;
	int value;

	Node(int val){
		value = val;
		right = NULL;
		left = NULL;
	}
};
#endif
