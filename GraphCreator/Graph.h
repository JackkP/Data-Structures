// Graph class for Graph Creator Project, Jack Porter, July 2022

#ifndef GRAPH_H
#define GRAPH_H


using namespace std;

class Graph {
	public:
		
		Graph();

		~Graph();

		int adj[20][20];

		void printAdj();
		
		bool addV(char name); //add a vertex
		bool addE(char n1, char n2, int weight); //add an edge

		bool rmV(char name); //remove a vertex
		bool rmE(char n1, char n2); //remove an edge
		
		int* djikstra(char n1, char n2); //return an array of integers showing the path to the node, last value is the distance, returns null if no path

	private:

};
#endif
