/* Jack Porter, C++ Data Structures, Febuary 2022
 * Shunting yard algorithm
 */

#include <iostream>
#include <cstring>

using namespace std;

struct Node{ //node class for stack and queue functions
	Node* next;
	char* token;

};

//functions for stack
//add a pointer to the front of the list (top of stack)
void push(Node* & head, Node* n){
	n->next = head;
	head = n;
}

//remove node from the top of the stack
Node* pop(Node* & head){
	Node* n = head;
	head = head->next;
	return n;
}

//return the head pointer... why is this a function
Node* peek(Node* head){
	return head;
}

//functions for queue
//add a node at the end using recurion
void enqueue(Node* & head, Node* n){
	if(!head) { head = n; }
	enqueue(head->next, n);
}

//remove the head pointer and return it (since the head is the front of the queue)
Node* dequeue(Node* & head){
	if (head){
		Node* n = head;
		head = head->next;
		return n;
	}
	return NULL;
}

int main(){
	
	cout << "Shunting Yard Algorithm!" << endl;
	while (true) {
		//formatting
		cout << "=====================================================" << endl;
		cout << "Functions: (, ), +, -, *, /, and ^\nInput an equation to start! or type 'quit' to quit" << endl;
		
		char next[100];
		cin.get(next, 100);
		cin.get();
		
		cout << "=====================================================" << endl;
		
		if(strcmp(next, "quit") == 0){
			break
		}
		
		else{
			
		}



	}

	return 0;
}
