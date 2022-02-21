/* Jack Porter, C++ Data Structures, Febuary 2022
 * Shunting yard algorithm
 * there are lots of very long lines, read this in full screen with small font
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

	map<char, int> precedence;
	precedence.insert(pair<char, int>('(', 0));
	precedence.insert(pair<char, int>(')', 0));
	precedence.insert(pair<char, int>('+', 2));
	precedence.insert(pair<char, int>('-', 2));
	precedence.insert(pair<char, int>('*', 3));
	precedence.insert(pair<char, int>('/', 3));
	precedence.insert(pair<char, int>('^', 4));


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
				 * Unary "-" operators are just merged into the numebers they
				 * preceed instead of doing it the right way
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
				

				//Queue temp;
				Node* n; // = inQ.dequeue();
				/*while(n){
					cout << n->token << " ";
					temp.enqueue(n);
					n = inQ.dequeue();
				}
				cout << endl;
				n = temp.dequeue();
				while(n){
					inQ.enqueue(n);
					n = temp.dequeue();
				}*/
				
				inQ.print();
			

				/* Shunting Yard Algorithm
				 * from https://en.wikipedia.org/wiki/Shunting-yard_algorithm
				 */

				/* while there are tokens to be read:
				 * read a token
				 * if the token is:
				 *   - a number:
				 *   	put it into the output queue
				 *   - a function:
				 *   	push it onto the operator stack 
				 *   - an operator o1:
				 *   	while (
				 *   	   there is an operator o2 other than the left parenthesis at the top
				 *   	   of the operator stack, and (o2 has greater precedence than o1
				 *   	   or they have the same precedence and o1 is left-associative)
				 *   	):
				 *  	   pop o2 from the operator stack into the output queue
				 *  	push o1 onto the operator stack
				 *   - a left parenthesis (i.e. "("):
				 *   	push it onto the operator stack
				 *   - a right parenthesis (i.e. ")"):
        			 *	while the operator at the top of the operator stack is not a left parenthesis:
				 *	   {assert the operator stack is not empty}
            			 *	   $$ If the stack runs out without finding a left parenthesis, 
				 *	   $$ then there are mismatched parentheses.
          			 *	   pop the operator from the operator stack into the output queue
        			 *	{assert there is a left parenthesis at the top of the operator stack}
				 *	pop the left parenthesis from the operator stack and discard it
				 *	if there is a function token at the top of the operator stack, then:
				 *		pop the function from the operator stack into the output queue
				 * $$ After the while loop, pop the remaining items from the operator stack
				 * $$ into the output queue.
				 * while there are tokens on the operator stack:
				 * 	$$ If the operator token on the top of the stack is a parenthesis, 
				 * 	$$ then there are mismatched parentheses.
				 * 	{assert the operator on top of the stack is not a (left) parenthesis}
				 * 	pop the operator from the operator stack onto the output queue 
	    			 */
				
				Queue outQ; //should be dynamic or static?
				Stack opS;
				
				cout << "opS: ";
				opS.print();
				cout << "inQ: ";
				inQ.print();
				cout << "outQ: ";
				outQ.print();

				n = inQ.dequeue();
				while(n){
					switch (type.at(n->token[strlen(n->token)-1])){
						case (0): {// a number, push it to the output stack
							outQ.enqueue(n);
							break;
						}
						case (1): // an operator,
						case (2):
						case (3):
						case (4):
						case (5): {
							cout << "Token is an operator" << endl;
							while (opS.peek()) {
								// if the token on top of the operator stack has a higher precedence than the current operator and is left associative (not ^)
								
								try { cout << "precedence.at(opS.peek()->token[0]): " << precedence.at(opS.peek()->token[0]) << endl; } 
								catch (...) { cout << "failure of precedence.at(opS.peek()->token[0]), opS.peek()->token[0]: " << opS.peek()->token[0]  << endl; }
								
								try { cout << "precedence.at(n->token[0]): " << precedence.at(n->token[0]) << endl; } 
								catch (...) { cout << "failure of precedence.at(n.peek()->token[0])" << endl; }




								if(precedence.at(opS.peek()->token[0]) >= precedence.at(n->token[0]) && type.at(opS.peek()->token[0]) == 5){
									outQ.enqueue(opS.pop()); //push it to the output queue
								}
								else {
									break;
								}
							}
							opS.push(n); //push the operator to the operator stack
							break;
						}
						case (6): { // a left parenthesis "(", push to the operator stack
							opS.push(n);
							break;
						}
						case (7): { //a right parenthesis ")", 
							Node* stktp = opS.pop();
							bool parenMismatch = true;
							while (stktp) {
								// if the token on top of the operator stack has a higher precedence than the current operator
								if(type.at(stktp->token[0]) != 6){ //if the token is not a left parenthesis push it to output stack
									outQ.enqueue(stktp);
								}
								else {
									parenMismatch = false; //found a right parenthesis
									break;
								}
								stktp = opS.pop();
							}
							if(parenMismatch) throw;
							break;
						}
					}
					cout << "==============\nopS: ";
					opS.print();
					cout << "inQ: ";
					inQ.print();
					cout << "outQ: ";
					outQ.print();

					n = inQ.dequeue();
					if (n) cout << "Next token: " << n->token << endl;
				}
				cout << "successfully ran shunting yard" << endl;
				n = opS.pop();
				while (n){
					//if(type.at(n->token[0] == 6 || type.at(n->token[0]) == 7)) throw; //parenthesis mismatch
					outQ.enqueue(n);
					n = opS.pop();
				}
				
				cout << "Postfix notation: ";
				
				outQ.print();

				/*n = outQ.dequeue();
				while(n){
					cout << n->token << " ";
					temp.enqueue(n);
					n = outQ.dequeue();
				}
				cout << endl;
				n = temp.dequeue();
				while(n){
					outQ.enqueue(n);
					n = temp.dequeue();
				}*/

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
