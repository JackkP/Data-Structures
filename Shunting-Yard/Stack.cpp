/* Jack Porter, C++ Data Structures, February 2022
 * Stack Class for Shunting Yard Algorithm
 */


#include "Stack.h"

using namespace std;

Stack::Stack(){
	head = NULL;
}

Stack::~Stack(){
	deleteNext(head);
}


void Stack::print(){ //debug function
	//cout << "head/top to tail/bottom: ";
	printNext(head);
	cout << endl;
}

void Stack::printNext(Node* n){ //recursive print
	if(n){
		cout << " " << n->token;
		printNext(n->next);
	}
}

void Stack::deleteNext(Node* n){
	if(n) { //if this pointer is not null
		deleteNext(n->next); //delete the one after it
		delete n; //delete it
	}
}

//functions for stack
//add a pointer to the front of the list (top of stack)
void Stack::push(Node* n){
        n->next = head;
        head = n;
}

//remove node from the top of the stack
Node* Stack::pop(){
        Node* n = head;
        if (head) head = head->next;
        return n;
}

//return the head pointer... why is this a function
Node* Stack::peek(){
        return head;
}

