#include <iostream>
#include <vector>
using namespace std;


class Graph
{
  public:
    
    int size;           // number of nodes
    vector<int>* adj;   // adjacency list

    Graph(int s){

        size = s;
        adj = new vector<int>[size+1];
    }


    /*
    Adds and edge to the adjacency list.

    */
    void addEdge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }


    /*
    Prints the adjacency list in a radable way.

    */
    void printGraph(){
        for (int v = 1; v <= size ; v++){

            cout << v << " ";

            for (int x : adj[v])
                cout << "-> " << x;
            
            printf("\n");
        }
    }


    /*
    Args:
        int Colors[]: an array representing a coloring for the nodes

    Returns the number of valid edges of the graph
    based of the given coloring.

    */
    int countValidEdges(int Colors[]){
        int sum = 0;

        for (int i = 1; i <= size ; i++){

            for (int x : adj[i]){
                if(Colors[x]!=Colors[i])
                    sum+= 1;
            }
        }

        // The total sum of the edges is always even, because
        // in an undirected graph every edge is
        // connected twice between two vertices
        return sum/2;
    }


    /*
    Returns the number of edges of the graph.

    */
    int countEdges(){
        int sum = 0;

        for (int i = 1; i <= size ; i++){

            for (int x : adj[i]){
                 sum+= 1;
            }
        }

        // The total sum of the edges is always even, because
        // in an undirected graph every edge is
        // connected twice between two vertices
        return sum/2;
    }

    // Implementing deep copy
    Graph(Graph& g)
    {
        size = g.size;
        adj = new vector<int>[size+1];

        for (int v = 1; v <= size ; v++){

            for (int x : g.adj[v]){
                adj[v].push_back(x);
            }
        }
    }

    // destructor
    ~Graph(){
        delete [] adj;
    }
};
