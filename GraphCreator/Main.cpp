// Graph Creator Project, Jack Porter, July 2022

#include "Graph.h"

#include <cstring>
#include <iostream>

using namespace std;

void printMenu();

int main(){
	cout << "Graph Creator Project!\nUtilizes a graph data structure to calculate the shortest path between vertexs" << endl;
	
	cout << "====================================================================================" << endl;
	printMenu();

	Graph* graph = new Graph();

	while (true) {
		//formatting
		cout << "====================================================================================" << endl;
		char next[2000];
		cin.get(next, 2000);
		cin.get();
	
		//cout << "====================================================================================" << endl;

		if(strcmp(next, "quit") == 0 || strcmp(next, "q") == 0 || strcmp(next, "exit") == 0){
			break;
		}
		
		//print the help menu
		else if(strcmp(next, "h") == 0 || strcmp(next, "help") == 0){
			printMenu();
		}
		
		//add a vertex or edge
		else if(strcmp(next, "i") == 0 || strcmp(next, "input") == 0 || strcmp(next, "add") == 0) {
			cout << "add a vertex or edge (v/e)" << endl;
			cin.get(next, 2000);
			cin.get();
			
			//adding a vertex
			if (strcmp(next, "v") == 0) {
				cout << "type the name of the vertex you would like to add (leter a through t)" << endl;
				cin.get(next, 2000);
				cin.get();
				if (!graph->addV(toupper(next[0]))) cout << "that name is invalid or the vertex already exists" << endl;
				else cout << "sucessfully added vertex " << (char)toupper(next[0]) << endl;
			}
			
			//adding an edge
			else if (strcmp(next, "e") == 0){
				//get vertex names and edge weight
				cout << "name of the first vertex" << endl;
				char n1[4];
				cin.get(n1, 4);
				cin.get();
				cout << "name of the second vertex" << endl;
				char n2[4];
				cin.get(n2, 4);
				cin.get();
				cout << "weight of the edge any number" << endl;
				cin.get(next, 10);
				cin.get();
				//addE returns true if the add was successful, will print its own errors otherwise
				if (graph->addE(toupper(n1[0]), toupper(n2[0]), atoi(next))){
					cout << "successfully added an edge from " << (char)toupper(n1[0])<< " to " << (char)toupper(n2[0]) << " with weight " << atoi(next) << endl;
				}
			}
			else cout << "not a valid input" << endl;
		}

		else if(strcmp(next, "p") == 0 || strcmp(next, "print") == 0){
			graph->printAdj();
		}
		
		//remove an edge or vertex
		else if(strcmp(next, "rm") == 0 || strcmp(next, "del") == 0 || strcmp(next, "remove") == 0){
			cout << "remove a vertex or edge (v/e)" << endl;
			cin.get(next, 2000);
			cin.get();
			
			//removing a vertex
			if (strcmp(next, "v") == 0) {
				cout << "type the name of the vertex you would like to remove (leter a through t)" << endl;
				cin.get(next, 2000);
				cin.get();
				if (!graph->rmV(toupper(next[0]))) cout << "that name is invalid or the vertex already exists" << endl;
				else cout << "sucessfully removed " << (char)toupper(next[0]) << endl;
			}
			
			//removing an edge
			else if (strcmp(next, "e") == 0){
				//get names of verticies
				cout << "name of the first vertex" << endl;
				char n1[4];
				cin.get(n1, 4);
				cin.get();
				cout << "name of the second vertex" << endl;
				char n2[4];
				cin.get(n2, 4);
				cin.get();
				if (graph->rmE(toupper(n1[0]), toupper(n2[0]))){
					cout << "successfully removed the edge from " << (char)toupper(n1[0])<< " to " << (char)toupper(n2[0]) << endl;
				}
			}
			else cout << "not a valid input" << endl;
		}
		
		//find the shortest path
		else if(strcmp(next, "s") == 0 || strcmp(next, "path") == 0){
			cout << "name of the first vertex" << endl;
			char n1[4];
			cin.get(n1, 4);
			cin.get();
			cout << "name of the second vertex" << endl;
			char n2[4];
			cin.get(n2, 4);
			cin.get();
			
			//store the path as an array
			//[<vertices>, <length>, <vertex n>, <vertex n-1>... <vertex 1>}
			//example: [3, 7, A, C, E]
			//the array returned by the algorithm also contians the number of verticies visited (first value) and the length (second value)
			//will return null if the verticies are not connected
			int* path = graph->djikstra(toupper(n1[0]), toupper(n2[0]));
			
			//if the verticies are connected
			if (path){
				
				cout << "the shortest path from " << (char)toupper(n1[0]) << " to " << (char)toupper(n2[0]) << " is" << endl;
				
				//print the verticies in order (the resulting array is backwards)
				for (int i = path[0]+1; i > 2; i--) {
					cout << (char)(path[i]+65) << "->";
				}
				//dont add an arrow for the last one
				cout << (char)(path[2]+65) << "\nand the distance is " << path[1] << endl;
			}			
		}
		
		//clear the graph
		else if(strcmp(next, "c") == 0 || strcmp(next, "clr") == 0 || strcmp(next, "clear") == 0){
			delete graph;
			graph = new Graph();
			cout << "cleared graph" << endl;
		}
		
		else {
			cout << "not a valid command, type 'help' for a command menu" << endl;
		}
	}

}

void printMenu(){ //print a command menu
	cout << "  h, help\t\t - print this menu" << endl;
	cout << "  q, quit, exit\t\t - exit the program\n" << endl;
	cout << "  i, input, add\t\t - add a vertex or an edge" << endl;
	cout << "  p, print\t\t - print the adjacency matrix of the graph" << endl;
	cout << "  rm, del, remove\t - remove a vertex or an edge" << endl;
	cout << "  c, clr, clear\t\t - clear the graph" << endl;
	cout << "  s, path\t\t - find the shortest path between vertexs" << endl;
}
