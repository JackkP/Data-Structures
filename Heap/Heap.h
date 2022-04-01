/* Jack Porter, C++ Data Structures, April 2022
 * heap class for heap project
 */

#ifndef HEAP_H
#define HEAP_H
#include <iostream>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;

class Heap{
	public:
		Heap();
		~Heap();
		void print();
		int peek();
		int pop();
		bool push(int val);

	private:
		int size();
		void siftUp(int index);
		void siftDown(int index);
		int left(int index);
		int right(int index);
		int parent(int index);
		void printRec(int index, int spaces);
		int capacity;
		int values[100];
};
#endif
