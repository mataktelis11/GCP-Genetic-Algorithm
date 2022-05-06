#include <iostream>
#include "Graph.h"
#include "genetic.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
#include <string>

using namespace std;


/*


*/
void random_draw(int choices[], int draw_size, int size){

    int draw_number;

    for (int i = 0; i < draw_size; i++){

        do{
            choices[i] = rand() % size;

            for (int j = 0; j < i; j++){

                if(choices[i] == choices[j]){
                    choices[i] = -1;
                    break;
                }
            }
        }while(choices[i]==-1);
    }
}



/*
 m is the size of scores

*/
int roulette(int scores[], int m){

    int sum = 0;

    for (int i = 0; i < m ; i++){
        sum += scores[i];
    }

    //cout<< "sum is: " << sum << endl;

    int choice = rand() % sum +1;

    //cout<< "choice is: " << choice << endl;

    int temp = 0;
    for (int j = 0; j < m ; j++){

        temp += scores[j];

        if(choice <= temp){
            //cout << "choose "<< j <<endl;
            return j;
        }

    }
    return -1;
}

/*


*/
void random_draw_with_roulette(int choices[], int draw_size, int size, int scores[]){
    int draw_number;

    for (int i = 0; i < draw_size; i++){

        do{
            choices[i] = roulette(scores, size);

            for (int j = 0; j < i; j++){

                if(choices[i] == choices[j]){
                    choices[i] = -1;
                    break;
                }
            }
        }while(choices[i]==-1);
    }
}

