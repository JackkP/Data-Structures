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

Heap::~Heap(){

}

/* Function to print a binary tree baseed on
 * https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
 */

void Heap::printRec(int index, int space) {
	if (values[index] == INT_MIN) return;
	
	// Increase distance between levels by 10 spaces
	space += 10;
	
	// Process right child first
	printRec(right(index), space);
	
	// Print current node after space
	// count
	cout<<endl;
	for (int i = 10; i < space; i++)
        	cout<<" ";

    	cout<<values[index]<<"\n";
		// Process left child
		printRec(left(index), space);
}

void Heap::print(){
	//cout << "printing" << endl;
	cout << values[0] << " " << values[1] << " " << endl;
	for(int i = 0; i<size(); i++){
		cout << values[i] << " ";
	}
	cout << endl;
	printRec(0, 0); //print starting at the head

	cout << values[0] << " " << values[1] << " " << endl;
}

int Heap::peek(){
	return values[0];
}

int Heap::pop(){
	//swap the head and the smallest value
	int swapindex = size()-1;
	int temp = values[swapindex];
	values[swapindex] = values[0];
	values[0] = temp;
	values[swapindex] = INT_MIN; //set the thing to null
	siftDown(0); //sift down the new head
	return temp;//the old head
}

int Heap::left(int index){
	return (index+1)*2-1;
}

int Heap::right(int index){
	return (index+1)*2;
}

int Heap::parent(int index){
	return index/2-1;
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
	if(values[index] > values[left(index)] || values[index] > values[right(index)]){ //if the value needs to be sifted down
		//swap with the larger value
		int swapindex = left(index);
		if (values[right(index)] > values[left(index)]) swapindex = right(index);
		int temp = values[index]; //swap it with the parent
		values[index] = values[swapindex];
		values[swapindex] = temp;
		siftDown(swapindex); //sifted down again
	}
}

int Heap::size(){
	//cout << "getting size" << endl;
 	for(int i = 0; i < capacity; i++){
		//cout << "  values[i] = " << values[i] << endl;
		if (values[i] == INT_MIN){
			return i+1;
		}
	}
	return capacity;
}

bool Heap::push(int val){ //push a value onto the heap
	int index = size()-1;
	//cout << "pushing" << endl;
	if (index != capacity){ //if the heap has room
		//cout << "adding at index: " << index << endl;
		values[index] = val; //add it and check to see if it needs to be sifted up
		siftUp(index);
		return true;
	}
	else return false;
}
