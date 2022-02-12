/* Jack Porter, C++ Data Structures, Febuary 2022
 * Shunting yard algorithm
 */

#include <iostream>
#include <cstring>
#include "Bnode.h"
#include "Stack.h"
//#include "Queue.h"

using namespace std;

int main(){
	
	cout << "Shunting Yard Algorithm!" << endl;
	while (true) {
		//formatting
		cout << "=====================================================" << endl;
		cout << "Functions: (, ), +, -, *, /, and ^\nInput an equation to start! or type 'quit' to quit" << endl;
		
		char next[100];
		cin.get(next, 100);
		cin.get();
		
		cout << "=====================================================" << endl;
		
		if(strcmp(next, "quit") == 0){
			break;
		}
		
		else{
			
		}



	}

	return 0;
}
