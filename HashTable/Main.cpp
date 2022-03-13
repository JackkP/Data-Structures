/* Jack Porter, C++ Data Structures, March 2022
 * Hash Table Student List
 * 
 * Random name generator using file reader <fstream> from
 * https://www.cplusplus.com/doc/tutorial/files/
 */


#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>

using namespace std;

struct Student {
	int ID;
	float GPA;
	char* first, * last;
	~Student(){
		delete first;
		delete last;
	}
	Student(char* f, char* l, int id, float gpa){
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
	~Item(){
		delete student;
	}
};

void recPrint(Item* i){
	if(i) {
		cout << i->student->ID << " - " << i->student->last << ", ";
		cout << i->student->first << " - GPA: " << setprecision(2) << fixed << i->student->GPA << endl;
		recPrint(i->next);
	}
}

int getLLSize(Item* i){ //recursively find the length of a linked list
	if (i) {
		return 1+getLLSize(i->next);
	}
	return 0;
}

bool hasID(Item* i, int ID){ //return true if any item in this linked list has a student with the matching ID
	if (i){
		if (i->student->ID == ID) {return true;}
		return hasID(i->next, ID);
	}
	return false;
}

void recSearch(Item* i, char* keyword){ //print all the students in this linked list with a name or ID containing a keyword
	if (i){
		if (strstr(to_string(i->student->ID).c_str(), keyword) || strstr(i->student->first, keyword) || strstr(i->student->last, keyword)){
			cout << i->student->ID << " - " << i->student->last << ", " << i->student->first;
			cout << " - GPA: " << setprecision(2) << fixed << i->student->GPA << endl;

		}
		recSearch(i->next, keyword);
	}
}

struct HashTable { //hash table class (very big struct)
	int size = 100; //default size is 1
	Item** items;
	HashTable(int i){
		size = i;
		items = new Item*[size];
		for (int i = 0; i < size; i++) {
			items[i] = NULL;
		}
	}

	int modHash(int i){ //modulus hashfunction
		return i % size;
	}

	bool add(Student* s){
		int index = modHash(s->ID); //index of this student;
		if (getLLSize(items[index]) < 3) {//if there are less than 3 items at this index
			if (hasID(items[index], s->ID)) {
				return false;
			}
			else {
				Item* newItem = new Item(items[index], s); //add the new item
				newItem->next = items[index];
				items[index] = newItem;
				return true;
			}
		}
		else { //otherwise rehash and try again
			rehash();
			add(s);
		}
	}

	void rehash(){ //rehas the hash table to fit more values
		//cout << "rehashing" << endl; //debug code
		bool rehashAgain = false; //check if we need to rehash again
		
		size = size*2; //double the size of the array
		Item** oldArray = items; //store the old array
		items = new Item*[size]; //create new array
		for (int i = 0; i < size; i++) { //set all items pointers in the new array to NULL
			items[i] = NULL;
		}

		for (int i = 0; i < size/2; i++){ //for every slot in the old array
			while(oldArray[i]){//while there are items in this slot		
				
				Item* thisItem = oldArray[i]; //pull the top item off that slot and add it to the new array
				oldArray[i] = thisItem->next;

				int thisItemIndex = modHash(thisItem->student->ID); //index of the current item 
				thisItem->next = items[thisItemIndex]; //set the next pointer of the current item to the pointer currently at that index
				items[thisItemIndex] = thisItem; //push the item onto the new array

				// if there are more than three items in a slot in the new array then rehash again
				if (getLLSize(items[thisItemIndex]) > 3) rehashAgain = true;
			}
		}
		delete oldArray; //get rid of the old array
		if (rehashAgain) {rehash();}
	}

	void print(){ //print every item in the hashtable
		for (int i = 0; i < size; i++){
			recPrint(items[i]); //recursively print all the items in this linked list
		}
	}

	void printIncl(char* keyword){ //search function to print all students associated with a keyword (looks at ID, first name, last name)
		for (int i = 0; i < size; i++ ){
			recSearch(items[i], keyword);
		}
	}

