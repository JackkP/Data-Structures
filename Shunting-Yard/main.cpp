/* Jack Porter, C++ Data Structures, Febuary 2022
 * Shunting yard algorithm
 */

#include <iostream>
#include <cstring>

using namespace std;

//node class for binary expression tree
class Bnode {
	public:
		Bnode(char* token);
		~Bnode();
		SetRight(Bnode* n);
		SetLeft(Bnode* n);
		Bnode* GetRight();
		Bnode* GetLeft();
	private:
		char* Token;
		Bnode* Right;
		Bnode* Left;

};

//constructor
Bnode::Bnode(char* token){
	Token = token;
	Right, Left = NULL;
}
//destructor
Bnode::~Bnode(){
	delete Token;
}
//set right pointer
Bnode::SetRight(Bnode* n){ Right = n; }
//set left pointer
Bnode::SetLeft(Bnode* n){ Left = n; }
//get right pointer
Bnode* Bnode::GetRight(){ return Right; }
//get left pointer
Bnode* Bnode::GetLeft(){ return Left; }

struct Node{ //node class for stack and queue functions
	Node* next;
	char* token;

};

//functions for stack
//add a pointer to the front of the list (top of stack)
void Push(Node* & head, Node* n){
	n->next = head;
	head = n;
}

//remove node from the top of the stack
Node* Pop(Node* & head){
	Node* n = head;
	head = head->next;
	return n;
}

//return the head pointer... why is this a function
Node* Peek(Node* head){
	return head;
}

//functions for queue
//add a node at the end using recurion
void Enqueue(Node* & head, Node* n){
	if(!head) { head = n; }
	Enqueue(head->next, n);
}

//remove the head pointer and return it (since the head is the front of the queue)
Node* Dequeue(Node* & head){
	if (head){
		Node* n = head;
		head = head->next;
		return n;
	}
	return NULL;
}

int main(){
	
	cout << "Shunting Yard Algorithm! << endl;
	while (true) {
		//formatting
		cout << "=====================================================" << endl;
		cout << "Functions: (, ), +, -, *, /, and ^\nInput an equation to start! or type 'quit' to quit" << endl;
		
		char next[100];
		cin.get(next, 100);
		cin.get();
		
		cout << "=====================================================" << endl;
		



	}

	return 0;
}
