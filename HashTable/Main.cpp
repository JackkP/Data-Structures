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


int getLLSize(Item* i){ //recursively find the length of a linked list
	if (i) {
		return 1+getLLSize(i->next);
	}
	return 0;
}

bool hasID(Item* i, int ID){
	if (i){
		if (i->student->ID = ID) {return true;}
		return hasID(i->next);
	}
	return false;
}

struct hashTable {
	int size = 1; //default size is 1
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
		if (getLLSize(items[index]) < 3) {//if there are less than 3 items at this index
			if 
			Item* newItem = new Item(items[index], s); //add the new item
			newItem->next = items[index];
			items[index] = newItem;
		}
		else { //otherwise rehash and try again
			rehash();
			add(s);
		}
	}
	void rehash(){
		cout << "rehashing" << endl;
		bool rehashAgain = false; //check if we need to rehash again
		size = size*2; //double the size of the array
		Item** oldArray = items; //store the old array
		items = new Item*[size]; //create new array (double size of old array)
		for (int i = 0; i < size; i++) { //set all items pointers in the new array to NULL
			items[i] = NULL;
		}
		for (int i = 0; i < size/2; i++){ //for every slot in the old array
			while(oldArray[i]){//while there are items in this slot		
				Item* thisItem = oldArray[i]; //pull the top item off that slot and add it to the new array
				oldArray[i] = thisItem->next;
				int thisItemIndex = thisItem->student->ID % size;
				thisItem->next = items[thisItemIndex];
				items[thisItemIndex] = thisItem;
				// if there are more than three items in a slot in the new array then rehash again
				if (getLLSize(items[thisItemIndex]) > 3) rehashAgain = true;
			}
		}
		delete oldArray; //get rid of the old array
		if (rehashAgain) {rehash();}
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