	void recDelete(Item* & i, int ID){ //recursively delete the item and return true/false if successful
		if (i) {
			if (i->student->ID == ID){

				cout << "Successfully deleted " << i->student->ID << " - " << i->student->last << ", " << i->student->first;
				cout << " - GPA: " << setprecision(2) << fixed << i->student->GPA << endl;
				
				Item* toDelete = i;
				i = toDelete->next;
				delete toDelete;
				return;
			}
			recDelete(i->next, ID);
		}
		return;
	}

	void deleteID(int ID){ //delete a student by ID
		recDelete(items[modHash(ID)], ID);
	}

};


int main() {
	
	//generate tables for first and last names (for generate function)
	
	char** firstNames = new char*[1000];
	char** lastNames = new char*[1000];
	
	ifstream firstFile ("First.txt");
	ifstream lastFile ("Last.txt");

	for (int i = 0; i < 1000; i++){
		char* firstname = new char[50];
		firstFile.getline(firstname, 50);
		firstNames[i] = firstname;
		
		char* lastname = new char[50];
		lastFile.getline(lastname, 50);
		lastNames[i] = lastname;
	}
	firstFile.close();
	lastFile.close();

	cout << "Hash Table!" << endl;
	HashTable* hTbl = new HashTable(1);
	while (true) {
		//formatting
		cout << "=====================================================" << endl;
		cout << "Commands: 'print', 'add', 'search', 'delete', 'generate', or 'quit'" << endl;
		
		char next[200];
		cin.get(next, 200);
		cin.get();
		
		cout << "=====================================================" << endl;
		
		if(strcmp(next, "print") == 0){
			hTbl->print();
		}
		
		else if(strcmp(next, "add") == 0){
			//prompt all 4 pieces of information necessesary for a student
			char p[50];
			char* first = new char[50];
			cout << "First Name?" << endl;
			cin.get(first, 50);
			cin.get();
			char* last = new char[50];
			cout << "Last Name?" << endl;
			cin.get(last, 50);
			cin.get();

			cout << "GPA?" << endl;
			cin.get(p, 50);
			cin.get();
			float GPA = atof(p);
			cout << "ID?" << endl;
			cin.get(p, 50);
			cin.get();
			int ID = atoi(p);
			
			Student* newStudent = new Student(first, last, ID, GPA);
			if (!hTbl->add(newStudent)){
				cout << "A student with that ID already exists" << endl;
				delete newStudent;
			}
		}

		else if(strcmp(next, "delete") == 0){
			cout << "Type the ID of the student you would like to delete" << endl;
			char in[50];
			cin.get(in, 50);
			cin.get();
			int ID = atoi(in);
			hTbl->deleteID(ID);
		}
		else if(strcmp(next, "search") == 0) {
			cout << "Search students (by first name, last name, or ID, case sensitive):" << endl;
			char* keyword = new char[50];
			cin.get(keyword, 50);
			cin.get();
			hTbl->printIncl(keyword);
			delete keyword;
		}
		else if(strcmp(next, "generate") == 0){
			cout << "How many students would you like to generate?" << endl;
			char num[50];
			cin.get(num, 50);
			cin.get();
			int ammount = atoi(num);
			int numGenerated = 0;
			int iterateID = 0;
			while (numGenerated < ammount){ //very inefficient but if it fails to add (because of matching ID) then it just generates a new one
				float GPA = float(rand() % 300)/100 + 1; //random gpa between 1.00 and 4.00
				char* first = new char[50];
				strcpy(first, firstNames[rand()%1000]);
				char* last = new char[50];
				strcpy(last, lastNames[rand()%1000]);
				Student* newStudent = new Student(first, last, iterateID, GPA);
				//bool rslt = hTbl->add(newStudent);
				if (hTbl->add(newStudent)){
					numGenerated++;
				}
				iterateID++;
			}

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
