#include <iostream>
#include "Graph.h"
#include "genetic.h"

using namespace std;

/*
Main function that calls solves the Graph Coloring Problem
for a specific graph by using a genetic algorithm. The graph
in this case is the map of the USA.

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
    int size = 48;

    // create Graph object
    Graph g(size);
    // add the edges
    g.addEdge(1,8);
    g.addEdge(1,9);
    g.addEdge(1,22);
    g.addEdge(1,40);
    g.addEdge(2,4);
    g.addEdge(2,26);
    g.addEdge(2,29);
    g.addEdge(2,42);
    g.addEdge(3,16);
    g.addEdge(3,22);
    g.addEdge(3,23);
    g.addEdge(3,34);
    g.addEdge(3,40);
    g.addEdge(3,41);
    g.addEdge(4,26);
    g.addEdge(4,35);
    g.addEdge(5,14);
    g.addEdge(5,25);
    g.addEdge(5,29);
    g.addEdge(5,34);
    g.addEdge(5,42);
    g.addEdge(5,48);
    g.addEdge(6,19);
    g.addEdge(6,30);
    g.addEdge(6,37);
    g.addEdge(7,18);
    g.addEdge(7,28);
    g.addEdge(7,36);
    g.addEdge(8,9);
    g.addEdge(9,31);
    g.addEdge(9,38);
    g.addEdge(9,40);
    g.addEdge(10,24);
    g.addEdge(10,26);
    g.addEdge(10,35);
    g.addEdge(10,42);
    g.addEdge(10,45);
    g.addEdge(10,48);
    g.addEdge(11,12);
    g.addEdge(11,13);
    g.addEdge(11,15);
    g.addEdge(11,23);
    g.addEdge(11,47);
    g.addEdge(12,15);
    g.addEdge(12,20);
    g.addEdge(12,33);
    g.addEdge(13,21);
    g.addEdge(13,23);
    g.addEdge(13,25);
    g.addEdge(13,39);
    g.addEdge(13,47);
    g.addEdge(14,23);
    g.addEdge(14,25);
    g.addEdge(14,34);
    g.addEdge(15,23);
    g.addEdge(15,33);
    g.addEdge(15,40);
    g.addEdge(15,44);
    g.addEdge(15,46);
    g.addEdge(16,22);
    g.addEdge(16,41);
    g.addEdge(17,27);
    g.addEdge(18,36);
    g.addEdge(18,44);
    g.addEdge(18,46);
    g.addEdge(19,27);
    g.addEdge(19,30);
    g.addEdge(19,37);
    g.addEdge(19,43);
    g.addEdge(20,33);
    g.addEdge(20,47);
    g.addEdge(21,32);
    g.addEdge(21,39);
    g.addEdge(21,47);
    g.addEdge(22,40);
    g.addEdge(23,25);
    g.addEdge(23,34);
    g.addEdge(23,40);
    g.addEdge(24,32);
    g.addEdge(24,39);
    g.addEdge(24,48);
    g.addEdge(25,39);
    g.addEdge(25,48);
    g.addEdge(26,35);
    g.addEdge(26,42);
    g.addEdge(27,43);
    g.addEdge(28,30);
    g.addEdge(28,36);
    g.addEdge(29,34);
    g.addEdge(29,41);
    g.addEdge(30,36);
    g.addEdge(30,43);
    g.addEdge(31,38);
    g.addEdge(31,40);
    g.addEdge(31,44);
    g.addEdge(32,39);
    g.addEdge(33,36);
    g.addEdge(33,46);
    g.addEdge(34,41);
    g.addEdge(35,45);
    g.addEdge(36,46);
    g.addEdge(39,48);
    g.addEdge(40,44);
    g.addEdge(42,48);
    g.addEdge(44,46);

    //cout << "Adjacency List of the graph is:" << endl;
    //g.printGraph();
    cout <<"USA map graph loaded."<< endl;

    // initialize chromosome that will have the solution
    // (first element is dummy)
    int solution[size+1];

    bool check = run(g, 2000, 1000, 0.015, 1, solution, true); 

    if(check){

        // create command
        string command = PYTHONCALL + " python_scripts/usa_draw.py ";

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