/* Jack Porter, C++ Data Structures, April 2022
 * Heap class for heap project
 */

#include "Heap.h"

Heap::Heap(){
	capacity = 100;
	for(int i = 0; i < capacity; i++){
		values[i] = INT_MIN;
	}
}

Heap::~Heap(){}

/* Function to print a binary tree baseed on
 * https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
 */
void Heap::printRec(int index, int space) {
	if (index+1 >= capacity || index == INT_MIN) return;
	else if (values[index] == INT_MIN) return;
	
	// Increase distance between levels by 10 spaces
	space += 10;
	
	//Print right child tree first
	printRec(right(index), space);
	
	// Print current value after space
	for (int i = 10; i < space; i++)
        	cout<<" ";
    	cout<<values[index]<<"\n";

	//Print left child tree
	printRec(left(index), space);
}

void Heap::print(){
	int counter = 0;
	cout << "printing, capacity = " << capacity << endl;
	for(int i = 0; i < capacity; i++){
	cout << "i = " << i << ", " << values[i] << endl;	
	}

	cout << endl;
	
	printRec(0, 0); //print starting at the head
}

int Heap::peek(){
	return values[0];
}

int Heap::pop(){
	//swap the head and the last value
	int swapindex = size()-1; 
	int temp = values[0];
	values[0] = values[swapindex];
	values[swapindex] = temp;

	values[swapindex] = INT_MIN; //set the new last value to null
	siftDown(0); //sift down the new head
	return temp; //the old head
}

int Heap::left(int index){
	//return index of left child or INT_MIN if too large
	if((index+1)*2-1 < capacity) return (index+1)*2-1;
	else return INT_MIN;
}

int Heap::right(int index){
	//return index of right child or INT_MIN if too large
	if((index+1)*2 < capacity) return (index+1)*2;
	else return INT_MIN;
}

int Heap::parent(int index){
	return (index+1)/2-1;
}

void Heap::siftUp(int index){
	int pIndex = parent(index);
	if(values[index] > values[pIndex]){ //if the value is greater than its parent
		int temp = values[index]; //swap it with the parent
		values[index] = values[pIndex];
		values[pIndex] = temp;
		siftUp(pIndex); //sift up again
	}
}

void Heap::siftDown(int index) {
	int swapindex = INT_MIN;
	//if the value is less than the left child and the left child is larger than the right
	if(values[index] < values[left(index)] && values[left(index)] >= values[right(index)]){
		swapindex = left(index);
	}
	//if the value is less than the right child and the right child is larger than the left
	else if(values[index] < values[right(index)] && values[right(index)] > values[left(index)]){
		//cout << "swapping with right" << endl;
		swapindex = right(index);
	}
	//if swapping with a child
	if(swapindex != INT_MIN){
		int temp = values[index]; //swap it with the parent
		values[index] = values[swapindex];
		values[swapindex] = temp;
		siftDown(swapindex); //sifted down again
	}
}

int Heap::size(){
	//walk to the last element then return the index of it
 	for(int i = 0; i < capacity; i++){
		if (values[i] == INT_MIN){
			return i;
		}
	}
	return capacity;
}

bool Heap::push(int val){ //push a value onto the heap
	cout << "capacity = " << capacity << endl;
	int index = size();
	if (index < capacity){ //if the heap has room
		values[index] = val; //add it and check to see if it needs to be sifted up
		siftUp(index);
		return true;
	}
	else return false;
}
