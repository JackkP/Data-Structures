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
void Push(Node* head, Node* n){
	n->next = head;
	head = n;
}
Node* Pop(Node* head){
	Node* n = n
	head = head
	return n
}
Node* Peek(Node* head){
	return head;
}

//functions for queue
void Enqueue();
Node* Dequeue();

int main(){
	
	return 0;
}
