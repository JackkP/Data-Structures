/* Jack Porter, C++ Data Structures, Febuary 2022
 * Shunting yard algorithm
 */

#include <iostream>
#include <cstring>
#include "Bnode.h"
#include "Stack.h"
#include <map>

using namespace std;

int main(){
	
	//map to map character to its type
	//throws out_of_range if key character is not found
	map<char, int> type;
	
	type.insert(pair<char, int>('0', 0));
	type.insert(pair<char, int>('1', 0));
	type.insert(pair<char, int>('2', 0));
	type.insert(pair<char, int>('3', 0));
	type.insert(pair<char, int>('4', 0));
	type.insert(pair<char, int>('5', 0));
	type.insert(pair<char, int>('6', 0));
	type.insert(pair<char, int>('7', 0));
	type.insert(pair<char, int>('8', 0));
	type.insert(pair<char, int>('9', 0));
	type.insert(pair<char, int>('.', 0));
	type.insert(pair<char, int>('+', 1));
	type.insert(pair<char, int>('-', 2));
	type.insert(pair<char, int>('*', 3));
	type.insert(pair<char, int>('/', 4));
	type.insert(pair<char, int>('^', 5));
	type.insert(pair<char, int>('(', 6));
	type.insert(pair<char, int>(')', 7));

	cout << "Shunting Yard Algorithm!" << endl;
	while (true) {
		//formatting
		cout << "=====================================================" << endl;
		cout << "Functions: (, ), +, -, *, /, and ^\nInput an equation to start or type 'quit' to quit" << endl;
		
		char next[200];
		cin.get(next, 200);
		cin.get();
		
		cout << "=====================================================" << endl;
		
		if(strcmp(next, "quit") == 0){
			break;
		}
		
		else{ //assume its an expression

			Queue* inQ = new Queue(NULL);
			
			/* 0 - Number
			 * 1 - +, 2 - -
			 * 3 - *, 4 - /
			 * 5 - ^
			 * 6 - (, 7 - )
			 */
			
			//tokenize it and put tokens into input stack
			
			//if the first character is a negative sign set the type to 0
			try {
				int curType = 0;
				int tknStrt = 0;

				if (type.at(next[0]) == 2) { //if the first sign is unary minus sign
					curType = 0; 	//consider it part of a multi-digit number
				}
				else curType = type.at(next[0]);
				
				for(int i = 1; i < strlen(next); i++){ //starting with the second character
					if(type.at(next[i]) != curType && !(type.at(next[i]) == 0 && curType == 2)){ //if the character does not match the previous character token type
						char* tkn = new char[i-tknStrt]; //create a new token
						for(int j = tknStrt; j < i; j++){ //for every character in the new token
							tkn[j-tknStrt] = next[j]; //copy the character from the input to the corresponding character in the token array
						}
						tkn[i-tknStrt] = 00; //set end character to null
						cout << "final token: " << tkn << endl;
						Node* n = new Node; //create a new node and assign it
						n->next = NULL;
						n->token = tkn;
						inQ->enqueue(n); //add the node to the input queue
						curType = type.at(next[i]); //update position and type of last token
						tknStrt = i;
					}
					if(i == strlen(next)-1) { //last token
						char* tkn = new char[i-tknStrt]; //create a new token
						for(int j = tknStrt; j <= i; j++){ //for every character in the new token
							tkn[j-tknStrt] = next[j]; //copy the character from the input to the corresponding character in the token array
						}
						tkn[i+1-tknStrt] = 00; //set end character to null
						cout << "final token: " << tkn << endl;
						Node* n = new Node; //create a new node and assign it
						n->next = NULL;
						n->token = tkn;
						inQ->enqueue(n); //add the node to the input queue
					}
				}
			

				//run the shunting yard
				//print prefix infix postfix
				//evaluate
			}
			catch (...) {
				cout << "not a valid expression" << endl;
			}
			
			
		}



	}

	return 0;
}
