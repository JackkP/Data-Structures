/* Jack Porter, C++ Data Structures, February 2022
 * Queue class for Shunting Yard Algorithm
 */

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
void Queue::enqueueAfter(Node* & h, Node* n){
	if(!h) { h = n; }
	else enqueueAfter(h->next, n);
}
void Queue::enqueue(Node* n){
	if(head == 0) { head = n; }
	else enqueueAfter(head->next, n);
}

//remove the head pointer and return it (since the head is the front of the queue)
Node* Queue::dequeue(){
	if (head){
		Node* n = head;
		head = head->next;
		return n;
	}
	return NULL;
}
