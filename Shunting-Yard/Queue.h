/* Jack Porter, C++ Data Structures, Febuary 2022
 * Stack class
 * Shunting yard algorithm
 */

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

};	
