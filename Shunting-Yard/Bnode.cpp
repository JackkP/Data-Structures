#include "BNODE.H"

using namespace std;

//constructor
Bnode::Bnode(char* token){
        Token = token;
        Right, Left = NULL;
}
//destructor
Bnode::~Bnode(){
        delete Token;
}
//set right pointer
void Bnode::SetRight(Bnode* n){ Right = n; }
//set left pointer
void Bnode::SetLeft(Bnode* n){ Left = n; }
//get right pointer
Bnode* Bnode::GetRight(){ return Right; }
//get left pointer
Bnode* Bnode::GetLeft(){ return Left; }

