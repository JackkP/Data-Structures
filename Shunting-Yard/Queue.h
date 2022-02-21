/* Jack Porter, C++ Data Structures, Febuary 2022
 * Stack class for Shunting yard algorithm
 */

#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <cstring>
#include "Node.h"

using namespace std;

class Queue{
	public:
		Queue();
		~Queue();
		void enqueue(Node* n);
		Node* dequeue();
		void print();
	private:
		Node* head;
		void printNext(Node* n);
		void deleteNext(Node* n);
		void enqueueAfter(Node* & h, Node* n);

};

#endif
