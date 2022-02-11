#include <iostream>
#include <cstring>

using namespace std;

//node class for binary expression tree
class Bnode {
        public:
                Bnode(char* token);
                ~Bnode();
                void SetRight(Bnode* n);
                void SetLeft(Bnode* n);
                Bnode* GetRight();
                Bnode* GetLeft();
        private:
                char* Token;
                Bnode* Right;
                Bnode* Left;

};

