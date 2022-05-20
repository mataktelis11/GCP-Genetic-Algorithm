#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string>
#include <unordered_map>

using namespace std;


/*
Args:
    float a,b
    float epsilon : a very small float number (default value=0.005)

Compare 2 the given float numbers. This is done by using a small 'epsilon' value.
(The '==' shouldn't be used when comparing floats. Source: https://noobtuts.com/cpp/compare-float-values)

*/
bool cmpfloats(float a, float b, float epsilon = 0.005f){
    return (fabs(a - b) < epsilon);
}


/*
Args:
    int P[]: a chromosome
    int chromosome_size: the chromosome's size

Print the given chromosome. Doesn't print a new line.

*/
void print_chromosome(int P[],int chromosome_size){
    for (int i = 1; i <= chromosome_size ; i++){
        cout << P[i] << " ";
    }
}


/*
Args:
    int parent1[], parent2[]: the parent chromosomes
    int child1[], child2[]: the child chromosomes that will be born
    int m: size of chromosomes
    bool random: indicates if the point of cross over will be in the middle or random

Implements the single point crossover. The children are stored
in the arguments child1 and child2.

*/
void do_crossover_single_point(int parent1[], int parent2[], int child1[], int child2[], int m, bool random){

    int n; // index point of cross over

    if(!random)
        n = m/2;        // cross over in the middle
    else
        n = rand() % m; // cross over random

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
Generates random numbers with values from 0 to 'size'.
These numbers are all unique and passed to the argument 'choices[]'

draw_size: number of random numbers that will be generated

*/
void random_draw(int choices[], int draw_size, int size){

    for (int i = 0; i < draw_size; i++){

        // check if current generated number is equal to any of the
        // previous ones. If yes, generate new one.
        do{
            choices[i] = rand() % size;

            for (int j = 0; j < i; j++){

                if(choices[i] == choices[j]){
                    choices[i] = -1; // indicates the number has already been generated
                    break;
                }
            }
        }while(choices[i]==-1);
    }
}


/*
Args:
    int[] fitness: array containing the fitness values of the population
    int m: is size of fitness array

Performs the roulette test and returns the chosen chromosome index (number from 0 to m)

*/
int roulette(int fitness[], int m){

    // find sum of fitness values
    int sum = 0;

    for (int i = 0; i < m ; i++){
        sum += fitness[i];
    }

    int choice = rand() % sum +1; // rand number from 1 to sum

    int temp = 0;
    for (int j = 0; j < m ; j++){

        temp += fitness[j];

        if(choice <= temp){
            return j;
        }
    }

    return -1; // unreachable (just to avoid warning)
}


/*
Generates random numbers from 0 to 'size' by using roulette.
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
    int fitness[]: array containing the fitness values of the population
    int population_size: the population size (= length of fitness)

    Returns true if the population converges

*/
bool check_if_population_converges(int fitness[], int population_size){
    // This function must count the duplicates of array 'fitness'.
    // It does so by incrementing every element of 'fitness' to an unordered_map.
    // This way the unordered_map contains the count of each encountered number.
    unordered_map<int, int> counts;

    for (int i = 0; i < population_size ; i++){
        counts[fitness[i]]++;
    }

    // A population converges when 95% of chromosome have the same fitness
    int number = round(population_size * 0.95);

    // Loop through the unordered map to check
    for (auto x : counts){
        if(x.second >= number)
            return true;
    }
    return false;
}


/*
Args:
    Graph g: graph object to solve the Graph Coloring Problem
    int population_size: the size of the population
    int generations_limit: the maximum number of iterations the algorithm is allowed to do
    float mutation_per: the mutation percentage
    float renew_per: the renew percentage
    int solution[]: array to write the solution (the fittest chromosome)
    bool random_cross_over: indicates if the point of cross over will be in the middle or random

Creates a random initial population and executes the main loop of the Genetic Algorithm.
Returns 'true' if solution was found.

*/
bool run(Graph g, int population_size, int generations_limit, float mutation_per, float renew_per, int solution[], bool random_cross_over=false) {

    // initialize random seed
    srand (time(NULL));

    // get the size of the chromosomes (= number of nodes of the graph)
    int chromosome_size = g.size; // size is the number of nodes
    //get the number of edges
    int edges = g.countEdges();

    // initial population
    int P[population_size][chromosome_size+1];
    // fitness of population
    int fitness[population_size];
    // new population
    int Ps[population_size][chromosome_size+1];

    // helping variables
    int parent1;
    int parent2;
    int index;

    // renew percentage check
    float population_keep_f = (1-renew_per)*(float)population_size;
    float population_pair_f = (renew_per * (float)population_size) / 2;

    if (cmpfloats(population_keep_f,floor(population_keep_f)) && cmpfloats(population_pair_f,floor(population_pair_f))){
        cout << "Given arguments are valid are valid." << endl;
    }
    else {
        cout << "Argument renew_per is NOT valid. Please use different arguments." << endl;
        return false;
    }

    // initialize a random population
    for (int i = 0; i < population_size ; i++){

        // first is dummy
        P[i][0] = -1;

        // fill with random values
        for (int j = 1; j <= chromosome_size ; j++){
            P[i][j] = rand() % 4;
        }

        // calculate fitness foreach chromosome
        fitness[i] = g.countValidEdges(P[i]); // fitness is the number of valid edges in the graph
    }

    /*
    // DEBUG ONLY
    cout << "Initial Population is:" << endl;
    for (int i = 0; i < population_size; i++){
        cout << i << " : ";
        print_chromosome(P[i],chromosome_size);
        cout << "Number of valid edges: " << fitness[i] << endl;
    }
    */

    // main loop
    for(int k = 0; k < generations_limit; k++){

        // check if there is a solution in the population
        for (int i = 0; i < population_size; i++){

            if(fitness[i] == edges){

                cout << "Solution found on iteration k = " << k <<endl;
                cout << "Solution is: ";
                print_chromosome(P[i],chromosome_size);
                cout << endl;

                // copy the chromosome to the argument 'solution'
                for(int xi = 1; xi <= chromosome_size; xi++ ){
                    solution[xi] = P[i][xi];
                }

                return true;
            }
        }

        // check if population converges
        if(check_if_population_converges(fitness,population_size)){
            cout << "The population converges before a solution could be found."<<endl;
            cout << "Aborting on iteration k = " << k <<endl;
            return false;
        }

        // Choose some chromosomes that will pass from P to Ps

        int renew_size = (int)population_keep_f;
        int renew_indexes[renew_size];

        random_draw_with_roulette(renew_indexes,renew_size,population_size, fitness);

        //cout << "Chromosome indexes that will go to Ps: ";
        //for (int m=0;m<renew_size;m++){
            //cout << renew_indexes[m]<< " ";
        //}
        //cout<<endl;

        // pass these chromosomes from P to Ps
        for (int i = 0; i < renew_size; i++){

            for (int j = 0; j < chromosome_size+1; j++){
                
                Ps[i][j] = P[renew_indexes[i]][j];
            }
        }

        // Pair some chromosomes and add the children to Ps

        index = (int)population_keep_f;

        for (int i = 0; i < (int)population_pair_f; i++){

            parent1 = roulette(fitness,population_size);
            parent2 = roulette(fitness,population_size);

            while(parent1 == parent2){

                parent2 = roulette(fitness,population_size);
            }

            //cout << "Pairing members " << parent1 << " " << parent2 << endl;

            do_crossover_single_point(P[parent1],P[parent2],Ps[index],Ps[index+1],chromosome_size,random_cross_over);

            index += 2;
        }
        
        // Mutation

        int mutation_size = round(population_size * mutation_per); // number of the chromosomes that will be mutated
        int mutation_indexes[mutation_size]; //The indexes of the chromosomes that will be mutated

        // randomly (uniform) choose the indexes
        random_draw(mutation_indexes,mutation_size,population_size);

        for (int m=0;m<mutation_size;m++){

            int position = rand() % chromosome_size + 1;

            int new_color = rand() % 4;
            // make sure the mutation doesn't choose the same color 
            // as the existing one
            while(Ps[mutation_indexes[m]][position] == new_color){
                new_color = rand() % 4;
            }

            Ps[mutation_indexes[m]][position] = new_color;

            //cout<< "Mutate member " << mutation_indexes[m] << " on position "<< position << " with color " << new_color << endl;
        }
        
        // copy population from Ps to P
        for (int i = 0; i < population_size; i++){
            for (int j = 0; j < chromosome_size+1; j++){
                P[i][j] = Ps[i][j];
            }
        }

        // calculate fitness of P
        for (int i = 0; i < population_size ; i++){
            fitness[i] = g.countValidEdges(P[i]);
        }

    }

    cout << "Algorithm reached the maximum number of iterations and solution was NOT found." << endl;
    cout << "Aborting . . ." << endl;
    return false;
}
