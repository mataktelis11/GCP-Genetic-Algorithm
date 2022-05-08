#include <iostream>
#include <vector>
using namespace std;


class Graph
{
  public:
    
    int size;
    vector<int>* adj;

    Graph(int s){

        size = s;
        adj = new vector<int>[size+1];
    }


    void addEdge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }


    void printGraph(){
        for (int v = 1; v <= size ; v++){

            cout << v << " ";

            for (int x : adj[v])
                cout << "-> " << x;
            
            printf("\n");
        }
    }


    int countValidEdges(int Vcolors[]){
        int sum = 0;

        for (int i = 1; i <= size ; i++){

            for (int x : adj[i]){
                if(Vcolors[x]!=Vcolors[i])
                    sum+= 1;
            }
        }

        // The total sum of the edges is always even, because
        // in an undirected graph every edge is connected
        // twice between two vertices
        return sum/2;
    }

    int countEdges(){
        int sum = 0;

        for (int i = 1; i <= size ; i++){

            for (int x : adj[i]){
                 sum+= 1;
            }
        }

        // The total sum of the edges is always even, because
        // in an undirected graph every edge is connected
        // twice between two vertices
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

    ~Graph(){
        delete [] adj;
    }

};
