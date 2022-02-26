/* Jack Porter, C++ Data Structures, February 2022
 * Binary tree node for Shunting Yard Algorithm
 */

#include "Bnode.h"

using namespace std;

//constructor
Bnode::Bnode(char* tkn){
        token = tkn;
        right = NULL;
	left = NULL;
}
//destructor
Bnode::~Bnode(){
        delete token;
}
//set right pointer
void Bnode::setRight(Bnode* n){ right = n; }
//set left pointer
void Bnode::setLeft(Bnode* n){ left = n; }
//get right pointer
Bnode* Bnode::getRight(){ return right; }
//get left pointer
Bnode* Bnode::getLeft(){ return left; }
//set token
void Bnode::setToken(char* c){ token = c; }
//get token
char* Bnode::getToken(){ return token; }
