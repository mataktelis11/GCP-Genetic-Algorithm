


void do_crossover_single_point(int parent1[], int parent2[], int child1[], int child2[], int m){

    int n = m/2;

    //cout << "n is "<< n <<endl;

    for (int i = 1; i <= n; i++){
        child1[i] = parent1[i];
        child2[i] = parent2[i];
    }

    for (int i = n+1; i <= m; i++){
        child1[i] = parent2[i];
        child2[i] = parent1[i];
    }

}


void printColors(int Vcolors[],int size){
    for (int i = 1; i <= size ; i++){
        cout << Vcolors[i] << " ";
    }
    //printf("\n");
}