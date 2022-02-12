/* Jack Porter, C++ Data Structures, Febuary 2022
 * Stack class for Shunting yard algorithm
 */

#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <cstring>

using namespace std;

struct Node{
	Node* next;
	char* token;
	
	~Node(){ //destructor used to delete node when calling queue destructor
		delete token;
	}
};

class Queue{
	public:
		Queue(Node* h);
		~Queue();
		void enqueue(Node* n);
		Node* dequeue();
	private:
		Node* head;
		void deleteNext(Node* n);
		void enqueueAfter(Node* & h, Node* n);

};

#endif
