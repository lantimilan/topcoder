/**
* A graph ADT
* source: Sedgewick Algorithms in C
*/

typedef struct { int v; int w; } Edge;
Edge EDGE(int, int);

typedef struct graph *Graph;
Graph GRAPHinit(int);  // number of vertices
void GRAPHinsertE(Graph, Edge);  // insert edge into graph
void GRAPHremoveE(Graph, Edge);  // remove edge from graph
int  GRAPHedges(Edge [], Graph G);  // dump all edges in array
Graph GRAPHcopy(Graph);  // clone graph
void GRAPHdestropy(Graph);  // deallocate memory

