// Branch struct for Red Black Tree Project
// Jack P, C++ Data Structures, April 2022
//struct for printing trees based on https://www.techiedelight.com/c-program-print-binary-tree/
#ifndef BRANCH_H
#define BRANCH_H

#include <cstring>

using namespace std;


struct Branch {
	Branch* prev;
	char* str;

	Branch(){
		str = new char[10];
	}
    
	~Branch(){
		delete str;
	}
};

#endif
