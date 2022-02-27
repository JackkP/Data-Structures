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
#include <math.h>

using namespace std;

Queue* tokenize(char* input); //tokenizer
Queue* shuntingYard(Queue* inQ); //function that actually runs the shunting yard algorithm
Bnode* binaryTree(Queue* inQ); //convert postfix to a binary tree
void printPrefix(Bnode* n);
void printInfix(Bnode* n);
void printPostfix(Bnode* n);
float evaluate(Bnode* n);

//map to map character to its type
//throws out_of_range if key character is not found
map<char, int> type;
//map to map operator to precedence (see wikipedia for precedence explanation)
map<char, int> precedence;

int main(){
	
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
	type.insert(pair<char, int>(' ', 8)); //spaces to be ignored, can handle everything but starting with a space
	
	precedence.insert(pair<char, int>('(', 0));//even though parenthesis are not operators, they are given lowest
	precedence.insert(pair<char, int>(')', 0));//precedence since they are compared with other operators
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
		
			try { //try catch used to deal with invalid expressions, stuff will throw errors if invalid
				
				//tokenize the input string
				Queue* inQ = tokenize(next);
				
				//cout << "Infix notation: "; //for debugging
				//inQ->print();
				
				//run the shunting yard alogrithm on the tokenized input
				Queue* outQ = shuntingYard(inQ);
								
				// cout << "Postfix notation: "; //for debugging
				// outQ->print();
				
				//convert it to a binary tree
				Bnode* opTHead = binaryTree(outQ);
				
				cout << "Prefix: ";
				printPrefix(opTHead);
				cout << endl << "Postfix: ";
				printPostfix(opTHead);
				cout << endl << endl;
				
				printInfix(opTHead);
				cout << "= " << evaluate(opTHead) << endl;;
			}
			catch (...) {
				cout << "not a valid expression" << endl;
			}
		}
	}
	return 0;
}

Queue* tokenize(char* input){
	
	/* Tokenizer: works by walking through input array and starting a new token every time
	 * there is a change in character type.
	 * This can handle unary "-" signs by checking if they come after an operator.
	 * Unary "-" operators are just merged into the numebers they
	 * preceed instead of doing it the right way (this is cheating but its fine).
	 */

	Queue* inQ = new Queue();

	int curType = 0;
	int prevType = 0;
	int tknStrt = 0;
	
	if (strlen(input) == 1) { //only one character (since we check starting with the second character)
		if (type.at(input[0]) == 0) {
			char* tkn = new char[1];
			tkn[0] = input[0];
			tkn[1] = '\0';
			Node* n = new Node();
			n->next = NULL;
			n->token = tkn;
			inQ->enqueue(n);
		}
		else throw;
	}
	if (type.at(input[0]) == 2) { //if the first sign is unary minus sign
		curType = 0; 	//consider it part of a multi-digit number
	}
	else curType = 0;
	
	for(int i = 1; i < strlen(input); i++){ //starting with the second character
		if(type.at(input[i]) != curType && !(prevType>=1 && prevType <=5 && type.at(input[i]) == 0 && curType == 2)){ //if the character does not match the previous character token type and is not a unary minus following an operator
			char* tkn = new char[i-tknStrt]; //create a new token
			for(int j = tknStrt; j < i; j++){ //for every character in the new token
				tkn[j-tknStrt] = input[j]; //copy the character from the input to the corresponding character in the token array
			}
			tkn[i-tknStrt] = 00; //set end character to null
			Node* n = new Node; //create a new node and assign it
			n->next = NULL;
			n->token = tkn;
			inQ->enqueue(n); //add the node to the input queue
			curType = type.at(input[i]); //update position and type of last token
			prevType = type.at(input[i-1]);
			tknStrt = i;
		}
		if(i == strlen(input)-1) { //last token
			char* tkn = new char[i-tknStrt]; //create a new token
			for(int j = tknStrt; j <= i; j++){ //for every character in the new token
				tkn[j-tknStrt] = input[j]; //copy the character from the input to the corresponding character in the token array
			}
			tkn[i+1-tknStrt] = 00; //set end character to null
			Node* n = new Node; //create a new node and assign it
			n->next = NULL;
			n->token = tkn;
			inQ->enqueue(n); //add the node to the input queue
		}
	}
	return inQ;
}


