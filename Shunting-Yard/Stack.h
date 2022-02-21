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
		void print();
		Node* pop();
		Node* peek();
	private:
		Node* head;
		void printNext(Node* n);
		void deleteNext(Node* n);
};

#endif
