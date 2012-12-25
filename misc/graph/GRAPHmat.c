// An adjacency matrix implementation of graph ADT
//
#include <stdio.h>
#include <stdlib.h>
#include "GRAPH.h"

struct graph { int V; int E; int **adj; };

// forward declaration
int **MATRIXinit(int r, int c, int val);

Graph GRAPHinit(int V, int E)
{
    Graph G = malloc(sizeof *G);
    G->V = V; G->E = 0;
    G->adj = MATRIXinit(V, V, 0);
    return G;
}

void GRAPHinsertE(Graph G, Edge e)
{
    int v, w;
    v = e.v; w = e.w;
    if (G->adj[v][w] == 0) G->E++;
    G->adj[v][w] = 1;
    G->adj[w][v] = 1;
}

void GRAPHremoveE(Graph G, Edge e)
{
    int v, w;
    v = e.v; w = e.w;
    if (G->adj[v][w] == 1) G->E--;
    G->adj[v][w] = 0;
    G->adj[w][v] = 0;
}

int GRAPHedges(Edge a[], Graph G)
{
    int i, j;
    int E = 0;
    for (i=0; i < G->V; ++i)
        for (j=i+1; j < G->V; ++j)
            if (G->adj[i][j] == 1)
                a[E++] = EDGE(i, j);
    return E;
}

void GRAPHshow(Graph G)
{
    int i, j;
    for (i=0; i < G->V; ++i) {
        printf("%2d:", i);
        for (j=0; j < G->V; ++j) {
            if (G->adj[i][j] == 1)
                printf(" %2d", j);
        }
        printf("\n");
    }
}

int GRAPHcc(Graph G)
{
    return 0;  // dummy implementation
}

// helper function
int **MATRIXinit(int r, int c, int val)
{
    int i, j;
    int **t = malloc(r * sizeof(int *));
    for (i=0; i<r; ++i)
        t[i] = malloc(c * sizeof(int));
    for (i=0; i<r; ++i)
        for (j=0; j<c; ++j)
            t[i][j] = val;
    return t;
}
