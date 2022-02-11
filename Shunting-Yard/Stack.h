/* Jack Porter, C++ Data Structures, February, 2022
 * Stack Class for Shunting Yard Algorithm
 */

#include <iostream>
#include <cstring>

using namespace std;

struct Node{ //node class for stack and queue functions
        Node* next;
        char* token;
	~Node(){ //destructor used to delete node when calling queue destructor
		delete token;
	}

};

class Stack{
	public:
		Stack(Node* h);
		~Stack();
		void push(Node* n);
		Node* pop();
		Node* peek();
	private:
		Node* head;
		deleteNext(Node* n);
};
