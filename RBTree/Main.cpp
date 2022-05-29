// Red Black Tree Tree Project
// Jack Porter, C++ Data structures, April 2022

#include "RedBlackTree.h"

#include <cstring>
#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>


using namespace std;

//(sensitive) function to split char array to vector of integers with a delimiter
//(copied from heap)
vector<int>* split(char* in, char delimiter);
void printMenu();

int main(){

	cout << "Binary Search Tree Project!\nManipulates and displays data using a binary search tree!" << endl;
	srand(time(0));
	
	cout << "====================================================================================" << endl;
	printMenu();
	RedBlackTree* tree = new RedBlackTree();

	while (true) {
		//formatting
		cout << "====================================================================================" << endl;
		char next[2000];
		cin.get(next, 2000);
		cin.get();
	
		//cout << "====================================================================================" << endl;

		if(strcmp(next, "quit") == 0 || strcmp(next, "q") == 0 || strcmp(next, "exit") == 0){
			break;
		}
		if(strcmp(next, "h") == 0 || strcmp(next, "help") == 0){
			printMenu();
		}

		else if(strcmp(next, "read") == 0 || strcmp(next, "r") == 0){
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
		else if(strcmp(next, "input") == 0 || strcmp(next, "i") == 0 || strcmp(next, "add") == 0){
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
		else if(strcmp(next, "generate") == 0 || strcmp(next, "g") == 0 || strcmp(next, "gen") == 0){
			cout << "how many numbers would you like to generate?" << endl;
			cin.get(next, 1000);
			cin.get();
			cout << "====================================================================================" << endl;
			int amount = atoi(next);
			
			for(int i = 0; i < amount; i++){ //add (amount) random numbers to the heap
				int number = rand()%101;
				tree->push(number); //add a random number between 0 and 100
			}
			tree->print();
		}
		else if (strcmp(next, "remove") == 0 || strcmp(next, "rm") == 0 || strcmp(next, "del") == 0){
			cout << "what number would you like to remove?" << endl;
			cin.get(next, 100);
			cin.get();
			cout << "====================================================================================" << endl;

			int numremoved = tree->remove(atoi(next));
			if(numremoved == 0) cout << "The tree does not contain " << atoi(next) << endl;
			else cout << "successfully removed " << numremoved << " " <<atoi(next) << "s" << endl;
			tree->print();
		}
		else if (strcmp(next, "search") == 0 || strcmp(next, "s") == 0){
			cout << "what number would you like to search for?" << endl;
			cin.get(next, 100);
			cin.get();
			int numfound = tree->search(atoi(next));
			if(numfound == 0) cout << "The tree does not contain " << atoi(next) << endl;
			else cout << "found " << numfound << " " <<atoi(next);
			if (numfound > 1) cout << "s" << endl;
			else cout << endl;
		}
		else if (strcmp(next, "clear") == 0 || strcmp(next, "clr") == 0 || strcmp(next, "c") == 0){
			delete tree;
			tree = new RedBlackTree();
			cout << "cleared tree" << endl;
		}
		else if (strcmp(next, "print") == 0 || strcmp(next, "p") == 0) {
			tree->print();
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

void printMenu(){ //print a command menu
	cout << "  h, help\t\t - print this menu" << endl;
	cout << "  q, quit, exit\t\t - exit the program\n" << endl;
	cout << "  r, read\t\t - add numbers from a file" << endl;
	cout << "  i, input, add\t\t - add numbers manually" << endl;
	cout << "  g, gen, generate\t - generate random numbers" << endl;
	cout << "  p, print\t\t - print the working tree" << endl;
	cout << "  s, search\t\t - see how many of a number are stored" << endl;
	cout << "  rm, del, remove\t - remove all of one number" << endl;
	cout << "  c, clr, clear\t\t - clear the working tree" << endl;
}
