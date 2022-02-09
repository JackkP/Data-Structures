#include "STACK.H"

using namespace std;

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

