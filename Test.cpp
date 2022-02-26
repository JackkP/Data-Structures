#include <iostream>
#include <cstring>

using namespace std;

int main()(){
	
	for (int i = 0; i < 20; i++){
		cout << " ";
	}
	cout << "|" << endl;

	for (int i = 0; i < 20; i++){
		cout << "1";
	}
	cout << "|" << endl;
	
	for (int i = 0; i < 20; i++){
		cout << "\\";
	}
	cout << "|" << endl;

	for (int i = 0; i < 20; i++){
		cout << ".";
	}
	cout << "|" << endl;

	return 0;
}
