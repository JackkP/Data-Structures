/* Jack Porter, C++ Data Structures, March 2022
 * Heap project, creates a binary tree/max heap, displays it,
 * and prints a sorted list of numbers by removing the values from the top of the heap
 */

#include "Heap.h"

#include <cstring>
#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>

using namespace std;

void printHeap(Heap* heap){
	//print the tree
	cout << "\nVisualized as a tree:\n" << endl;
	heap->print();
	
	//remove the items from the tree one by one and print those as a list
	int top = heap->pop();
	cout << "\nSorted list:" << endl;
	while (top != INT_MIN){
		cout << top << " ";
		top = heap->pop();
	}
	cout << endl;
}

//(sensitive) function to split char array to vector of integers with a delimiter
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

int main(){
	cout << "Heap Project!\nSorts and displays data using a max heap data structure." << endl;
	srand(time(0));
	while (true) {
		//formatting
		cout << "====================================================================================" << endl;
		cout << "type \"read\" to read in numbers from a file, \"input\" to input numbers manually,";
		cout << "\n \"generate\" to generate random numbers, or \"quit\" to exit the program" << endl;
		
		char next[2000];
		cin.get(next, 2000);
		cin.get();
		
		cout << "====================================================================================" << endl;
		
		Heap* heap = NULL;

		if(strcmp(next, "quit") == 0){
			break;
		}
		else if(strcmp(next, "read") == 0){
			cout << "filename? (numbers should be seperated by spaces, up to 100 numbers)" << endl;
			cin.get(next, 100);
			cin.get();
			
			ifstream numberfile (next);
			//for reading from file:
			char* numberInput = new char[2000];
			numberfile.getline(numberInput, 2000);
			numberfile.close();
			
			heap = new Heap();

			vector<int>* splitArray = split(numberInput, ' '); //result vector
			//push all the integers in the output vector onto the maxheap
			for (vector<int>::iterator ptr = splitArray->begin(); ptr < splitArray->end(); ptr++) {
				heap->push(*ptr);
			}
			
			//print the heap
			printHeap(heap);

			delete splitArray;
			delete heap;
		}
		else if(strcmp(next, "input") == 0){
			cout << "enter your numbers seperated by spaces, no extra spaces, up to 100 numbers" << endl;
			cin.get(next, 2000);
			cin.get();
			
			heap = new Heap();

			vector<int>* splitArray = split(next, ' '); //result vector
			//push all the integers in the output vector onto the max heap
			for (vector<int>::iterator ptr = splitArray->begin(); ptr < splitArray->end(); ptr++) {
				heap->push(*ptr);
			}
			
			//print the heap
			printHeap(heap);

			delete splitArray;
			delete heap;

		}
		else if(strcmp(next, "generate") == 0){
			cout << "how many numbers would you like to generate? (up to 100)" << endl;
			cin.get(next, 1000);
			cin.get();
			int amount = atoi(next);
			
			heap = new Heap(); //create a new heap
			
			for(int i = 0; i < amount; i++){ //add (amount) random numbers to the heap
				int number = rand()%1001;
				heap->push(number); //add a random number between 0 and 100
			}
			printHeap(heap); //print it
			delete heap; //get rid of it
		}
		else {
			cout << "not a valid input, please try again" << endl;
		}
	}
}