Queue* shuntingYard(Queue* inQ) {//function that actually runs the shunting yard algorithm
	
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
	Queue* outQ = new Queue;
	Stack opS;

	/*cout << "opS: "; //debug code
	opS.print();
	cout << "inQ: ";
	inQ.print();
	cout << "outQ: ";
	outQ.print();*/
	
	Node* n = inQ->dequeue();
	while(n){
		switch (type.at(n->token[strlen(n->token)-1])){
			case (0): {// a number, push it to the output stack
				outQ->enqueue(n);
				break;
			}
			case (1): // an operator,
			case (2):
			case (3):
			case (4):
			case (5): {
				while (opS.peek()) {
					// if the token on top of the operator stack has a higher precedence than the current operator and token n is left associative (not ^)
					if(precedence.at(opS.peek()->token[0]) >= precedence.at(n->token[0]) && type.at(n->token[0]) != 5){
						outQ->enqueue(opS.pop()); //push it to the output queue
					}
					else break; 
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
						outQ->enqueue(stktp);
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
		//cout << "==============\nopS: "; // Debug code
		//opS.print();
		//cout << "inQ: ";
		//inQ.print();
		
		n = inQ->dequeue();
		
		//cout << "outQ: "; //debug code
		//outQ.print();
		//if (n) cout << "Next token: " << n->token << endl;
	}

	n = opS.pop();
	while (n){ //move all tokens on the operator stack to the output queue
	if(type.at(n->token[0]) == 6 || type.at(n->token[0]) == 7) { throw; } //parenthesis mismatch
		outQ->enqueue(n);
		n = opS.pop();
	}
	return outQ;
}

Bnode* binaryTree(Queue* inQ){ //convert postfix to a binary tree
	//construct binary tree
	// while there are tokens in the input queue
	// 	if the token is a number
	// 		create a binary tree node with this value and:
	// 		move it to the value stack
	// 		{assert that there should still be tokens in the input queue}
	// 	if the token is an operator
	// 		{assert that there should be at least two items on the value stack}
	// 		create a new binary tree node with this operator as the token
	// 		add the top two items off the value stack to the left and right pointers of this operator
	// 		add this operator to the value stack
	// {assert that there should be only one node in the value stack}
	// Set the head to be the top of the value stack

	Stack numStk; //temporary stack
	
	Node* n = inQ->dequeue();
	while (n) {
		if (type.at(n->token[strlen(n->token)-1]) == 0) { //the token is a number
			Node* newN = new Node(); //create a new node for the temporary stack
		
			Bnode* b = new Bnode(n->token); //create a new node and add that to the stack
			newN->bnode = b;
			
			numStk.push(newN);
			n->token = NULL; //delete the old node
			delete n;
		}
		else { //the token is an operator
			//cout << "token is an operator" << endl;
			Node* newN = new Node(); //create a new node for the temporary stack
			
			Bnode* b = new Bnode(n->token); //create a new binary node and node(struct) to store in stack
			newN->bnode = b;
			
			n->token = NULL; //delete token
			delete n;
			
			Node* right = numStk.pop(); //get node off the top of the stack and set right
			b->setRight(right->bnode);
			right->bnode = NULL; //delete old node
			delete right;
			
			Node* left = numStk.pop(); //get node off the top of the stack and set left
			b->setLeft(left->bnode);
			left->bnode = NULL; //delete old node
			delete left;
			
			numStk.push(newN); //push this new node back onto the stack
		}
		n = inQ->dequeue();
	}
	n = numStk.pop(); //get the last node (head)
	Bnode* outputTreeHead = n->bnode;
	n->bnode = NULL; //delete old node
	delete n;
	return outputTreeHead;

}

void printPrefix(Bnode* n){
	if (n){
		cout << n->getToken() << " ";
		printPrefix(n->getLeft());
		printPrefix(n->getRight());
	}
}

void printInfix(Bnode* n){ //need to deal with precedence for operators so that parenthesis can be printed
	if (n) {
		if (type.at(n->getToken()[strlen(n->getToken())-1]) > 0) { //if the token is an operator
			if (type.at(n->getLeft()->getToken()[strlen(n->getLeft()->getToken())-1]) > 0) {//left token is an operator
				if (precedence.at(n->getToken()[0]) > precedence.at(n->getLeft()->getToken()[0])){ //|| type.at(n->getToken()[0]) == 2){ //operator has a higher precedence than the left operator or is a minus
					cout << "( "; //left side needs parenthesis
					printInfix(n->getLeft());
					cout << ") ";
				}
				else { printInfix(n->getLeft()); }
			}
			else { printInfix(n->getLeft());}
			cout << n->getToken() << " ";
			if (type.at(n->getRight()->getToken()[strlen(n->getRight()->getToken())-1]) > 0) {//right token is an operator
				if (precedence.at(n->getToken()[0]) > precedence.at(n->getRight()->getToken()[0]) || (type.at(n->getToken()[0]) == 2 && precedence.at(n->getRight()->getToken()[0]) <= 2)){ 
					//operator has a higher precedence than the right operator or is a minus and has greater than or equal precedence
					cout << "( "; //Right side needs parenthesis
					printInfix(n->getRight());
					cout << ") ";
				}
				else { printInfix(n->getRight()); }
			}
			else { printInfix(n->getRight()); }

		}
		else { //token is a number
			printInfix(n->getLeft());
			cout << n->getToken() << " ";
			printInfix(n->getRight());
		}
	}
}

void printPostfix(Bnode* n){
	if (n) {
		printPostfix(n->getLeft());
		printPostfix(n->getRight());
		cout << n->getToken() << " ";
	}
}

float evaluate(Bnode* n){
	switch (type.at(n->getToken()[strlen(n->getToken())-1])){
		case 0: //number
			return atof(n->getToken());
		case 1: // +
			return evaluate(n->getLeft()) + evaluate(n->getRight());
		case 2: // -
			return evaluate(n->getLeft()) - evaluate(n->getRight());
		case 3: // *
			return evaluate(n->getLeft()) * evaluate(n->getRight());
		case 4: // /
			return evaluate(n->getLeft()) / evaluate(n->getRight());
		case 5: // ^
			return pow(evaluate(n->getLeft()), evaluate(n->getRight()));
	}
}
