/* Jack Porter, C++ Data Structures, February 2022
 * Queue class for Shunting Yard Algorithm
 */

#include "Queue.h"

Queue::Queue(){
	head = NULL;
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

void Queue::print(){ //debug function
	//cout << "head/front to tail/back: ";
	printNext(head);
	cout << endl;
}

void Queue::printNext(Node* n){ //recursive print
	if(n){
		cout << " " << n->token;
		printNext(n->next);
	}
}

//functions for queue
//add a node at the end using recursion
void Queue::enqueueAfter(Node* & h, Node* n){
	if(!h) { h = n; }
	else enqueueAfter(h->next, n);
}
void Queue::enqueue(Node* n){
	n->next = NULL; //this is to make sure that there are no accidental loops
	if(!head) { head = n; }
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
