# graph-coloring

## MILP Model formulation
The Graph Coloring problem, also known as Vertex Coloring Problem, aims 
to color each vertex of a given graph with the minimal number of different colors, 
given that two adjacent vertex cannot have the same color. See [the wikipedia article](https://en.wikipedia.org/wiki/Graph_coloring) for 
more information.


### Base Model
$$
\begin{align*}
    \min& \sum_{c \in C} y_c\\
    \text{subject to}&\\
    &\sum_{c \in C} x_{ic} = 1\ \ \ \ \forall i \in V\\
    &x_{ic} + x_{jc} \le 1\ \ \ \ \forall(i, j) \in E, \forall c \in C\\
    &x_{ic} \le y_{ic} \ \ \ \ \forall i \in V, \forall c \in C\\
    &x_{ic} \in \lbrace0, 1\rbrace \ \ \ \ \forall i \in V, \forall c \in C\\
    &y_{c} \in \lbrace0, 1\rbrace\ \ \ \ \forall c \in C\\
\end{align*}
$$


### Branch and Price Model

#### Master Problem
$$
\begin{align*}
    \min& \sum_{p \in P} \lambda_p\\
    \text{subject to}&\\
    &\sum_{p \in P} a_{ip}\lambda_p = 1\ \ \ \ \forall i \in V\\
    &\lambda_p \in \lbrace0, 1\rbrace\ \ \ \ \forall p \in P\\
\end{align*}
$$

#### Pricing Problem
$$
\begin{align*}
    \min&\ \ 1 - \sum_{i \in V} \pi_i x_i\\
    \text{subject to}&\\
    &x_{i} + x_{j} \le 1\ \ \ \ \forall(i, j) \in E\\
    &x_{i} \in \lbrace0, 1\rbrace \ \ \ \ \forall i \in V
\end{align*}
$$

## Compile

In order to compile this tool one needs cmake and SCIP.
This tools has been developed and tested using SCIP 8: it may work 
with previous versions but I cannot be sure. cmake scripts are 
configured to work with a system installation of SCIP: you may need to 
modify the configuration if you want or need to use a static linked SCIP library.

To compile *graph-coloring*
```bash
# Configure build environment 
cmake -S . -B build/

# Compile source code
cmake --build build/

# Run unit tests
ctest --test-dir build/
```

Once the compiling and testing procedures are done you will find inside 
the **build/** directory two executables:
+ *bnp-graph-coloring* : branch and price implementation of the graph coloring problem;
+ *graph-coloring* : arc based implementation of the graph coloring problem.

Note: on your platform you may find similar names but with extensions like *.exe*.

### Usage 
The two generated executables takes as input, from the command line, a single 
ASCII DIMACS file. The parser is trivial and assumes that the input file is 
correctly formatted. The parser does not support binary files. 

The two generated executables works in the same way so, for brevity, I will show 
only the usage of *bnp-graph-coloring*.

```bash
./bnp-graph-coloring your-graph.col
```
If you do not provide a graph file as argument the tool will get the graph 
specification from standard input. 
