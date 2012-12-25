/**
* A graph ADT
* source: Sedgewick Algorithms in C
*/

#ifndef __LYAN_GRAPH_H
#define __LYAN_GRAPH_H

typedef struct { int v; int w; } Edge;
Edge EDGE(int, int);

typedef struct graph *Graph;
Graph GRAPHinit(int, int);  // number of vertices
void GRAPHinsertE(Graph, Edge);  // insert edge into graph
void GRAPHremoveE(Graph, Edge);  // remove edge from graph
int  GRAPHedges(Edge [], Graph G);  // dump all edges in array
Graph GRAPHcopy(Graph);  // clone graph
void GRAPHdestropy(Graph);  // deallocate memory
void GRAPHshow(Graph);  // print graph
int GRAPHcc(Graph);  // count connected components
#endif
