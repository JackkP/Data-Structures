/* Jack Porter, C++ Data Structures, February, 2022
 * Stack Class for Shunting Yard Algorithm
 */

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <cstring>
#include "Node.h"


using namespace std;

class Stack{
	public:
		Stack();
		~Stack();
		void push(Node* n);
		Node* pop();
		Node* peek();
	private:
		Node* head;
		deleteNext(Node* n);
};

#endif
