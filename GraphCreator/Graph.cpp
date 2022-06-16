// Graph class for Graph Creator Project, Jack Porter, July 2022
// The implementation is horrible, but it was the last project for the class so what can I say...

#include "Graph.h"
#include <cstring>
#include <iostream>
#include <cmath>

using namespace std;


Graph::Graph(){ //set all the adjacency values to -1 (no vertices exist);
	for (int i = 0; i < 20; i++){
		for (int j = 0; j < 20; j++){
			adj[i][j] = -1;
		}
	}
}

Graph::~Graph(){

}

//print the adjacency matrix in a nice way
void Graph::printAdj(){
	//print the first row (letters with a vertical bar between)
	cout << "   ";
	for (int i = 0; i < 20; i++){
		cout << "| " << (char)(i+65) << "  ";
	}
	cout << endl;
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	
	
	for (int i = 0; i < 20; i++){
		cout << " " << (char)(i+65) << " " ;
		
		//print each adjacency value followed by the number of spaces required for 4 characters
		for (int j = 0; j < 20; j++){
			cout << "|";
			char num[4];
			sprintf(num, "%d", adj[i][j]);
			cout << num;
			for (int i = 0; i < 4-strlen(num); i++) cout << " ";
		}
		cout << endl;
	}
}
		
bool Graph::addV(char name){ //add a vertex or return false if not possible
	if ((int)(name) < 85 && (int)(name) >= 65 && adj[(int)(name)-65][(int)(name)-65] == -1){
		adj[(int)(name)-65][(int)(name)-65] = 0;
		return true;
	}
	return false;
}

bool Graph::addE(char n1, char n2, int weight){ //add an edge or return false if not possible
	if (!(65 <= n1 && n1 < 85 && 65 <= n2 && n2 < 85)){
		cout << "invalid vertex input" << endl;
		return false;
	}
	else if (!adj[(int)(n1)-65][(int)(n2)-65] == -1) {
		cout << "that edge already exists" << endl;
		return false;
	}
	else if (!(adj[(int)(n1)-65][(int)(n1)-65] == 0 && adj[(int)(n2)-65][(int)(n2)-65] == 0)){
		cout << "vertex does not exist" << endl;
		return false;
	}
	else {
		adj[(int)(n1)-65][(int)(n2)-65] = abs(weight);
		adj[(int)(n2)-65][(int)(n1)-65] = abs(weight);

		return true;
	}
}

bool Graph::rmV(char name){ //remove a vertex or return false if not possible
	if ((int)(name) < 85 && (int)(name) >= 65 && adj[(int)(name)-65][(int)(name)-65] == 0){
		adj[(int)(name)-65][(int)(name)-65] = -1;
		for (int i = 0; i < 20; i++){
			adj[(int)name-65][i] = -1;
			adj[i][(int)name-65] = -1;
		}
		return true;
	}
	return false;
}

bool Graph::rmE(char n1, char n2){ //remove an edge or return false if not possible
	if (!(65 <= n1 && n1 < 85 && 65 <= n2 && n2 < 85)){
		cout << "invalid vertex input" << endl;
		return false;
	}
	else if (adj[(int)(n1)-65][(int)(n2)-65] == -1) {
		cout << "that edge does not exist" << endl;
		return false;
	}
	else {
		adj[(int)(n1)-65][(int)(n2)-65] = -1;
		adj[(int)(n2)-65][(int)(n1)-65] = -1;

		return true;
	}
}

//runs djikstras shortest path algorithm between two verticies
//returns the result as an array of vertices from n2 to n1
//the first value is the number of verticies in the path (including start and end)
//and the second value is the length of the path
int* Graph::djikstra(char n1, char n2){
	n1 = n1-65;
	n2 = n2-65;
	
	if (!(0 <= n1 && n1 < 20 && 0 <= n2 && n2 < 20)){
		cout << "invalid vertex input" << endl;
		return NULL;
	}
	else if (adj[n1][n1] != 0 || adj[n2][n2] != 0) {
		cout << "vertex does not exist" << endl;
		return NULL;
	}
	else {
		int dist[20];
		int prev[20];
		int queue[20];
		
		//enqueue all the vertices that exist
		int count = 0;
		for (int i = 0; i < 20; i++){
			prev[i] = -1;
			if (adj[i][i] == 0) {
				dist[i] = 9999;
				
				//this vertex is the starting vertex
				if (i == n1){
					//the distance is 0 and set previous to -2 so it's special
					dist[i] = 0;
					prev[i] = -2;
				}
				queue[i] = i;
			}
			else {
				dist[i] = -1;
				queue[i] = -1;
			}
		}
				
		while (true) { //break when the queue is empty
			
			//search the queue for the smallest distance, if a -1 is found quit
			int val = 9999;
			int sml = -1;
			bool cont = false;
			for (int i = 0; i < 20; i++){
				if (queue[i] != -1 && dist[i] < val){
					val = dist[i];
					sml = i;
					cont = true;
				}
			}
									
			if (!cont) break;
			
			//remove that v from the queue
			queue[sml] = -1;
			
			//if the destination was reached break the loop
			if (sml == n2){
				break;
			}
						
			//for each vertex
			for (int i = 0; i < 20; i++){
				
				//if i is adjacent and still in the queue
				if (adj[sml][i] != -1 && queue[i] != -1){
					int alt = dist[sml] + adj[sml][i];
					if (alt < dist[i] and dist[sml] != 9999) {
						dist[i] = alt;
						prev[i] = sml;
					}
				}
			} 
		}
				
		if(dist[n2] == 9999) {
			cout << toupper(n1+65) << " is not connected to " << toupper(n2+65) << endl;
			return NULL;
		}
				
		//put the ordered vertices into a list and return the path length
		
		//count the number of vertices in the path
		count = 1;
		int i = n2;
		while (prev[i] != -2) {
			count ++;
			i = prev[i];
		}
				
		//place the vertices in order into an array
		int* path = new int[count+2];
		for (int i = 0; i < count+2; i++){
			path[i] = 0;
		}
		
		path[0] = count;
		path[1] = dist[n2];
		path[count+1] = n1;
		
		count = 2;
		i = n2;
		//repeat until the starting vertex is reached
		while (prev[i] != -2) {
			path[count] = i;
			count++;
			i = prev[i];
		}
		
		return path;
	}
}