int main()
{

    // initialize random seed
    srand (time(NULL));

    // set the size of the graph
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

    int edges = g.countEdges();

    cout << "Edges are " << edges << endl;


    int population_size = 60;

    //int limit = 100000;
    int limit = 4000;
    //int limit = 2;

    // mutation percentage
    float mutation_per = 0.1;

    float renew_per = 0.3;

    // initial population
    int P[population_size][size+1];
    // scores of population    
    int scores[population_size];
    // new population
    int Ps[population_size][size+1];

    // helping variables
    int parent1;
    int parent2;

    int index;


    // check for renew percentage
    cout << (1-renew_per)*population_size<<endl;
    cout << (renew_per)*population_size/2<<endl;

    float population_keep_f = (1-renew_per)*population_size;
    float population_pair_f = (renew_per * population_size) / 2;

    int population_keep = (1-renew_per)*population_size;
    int population_pair = (renew_per * population_size) / 2;

    if(population_keep_f == (int)population_keep_f && population_pair_f == (int)population_pair_f)
        cout<<"ok"<<endl;
    else
        return -1;

    // initialize a random population
    for (int i = 0; i < population_size ; i++){

        // first is dummy
        P[i][0] = -1;

        // fill with random values
        for (int j = 1; j <= size ; j++){
            P[i][j] = rand() % 4;
        }

        // calculate "scores"
        scores[i] = g.countValidEdges(P[i]);


        cout << i << " : ";
        // print the color sequence
        printColors(P[i],size);
        cout<<"Number of valid edges: " << scores[i] << endl;
    }

    int end = 0;

    // main loop
    for(int k = 0; k < limit; k++){


        // check for solution
        for (int i = 0; i < population_size; i++){

            if(scores[i] == edges){
                end = 1;
                cout << "Solution found on iteration k =" << k <<endl;
                cout << "Solution is: ";
                printColors(P[i],size);
                cout << endl;

                string solution = "P='";

                for(int xi = 1; xi <= size; xi++ ){
                    solution += to_string(P[i][xi]);
                    solution += " ";
                }
                solution+="' python3 draw.py";
                cout << solution << endl;

                char* char_arr;
                string str_obj(solution);
                char_arr = &str_obj[0];
                cout << char_arr << endl;

                system(char_arr);
            }
                
        }

        if(end==1) break;

        //population_keep

        int renew_size = population_keep;
        int renew_indexes[renew_size];

        random_draw_with_roulette(renew_indexes,renew_size,population_size, scores);

        cout << "renew indexes: ";
        for (int m=0;m<renew_size;m++){
            cout << renew_indexes[m]<< " ";
        }
        cout<<endl;

        // pass parents to Ps
        for (int i = 0; i < renew_size; i++){

            for (int j = 0; j < size+1; j++){
                
                Ps[i][j] = P[renew_indexes[i]][j];
            }
        }




        // pairing

        index = population_keep;


        for (int i = 0; i < population_pair; i++){

            parent1 = roulette(scores,population_size);
            parent2 = roulette(scores,population_size);

            while(parent1 == parent2){

                parent2 = roulette(scores,population_size);
            }

            cout << "Pairing members " << parent1 << " " << parent2 << endl;
            cout<<index<<endl;
            cout<<index+1<<endl;

            do_crossover_single_point(P[parent1],P[parent2],Ps[index],Ps[index+1],size);

            index += 2;

        }
        


        cout << "New population:"<<endl;


        for (int i = 0; i < population_size ; i++){


            // calculate "scores"
            scores[i] = g.countValidEdges(Ps[i]);


            cout << i << " : ";
            // print the color sequence
            printColors(Ps[i],size);
            cout<<"Number of valid edges: " << scores[i] << endl;
        }


        // mutation

        int mutation_size = round(population_size * mutation_per);
        int mutation_indexes[mutation_size];

        // for (int m=0;m<mutation_size;m++){
        //     mutation_indexes[m] = m;
        // }

        random_draw(mutation_indexes,mutation_size,population_size);


        for (int m=0;m<mutation_size;m++){
            
            int new_color = rand() % 4;
            
            int position = rand() % size + 1;

            Ps[mutation_indexes[m]][position] = new_color;

            cout<< "Mutate member " << mutation_indexes[m] << " on position "<< position << " with color " << new_color << endl;
        }
        

        // int new_color = rand() % 4;
        // int member = rand() % population_size;
        // int position = rand() % size + 1;

        // cout<< "Mutate member " << member << " on position "<< position << " with color " << new_color << endl;

        // Ps[member][position] = new_color;

        cout << "New population after mutation:"<<endl;

        for (int i = 0; i < population_size ; i++){

            // calculate "scores"
            scores[i] = g.countValidEdges(Ps[i]);


            cout << i << " : ";
            // print the color sequence
            printColors(Ps[i],size);
            cout<<"Number of valid edges: " << scores[i] << endl;
        }

        // copy population from Ps to P
        for (int i = 0; i < population_size; i++){

            for (int j = 0; j < size+1; j++){
                
                P[i][j] = Ps[i][j];
            }
        }

    }

    if(end==0){
        cout << "Algorithm exeded the maximum number of iterations and solution was NOT found" << endl;
        cout << "Aborting . . ." << endl;
        //return -1;
    }


    // check
    // cout << "again population:"<<endl;


    // for (int i = 0; i < population_size ; i++){


    //     // calculate "scores"
    //     scores[i] = g.countValidEdges(P[i]);


    //     cout << i << " : ";
    //     // print the color sequence
    //     g.printColors(P[i]);
    //     cout<<"Number of valid edges: " << scores[i] << endl;
    // }

    

    // int child1[size+1];
    // int child2[size+1];


    // do_crossover(P[0],P[1],child1,child2,size);

    // cout << "child1 is: ";
    // g.printColors(child1);
    // cout << endl;

    // cout << "child2 is: ";
    // g.printColors(child2);
    // cout << endl;


    // // check the color sequence
    // if(g.checkColors(P)==true)
    //     cout<< "The coloring is valid" <<endl;
    // else{
    //     cout<< "The coloring is invalid" <<endl;
    // }

    //cout<<"Number of valid edges: " << g.countValidEdges(P) << endl;



        // renew test

        // int renew_size = 10;
        // int renew_indexes[renew_size];


        // random_draw_with_roulette(renew_indexes,renew_size,population_size, scores);

        // for (int m=0;m<renew_size;m++){
        //     cout << renew_indexes[m]<< " ";
        // }
        // cout<<endl;

        // for (int m=0;m<renew_size;m++){
        //     cout << scores[renew_indexes[m]]<< " ";
        // }
        // cout<<endl;


    return 0;
} 
