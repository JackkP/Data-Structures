/* Jack Porter, C++ Data Structures, March 2022
 * Hash Table Student List
 */


#include <iostream>
#include <cstring>

using namespace std;

struct Student {
	int ID;
	float GPA;
	char* first, * last;
	~Student(){
		delete first;
		delete last;
	}
	Struct(char* f, char* l, int id, float gpa){
		first = f;
		last = l;
		ID = id;
		GPA = gpa;
	}
};

struct Item {
	Item* next;
	Student* student;
	Item(Item* i, Student* s){
		next = i;
		student = s;
	}
};

void recPrint(Item* i){
	if(i) {
		cout << i->student->ID << ", " << i->student->last << ", ";
		cout << i->student->first << " GPA: " << i->student->GPA << endl;
		recPrint(i->next);
	}
}

struct hashTable {
	int size = 0;
	Item** items;
	hashTable(int i){
		size = i;
		items = new Item*[size];
		for (int i = 0; i < size; i++) {
			items[i] = NULL;
		}
	}
	void add(Student* s){
		int index = s->ID % size; //index of this student;
		//if there are less than 3 items at this index
		Item* newItem = new Item(items[index], s); //add the new item
		items[index]
		//otherwise rehash and check again
	}
	void rehash(){
		
	}
	void print(){
		for (int i = 0; i < size; i++){
			recPrint(items[i]); //print all the items in this linked list
		}
	}
};

int main() {
	cout << "Hash Table!" << endl;
	while (true) {
		//formatting
		cout << "=====================================================" << endl;
		cout << "Commands: 'print', 'add', 'delete', 'generate', or 'quit'" << endl;
		
		char next[200];
		cin.get(next, 200);
		cin.get();
		
		cout << "=====================================================" << endl;
		
		if(strcmp(next, "print") == 0){
		
		}
		
		else if(strcmp(next, "add") == 0){
		}

		else if(strcmp(next, "delete") == 0){
		}
		else if(strcmp(next, "generate") == 0){
			
		}
		else if (strcmp(next, "quit") == 0){
			break;
		}
		else{
			cout << "Not a valid command" << endl;
		}

	}
	return 0;
}
