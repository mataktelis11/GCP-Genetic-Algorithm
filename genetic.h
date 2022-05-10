#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string>

using namespace std;


/*
Args:
    float a,b
    float epsilon : a very small float number (default value=0.005)

Compare 2 given float numbers

*/
bool cmpfloats(float a, float b, float epsilon = 0.005f)
{
    return (fabs(a - b) < epsilon);
}


/*
Args:
    P a chromosome
    size the chromosome's size

Print the given chromosome

*/
void print_chromosome(int P[],int size){
    for (int i = 1; i <= size ; i++){
        cout << P[i] << " ";
    }
    //printf("\n");
}


/*
Args:
    parent1, parent2: the parent chromosomes
    child1, child2: the child chromosomes that will be born
    m: size of chromosomes

Implements the single point crossover. The children are stored
in the arguments child1 and child2.

*/
void do_crossover_single_point(int parent1[], int parent2[], int child1[], int child2[], int m){

    int n = m/2;

    for (int i = 1; i <= n; i++){
        child1[i] = parent1[i];
        child2[i] = parent2[i];
    }

    for (int i = n+1; i <= m; i++){
        child1[i] = parent2[i];
        child2[i] = parent1[i];
    }
}


/*
Generates random number from 0 to 'size'.
These numbers are all unique and passed to the argument 'choices[]'

draw_size: number of random numbers that will be generated

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
Args:
    int[] fitness: the fitness array
    int m: is size of fitness array

Performs the roulette test and returns the chosen chromosome index

*/
int roulette(int fitness[], int m){

    // find sum
    int sum = 0;

    for (int i = 0; i < m ; i++){
        sum += fitness[i];
    }

    //cout<< "sum is: " << sum << endl;

    int choice = rand() % sum +1;

    //cout<< "choice is: " << choice << endl;

    int temp = 0;
    for (int j = 0; j < m ; j++){

        temp += fitness[j];

        if(choice <= temp){
            //cout << "choose "<< j <<endl;
            return j;
        }

    }
    return -1;
}


/*
Generates random number from 0 to 'size' by using roulette.
These numbers are all unique and passed to the argument 'choices[]'

draw_size: number of random numbers that will be generated

*/
void random_draw_with_roulette(int choices[], int draw_size, int size, int fitness[]){
    int draw_number;

    for (int i = 0; i < draw_size; i++){

        do{
            choices[i] = roulette(fitness, size);

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
Args:
    Graph g: graph object to solve the Graph Coloring Problem
    int population_size: the size of the population
    int limit: the maximum number of iterations the algorithm is allowed to do
    float mutation_per: the mutation percentage
    float renew_per: the renew percentage
    int solution[]: array to write the solution (the fitest chromosome)


Creates a random initial population and executes the main loop.
Returns 'true' if solution was found.

*/
bool run(Graph g, int population_size, int limit, float mutation_per, float renew_per, int solution[]) {

    // initialize random seed
    srand (time(NULL));

    // get the size of the graph
    int size = g.size;
    //get the 
    int edges = g.countEdges();

    // initial population
    int P[population_size][size+1];
    // fitness of population
    int fitness[population_size];
    // new population
    int Ps[population_size][size+1];

    // helping variables
    int parent1;
    int parent2;
    int index;

    // renew percentage check
    float population_keep_f = (1-renew_per)*(float)population_size;
    float population_pair_f = (renew_per * (float)population_size) / 2;

    int population_keep = (1-renew_per)*(float)population_size;
    int population_pair = (renew_per * (float)population_size) / 2;


    if(cmpfloats(population_keep_f,floor(population_keep_f)) && cmpfloats(population_pair_f,floor(population_pair_f))){
        cout<<"Renew percentages are valid."<<endl;
    }
    else{
        cout << "Renew percentages are NOT valid."<<endl;
        return false;
    }

    // initialize a random population
    for (int i = 0; i < population_size ; i++){

        // first is dummy
        P[i][0] = -1;

        // fill with random values
        for (int j = 1; j <= size ; j++){
            P[i][j] = rand() % 4;
        }

        // calculate "fitness"
        fitness[i] = g.countValidEdges(P[i]);


        //cout << i << " : ";
        // print the color sequence
        //print_chromosome(P[i],size);
        //cout<<"Number of valid edges: " << fitness[i] << endl;
    }


    // main loop
    for(int k = 0; k < limit; k++){

        // check for solution
        for (int i = 0; i < population_size; i++){

            if(fitness[i] == edges){

                cout << "Solution found on iteration k = " << k <<endl;
                cout << "Solution is: ";
                print_chromosome(P[i],size);
                cout << endl;

                // copy the chromosome to the argument 'solution'
                for(int xi = 1; xi <= size; xi++ ){
                    solution[xi] = P[i][xi];
                }

                return true;
            }
        }

        //population_keep

        int renew_size = population_keep;
        int renew_indexes[renew_size];

        random_draw_with_roulette(renew_indexes,renew_size,population_size, fitness);

        //cout << "renew indexes: ";
        for (int m=0;m<renew_size;m++){
            //cout << renew_indexes[m]<< " ";
        }
        //cout<<endl;

        // pass chromosomes from P to Ps
        for (int i = 0; i < renew_size; i++){

            for (int j = 0; j < size+1; j++){
                
                Ps[i][j] = P[renew_indexes[i]][j];
            }
        }

        // pairing

        index = population_keep;


        for (int i = 0; i < population_pair; i++){

            parent1 = roulette(fitness,population_size);
            parent2 = roulette(fitness,population_size);

            while(parent1 == parent2){

                parent2 = roulette(fitness,population_size);
            }

            //cout << "Pairing members " << parent1 << " " << parent2 << endl;
            //cout<<index<<endl;
            //cout<<index+1<<endl;

            do_crossover_single_point(P[parent1],P[parent2],Ps[index],Ps[index+1],size);

            index += 2;

        }
        
        // calculate the

        //cout << "New population:"<<endl;

        // for (int i = 0; i < population_size ; i++){


        //     // calculate "fitness"
        //     fitness[i] = g.countValidEdges(Ps[i]);


        //     //cout << i << " : ";
        //     // print the color sequence
        //     //print_chromosome(Ps[i],size);
        //     //cout<<"Number of valid edges: " << fitness[i] << endl;
        // }


        // mutation

        int mutation_size = round(population_size * mutation_per);
        int mutation_indexes[mutation_size];

        random_draw(mutation_indexes,mutation_size,population_size);


        for (int m=0;m<mutation_size;m++){

            int position = rand() % size + 1;

            int new_color = rand() % 4;
            // make sure the mutation doesn't choose the same color 
            // as the existing one
            while(Ps[mutation_indexes[m]][position] == new_color){
                new_color = rand() % 4;
            }

            Ps[mutation_indexes[m]][position] = new_color;

            //cout<< "Mutate member " << mutation_indexes[m] << " on position "<< position << " with color " << new_color << endl;
        }
        

        //cout << "New population after mutation:"<<endl;

        for (int i = 0; i < population_size ; i++){

            // calculate "fitness"
            fitness[i] = g.countValidEdges(Ps[i]);


            //cout << i << " : ";
            // print the color sequence
            //print_chromosome(Ps[i],size);
            //cout<<"Number of valid edges: " << fitness[i] << endl;
        }

        // copy population from Ps to P
        for (int i = 0; i < population_size; i++){
            for (int j = 0; j < size+1; j++){
                P[i][j] = Ps[i][j];
            }
        }

    }

    cout << "Algorithm exeded the maximum number of iterations and solution was NOT found" << endl;
    cout << "Aborting . . ." << endl;
    return false;
}
