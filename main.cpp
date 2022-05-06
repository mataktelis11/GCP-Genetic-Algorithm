#include <iostream>
#include "Graph.h"
#include "genetic.h"

using namespace std;


int main(){

    // set the size of the graph (number of nodes)
    int size = 16;

    // create Graph object
    Graph g(size);
    // add the edges
    g.addEdge(1, 16);
    g.addEdge(1, 15);
    g.addEdge(1, 13);
    g.addEdge(1, 4);
    g.addEdge(1, 3);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(2, 5);
    g.addEdge(2, 9);
    g.addEdge(2, 8);
    g.addEdge(2, 14);
    g.addEdge(2, 15);
    g.addEdge(2, 16);
    g.addEdge(3, 4);
    g.addEdge(3, 6);
    g.addEdge(3, 5);
    g.addEdge(4, 6);
    g.addEdge(4, 13);
    g.addEdge(5, 6);
    g.addEdge(5, 7);
    g.addEdge(5, 9);
    g.addEdge(5, 10);
    g.addEdge(6, 7);
    g.addEdge(6, 11);
    g.addEdge(6, 13);
    g.addEdge(7, 10);
    g.addEdge(7, 11);
    g.addEdge(8, 9);
    g.addEdge(8, 14);
    g.addEdge(9, 10);
    g.addEdge(9, 12);
    g.addEdge(9, 14);
    g.addEdge(10, 11);
    g.addEdge(10, 12);
    g.addEdge(11, 12);
    g.addEdge(11, 13);
    g.addEdge(12, 13);
    g.addEdge(12, 14);
    g.addEdge(12, 15);
    g.addEdge(13, 15);
    g.addEdge(14, 15);
    g.addEdge(15, 16);

    cout << "Adjacency List of the graph is:" << endl;
    g.printGraph();


    run(g);




    return 0;
}