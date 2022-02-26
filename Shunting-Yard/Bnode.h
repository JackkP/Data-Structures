/* Jack Porter, C++ Data Structures, February 2022
 * Binary tree node for Shunting Yard Algorithm
 */
#ifndef BNODE_H
#define BNODE_H

#include <iostream>
#include <cstring>

using namespace std;

//node class for binary expression tree
class Bnode {
        public:
                Bnode(char* token);
                ~Bnode();
                void setRight(Bnode* n);
                void setLeft(Bnode* n);
                Bnode* getRight();
                Bnode* getLeft();
		void setToken(char* c);
		char* getToken();

        private:
                char* token;
                Bnode* right;
                Bnode* left;

};

#endif
