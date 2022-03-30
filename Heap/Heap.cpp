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

void Heap::print(){

}

int Heap::peek(){
	return values[0];
}

int Heap::pop(){
	
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
 	for(int i = 0; i < capacity; i++){
		if (values[i] == INT_MIN){
			return i+1;
		}
	}
	return capacity;
}

bool Heap::push(int val){ //push a value onto the heap
	int index = size();
	if (index != capacity){ //if the heap has room
		values[index] = val; //add it and check to see if it needs to be sifted up
		siftUp(index);
		return true;
	}
	else return false;
}
