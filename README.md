# GCP-Genetic-Algorithm
Solving the **Graph Coloring Problem** with a **Genetic Algorithm**. The programming language used is **C++**. There are also some Python 3 scripts used to visualize the solutions of the algorithm for two hard-coded graphs. You can edit the **main.cpp** to define your own graph.


## Dependencies
- g++
- Python3
- PIL
- matplotlib


## Usage

First we will solve the Graph Coloring Problem for a small graph.

Clone the repo
```
$ git clone https://github.com/mataktelis11/GCP-Genetic-Algorithm.git
```
Navigate to the folder and compile **main.cpp**
```
$ cd GCP-Genetic-Algorithm
$ g++ main.cpp
$ ./a.out
```
and you should see the following output

<img src="https://user-images.githubusercontent.com/61196956/169772631-3d32713b-82f6-4459-bf69-c451de29aa55.png" width="700">

the algorithm found a solution and called a python script to display it:

<img src="https://user-images.githubusercontent.com/61196956/169773562-11de3163-6460-48eb-9d9c-972cee824951.png" width="500">

You can edit the **main.cpp** file to define any graph you want.

There is a second graph included and it is the map of the U.S.A. It is located in the file **main_usa.cpp**. Simply compile and run it just like **main.cpp**. The graph's edges where extracted from **Matlab's Mapping Toolbox** (see the link in the [**Sources**](##Sources)).

```
$ g++ main_usa.cpp
$ ./a.out
```
you should see the following output


**Warning**
- In the case of the USA graph the program takes a long time to find a solution (~30 seconds). Sometimes the algorithm stops due to its iteration limit without finding a solution. This is due to the high complexity of the graph itself. You can try and modify the arguments in the **run** function or even do a PR. Any suggestions are welcome!
- The python scripts are only used to visualize the hard-coded graphs of the **main** programs.

## Sources
- https://mathigon.org/course/graph-theory/map-colouring
- https://noobtuts.com/cpp/compare-float-values
- https://blogs.mathworks.com/loren/2017/10/12/lorens-excellent-adventure-maps-graphs-and-polygons/
