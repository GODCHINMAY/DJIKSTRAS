#include "Dijkstra.hpp"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

Dijkstra::Dijkstra(string fname) {
    readFile(fname);
    Interface();
    runDijkstra();
    printPath();
}

// WRITE THIS (10 pts)
void Dijkstra::runDijkstra() {
    // Set the distance to the start vertex to 0 and visited to true for the start index
    distances[start] = 0;
    visited[start] = true;

    // Initialize the distances from the start city
    for (int i = 0; i < numOfCities; i++) {
        if (i != start) {
            distances[i] = matrixGraph[start][i];
            if (distances[i] < 100000) {
                prev[i] = start;
            }
        }
    }

    // Iterate until all vertices are visited or no more reachable vertices remain
    for (int count = 0; count < numOfCities - 1; count++) {
        int u = minDistance();  // find the unvisited vertex with the smallest distance
        if (u == -1) break;     // no more reachable vertices

        setDistances(u);        // update distances of neighbors

        // Uncomment this line if you want to see intermediate states:
        //printInfoSoFar();
    }
}

// WRITE THIS (12 pts)
void Dijkstra::setDistances(int latestVert) {
    // Update distances if going through latestVert is cheaper
    for (int i = 0; i < numOfCities; i++) {
        if (!visited[i] && matrixGraph[latestVert][i] < 100000) {
            int alt = distances[latestVert] + matrixGraph[latestVert][i];
            if (alt < distances[i]) {
                distances[i] = alt;
                prev[i] = latestVert;
            }
        }
    }
}

// WRITE THIS (8 pts)
int Dijkstra::minDistance() {
    int minDist = 100000;
    int minIndex = -1;

    for (int i = 0; i < numOfCities; i++) {
        if (!visited[i] && distances[i] < minDist) {
            minDist = distances[i];
            minIndex = i;
        }
    }

    if (minIndex != -1) {
        visited[minIndex] = true;
    }

    return minIndex;
}

// WRITE THIS (12 pts)
void Dijkstra::printPath() {
    if (distances[end] == 100000) {
        cout << "No path exists from " << Cities[start] << " to " << Cities[end] << endl;
        return;
    }

    // Backtrack from end to start using prev array
    int temp = end;
    int pathSize = 0;
    while (temp != -1) {
        pathSize++;
        temp = prev[temp];
    }

    string* pathArr = new string[pathSize];
    temp = end;
    for (int i = pathSize - 1; i >= 0; i--) {
        pathArr[i] = Cities[temp];
        temp = prev[temp];
    }

    cout << "The shortest path from " << Cities[start] << " to " << Cities[end] << " is: " << endl;
    for (int i = 0; i < pathSize; i++) {
        cout << pathArr[i];
        if (i < pathSize - 1) cout << " -> ";
    }
    cout << endl;
    cout << "Total distance: " << distances[end] << endl;

    delete[] pathArr;
}
/************************************************************/
/* That's the end of what you have to write                 */
/************************************************************/

// A utility function to print the constructed distance array
void Dijkstra::printMatrix() {
    cout <<"********************************************" << endl << "Adjacency Matrix (of Cities and Distances):"<<endl;
    for (int i = 0; i< numOfCities;i++) {
        for (int j = 0; j < numOfCities; j++) {
            cout << matrixGraph[i][j] << "\t";
        }
        cout << endl;
    }
    cout <<"********************************************" << endl;
}

//Another utility method to print out the different arrays so far
//so you can see their content
void Dijkstra::printInfoSoFar() {
    cout <<"\t";
    for (int i = 0; i < numOfCities; i++) {
        cout << "\t"<<i;
    }
    cout << endl;
    cout << "Dist:\t";
    for (int i = 0; i < numOfCities; i++) {
        cout << "\t"<<distances[i];
    }
    cout << endl;
    cout << "Prev:\t";
    for (int i = 0; i < numOfCities; i++) {
        cout << "\t"<<prev[i];
    }
    cout << endl;
    cout << "Visited:";
    for (int i = 0; i < numOfCities; i++) {
        cout << "\t"<<visited[i];
    }
    cout << endl;
    cout << endl;
}

/*************************************************************/
/* This is the user interface that allows you to choose your
/* start and end city you're traveling through.  You should not
/* need to touch this.
/*************************************************************/
void Dijkstra::Interface() {
    cout << "Choose from the following: "<<endl;
    for (int i = 0; i < numOfCities; i++) {
        cout << "\t" << i << ": " << Cities[i] << endl;
    }
    cout << endl;
    cout << "Choose your starting city (with the city's corresponding number): ";
    cin >> start;
    cout << "Choose your end destination (with the city's corresponding number): ";
    cin >> end;
}

/*************************************************************/
/* This method reads in the different Map files and initializes
/* all your arrays along with the adjacency matrix.  It
/* initializes the following:
/*
/* numOfCities: the number of cities in the adjacency matrix
/*
/* Cities: an array filled with the list of cities - the index in
/* the array is the number corresponding with each city (which
/* can be utilized when printing out the path
/*
/* visited: set to false for all cities (indices) to start
/*
/* prev: set to -1 (aka no previous city) for each index to start
/*
/* distance: set to a really large number for all indices to
/* start
/*
/* matrixGraph: this is your adjacency matrix that holds the
/* distance from each city to each city.  It is initialized in
/* here with values read in from the different Map***.txt files
/*
/* You should not need to touch this method.
/*************************************************************/
void Dijkstra::readFile(string fn) {
    ifstream file(fn.c_str());
    int numcities;
    file>>numcities;
    numOfCities = numcities;
    Cities = new string[numOfCities];
    visited = new bool[numOfCities];
    prev = new int[numOfCities];
    distances = new int[numOfCities];
    matrixGraph = new int*[numOfCities];
    for (int i = 0; i < numOfCities; i++) {
        matrixGraph[i] = new int[numOfCities];
        distances[i] = 100000;
        visited[i] = false;
        prev[i] = -1;
    }
    string abbr;
    string city;
    string abbrCity;
    for (int i = 0; i < numOfCities; i++) {
        file >> abbr;
        file >> city;
        abbrCity = abbr + " " + city;
        Cities[i] = abbrCity;
    }
    for (int ct = 0; ct < numOfCities; ct++)  {
        file >> abbr;
        file>>city;
        for (int i = 0; i < numOfCities; i++) {
            int x;
            file >> x;
            if (x == -1) {
                matrixGraph[ct][i] = 100000;
            }
            else matrixGraph[ct][i] = x;
        }
    }
    printMatrix();
    return;
}
