/* Jack Porter, C++ Data Structures, Febuary 2022
 * Shunting yard algorithm
 */

#include <iostream>
#include <cstring>
#include "Bnode.h"
#include "Stack.h"
#include "Queue.h"
#include "Node.h"
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

			Queue inQ; //is this better dynamically allocated?
			
			/* 0 - Number
			 * 1 - +, 2 - -
			 * 3 - *, 4 - /
			 * 5 - ^
			 * 6 - (, 7 - )
			 */
			
			
			try {

				/* Tokenizer: works by walking through input array and starting a new token every time
				 * there is a change in character type.
				 * This can handle unary "-" signs by checking if they come after an operator.
				 */
				int curType = 0;
				int prevType = 0;
				int tknStrt = 0;

				if (type.at(next[0]) == 2) { //if the first sign is unary minus sign
					curType = 0; 	//consider it part of a multi-digit number
				}
				else curType = type.at(next[0]);
				
				for(int i = 1; i < strlen(next); i++){ //starting with the second character
					if(type.at(next[i]) != curType && !(prevType>=1 && prevType <=5 && type.at(next[i]) == 0 && curType == 2)){ //if the character does not match the previous character token type and is not a unary minus following an operator
						char* tkn = new char[i-tknStrt]; //create a new token
						for(int j = tknStrt; j < i; j++){ //for every character in the new token
							tkn[j-tknStrt] = next[j]; //copy the character from the input to the corresponding character in the token array
						}
						tkn[i-tknStrt] = 00; //set end character to null
						Node* n = new Node; //create a new node and assign it
						n->next = NULL;
						n->token = tkn;
						inQ.enqueue(n); //add the node to the input queue
						curType = type.at(next[i]); //update position and type of last token
						prevType = type.at(next[i-1]);
						tknStrt = i;
					}
					if(i == strlen(next)-1) { //last token
						char* tkn = new char[i-tknStrt]; //create a new token
						for(int j = tknStrt; j <= i; j++){ //for every character in the new token
							tkn[j-tknStrt] = next[j]; //copy the character from the input to the corresponding character in the token array
						}
						tkn[i+1-tknStrt] = 00; //set end character to null
						Node* n = new Node; //create a new node and assign it
						n->next = NULL;
						n->token = tkn;
						inQ.enqueue(n); //add the node to the input queue
					}
				}
				


				/* Print in infix notation: walk through queue,
				 * copy the queue, then transfer back and delet copy
				 */
				cout << "Infix notation: ";
				Queue temp;
				Node* n = inQ.dequeue();
				while(n){
					cout << n->token << " ";
					temp.enqueue(n);
					n = inQ.dequeue();
				}
				cout << endl;
				n = temp.dequeue();
				while(n){
					inQ.enqueue(n);
					n = temp.dequeue();
				}
			

				//run the shunting yard
				
				//print prefix infix postfix
				
				//evaluate and print
			}
			catch (...) {
				cout << "not a valid expression" << endl;
			}
			
			
		}



	}

	return 0;
}
