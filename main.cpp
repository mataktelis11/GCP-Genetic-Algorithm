#include <iostream>
#include "Graph.h"
#include "genetic.h"

using namespace std;

/*
Main function that calls solves the Graph Coloring Problem
for a specific graph by using a genetic algorithm

If the genetic algorithm finds a solution, a python script is
called that will display the graph with the colors choosen.

See documentation for further details.
*/

int main(int argc, char* argv[]){

    // the command you use on your terminal to call Python 3.
    string PYTHONCALL = "python3"; // default value

    // give the command you on your terminal to call Python 3 as a main arg
    if(argc == 2){
        PYTHONCALL = argv[1];
    }
    if(argc > 2){
        cout << "Too many arguments given"<<endl;
        return -1;
    }

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

    // initialize chromosome that will have the solution
    // (first element is dummy)
    int solution[size+1];

    bool check = run(g, 100, 5000, 0.05, 0.3, solution);

    if(check){

        // create command
        string command = PYTHONCALL + " python_scripts/draw.py ";

        for(int xi = 1; xi <= size; xi++ ){
            command += to_string(solution[xi]);
            command += " ";
        }

        cout <<"Will run the following command to display graph:"<<endl;
        cout<< command << endl;

        // turn string into char*
        char* char_command;
        string str_obj(command);
        char_command = &str_obj[0];

        // call the command
        system(char_command);
    }

    return 0;
}