#ifndef DIJKSTRA_HPP_
#define DIJKSTRA_HPP_

#include <iostream>
#include <stdlib.h>
using namespace std;


class Dijkstra {
	int **matrixGraph;  //the adjacency graph matrix
	int numOfCities;  // total number of cities, read in from 
	// the map file and given a value in readFile()
	int start;  //this is the start city you will type in when
	//the Interface method is run
	int end;  // this is the end city, typed in when you run the 
	//Interface method
	string *Cities;  // the array of cities
	//BinHeap priorityQueue();  // not used - this is how you'd 
	//ideally implement the distance array - I wanted you to be
	//aware that there is an ideal data structure for this
	bool *visited;  //an array of cities - set to true if the
	// city has been visited, originally all set to false
	int *distances;  // the distance needed to get to each city 
	// from the start city so far
	int *prev;  // an array - for each city, it is set to the
	// best previous city for the shortest path
public:
	Dijkstra(string fname);  // constructor with map file name
	void runDijkstra();  // starts the program (see notes in 
	//.cpp for how to write ths
	void Interface();  // already written - this interface 
	//allows you 
	void setDistances(int lv);  // calculates the current 
	//shortest distance - see notes in cpp
	int minDistance();  // finds the next minimumdistance -
	// see cpp for details.
	void printMatrix();  // prints matrix - already written
	void printInfoSoFar();  // prints each of the arrays 
	// (visited, prev, and distance) - already written
	void printPath();  // prints the shortest path when found -
	// see notes in .cpp
	void readFile(string s);  // reads in the Map files and 
	// initializes all the array fields and the numOfCities 
	// field.  It's already written
};



#endif /* DIJKSTRA_HPP_ */
