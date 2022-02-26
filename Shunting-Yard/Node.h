/* Jack Porter, C++ Data Structures, February 2022
 * Node struct to be used in shunting yard algorithm 
 */

#ifndef NODE_H
#define NODE_H
#include "Bnode.h"

struct Node{
	Node* next;
	char* token;
	Bnode* bnode;

	~Node(){ //destructor used to delete node when calling queue destructor
		delete token;
	}
};

#endif
