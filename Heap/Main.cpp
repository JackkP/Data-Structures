/* Jack Porter, C++ Data Structures, March 2022
 * Heap project, creates a binary max 
 */

#include "Heap.h"

#include <cstring>
#include <iostream>
#include <time.h>

using namespace std;

int main(){
	cout << "Max Heap Project!" << endl;
	srand(time(0));
	while (true) {
		//formatting
		cout << "=====================================================" << endl;
		cout << "type \"read\" to read in numbers from a file, \"input\" to input numbers manually,";
		cout << "\n \"generate\" to generate random numbers, or \"quit\" to exit the program" << endl;
		
		char next[1000];
		cin.get(next, 1000);
		cin.get();
		
		cout << "=====================================================" << endl;
		
		Heap* heap = NULL;

		if(strcmp(next, "quit") == 0){
			break;
		}
		else if(strcmp(next, "read") == 0){
			cout << "filename?" << endl;
			cin.get(next, 1000);
			cin.get();
		}
		else if(strcmp(next, "input") == 0){
			cout << "enter your numbers seperated by commas" << endl;
			cin.get(next, 1000);
		}
		else if(strcmp(next, "generate") == 0){
			cout << "how many numbers would you like to generate? (up to 100)" << endl;
			cin.get(next, 1000);
			cin.get();
			int ammount = atoi(next);
			heap = new Heap();
			cout << "randomly generated numbers: ";
			for(int i = 0; i < ammount; i++){
				int number = rand()%101;
				//cout << number << " ";
				heap->push(number); //add a random number between 0 and 100
			}
			cout << endl;
			heap->print();
			cout << endl << endl;
`
			int top = heap->pop();
			cout << "peek = " << heap->peek();
			cout << "top = " << top;
			while (top != INT_MIN){
				cout << top << " ";

			}
		}
		else {
			cout << "not a valid input, please try again" << endl;
		}
	}
}
