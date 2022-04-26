// node struct for Red Black Tree Project
// Jack Porter, C++ Data Structures, April 2022

#ifndef NODE_H
#define NODE_H
#include <cstddef>

#define RED true
#define BLACK false

struct Node {
	Node* right;
	Node* left;
	Node* parent;
	int value;
	bool color;

	Node(int val){
		value = val;
		right = NULL;
		left = NULL;
		parent = NULL;
		color = RED;
	}
};
#endif
