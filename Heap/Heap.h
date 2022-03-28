/* Jack Porter, C++ Data Structures, April 2022
 * heap class for heap project
 */

#ifndef HEAP_H
#define HEAP_H
#include <iostream>
#include <cstring>

using namespace std;

class Heap{
	public:
		Heap();
		~Heap();
		void print();
		int getNext();
		void add(int val);

	private:
		int values[100];
		
};
#endif
