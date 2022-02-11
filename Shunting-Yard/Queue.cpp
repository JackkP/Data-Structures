#include "Queue.h"

Queue::Queue(Node* h){
	head = h;
}

Queue::~Queue(){
	deleteNext(head); //recursively delete all remaining nodes in the queue
}

void Queue::deleteNext(Node* n){
	if(n) { //if this pointer is not null
		deleteNext(n->next); //delete the one after it
		delete n; //delete it
	}
}

//functions for queue
//add a node at the end using recursion
void Queue::enqueue(Node* n){
	if(!head) { head = n; }
	enqueue(head->next, n);
}

//remove the head pointer and return it (since the head is the front of the queue)
Queue::dequeue(){
	if (head){
		Node* n = head;
		head = head->next;
		return n;
	}
	return NULL;
}
