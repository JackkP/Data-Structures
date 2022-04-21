// Binary Search Tree Project
// Jack Porter, C++ Data structures, April 2022

#include "BinaryTree.h"

#include <cstring>
#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>


using namespace std;

//(sensitive) function to split char array to vector of integers with a delimiter
//(copied from heap)
vector<int>* split(char* in, char delimiter);

int main(){
	cout << "Binary Search Tree Project!\nManipulates and displays data using a binary search tree!" << endl;
	srand(time(0));

	BinaryTree* tree = new BinaryTree;

	while (true) {
		//formatting
		cout << "====================================================================================" << endl;
		cout << "type \"read\" to add numbers from a file, \"input\" to add numbers manually,";
		cout << "\n\"generate\" to generate random numbers, \"delete\" to remove all of one number";
		cout << "\n\"search\" to see how many of a number are stored, or \"quit\" to exit the program" << endl;
		
		char next[2000];
		cin.get(next, 2000);
		cin.get();
	
		cout << "====================================================================================" << endl;

		if(strcmp(next, "quit") == 0){
			break;
		}

		else if(strcmp(next, "read") == 0){
			cout << "filename? (numbers should be seperated by spaces)" << endl;
			cin.get(next, 100);
			cin.get();
			cout << "====================================================================================" << endl;

			ifstream numberfile (next);
			//for reading from file:
			char* numberInput = new char[2000];
			numberfile.getline(numberInput, 2000);
			numberfile.close();
			
			vector<int>* splitArray = split(numberInput, ' '); //result vector
			//push all the integers in the output vector onto the maxheap
			for (vector<int>::iterator ptr = splitArray->begin(); ptr < splitArray->end(); ptr++) {
				tree->push(*ptr);
			}
			delete splitArray;
			tree->print();
		}
		else if(strcmp(next, "input") == 0){
			cout << "enter your numbers seperated by spaces" << endl;
			cin.get(next, 2000);
			cin.get();
			cout << "====================================================================================" << endl;

			vector<int>* splitArray = split(next, ' '); //result vector
			//push all the integers in the output vector onto the max heap
			for (vector<int>::iterator ptr = splitArray->begin(); ptr < splitArray->end(); ptr++) {
				tree->push(*ptr);
			}
			delete splitArray;
			tree->print();
		}
		else if(strcmp(next, "generate") == 0){
			cout << "how many numbers would you like to generate?" << endl;
			cin.get(next, 1000);
			cin.get();
			cout << "====================================================================================" << endl;
			int amount = atoi(next);
			
			for(int i = 0; i < amount; i++){ //add (amount) random numbers to the heap
				int number = rand()%11;
				tree->push(number); //add a random number between 0 and 100
			}
			tree->print();
		}
		else if (strcmp(next, "delete") == 0){
			cout << "what number would you like to remove?" << endl;
			cin.get(next, 100);
			cin.get();
			cout << "====================================================================================" << endl;

			int numremoved = tree->remove(atoi(next));
			if(numremoved == 0) cout << "The tree does not contain " << atoi(next) << endl;
			else cout << "successfully removed " << numremoved << " " <<atoi(next) << "s" << endl;
			tree->print();
		}
		else if (strcmp(next, "search") == 0){
			cout << "what number would you like to search for?" << endl;
			cin.get(next, 100);
			cin.get();
			int numfound = tree->search(atoi(next));
			if(numfound == 0) cout << "The tree does not contain " << atoi(next) << endl;
			else cout << "found " << numfound << " " <<atoi(next) << "s" << endl;
		}
		else {
			cout << "not a valid input, please try again" << endl;
		}
	}
}

vector<int>* split(char* in, char delimiter){
	vector<int>* list = new vector<int>;
	int startindex = 0; //start of the current word
	for(int i = 0; i < strlen(in); i++){
		if((in[i] == delimiter || i == strlen(in)) && startindex != i) { //if end of a word
			char newnum[i-startindex]; //new word string
			for(int j = 0; j < i-startindex; j++){ //copy to new word string
				newnum[j] = in[j+startindex];
			}
			newnum[i-startindex] = '\0';
			list->push_back(atoi(newnum)); //add to vector
			startindex = i; //update start of next word
		}
	}
	if(in[strlen(in)-1] != delimiter){ //last word
		char newnum[strlen(in)-startindex];
		for(int j = 0; j < strlen(in)-startindex; j++){
			newnum[j] = in[j+startindex];
		}
		newnum[strlen(in)-startindex] = '\0';
		list->push_back(atoi(newnum));
	}
	return list;
}
