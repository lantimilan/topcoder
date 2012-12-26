/**
* test program for Graph ADT
*/
#include <stdio.h>
#include <stdlib.h>
#include "GRAPH.h"

int main(int argc, char *argv[])
{
    int i, v, w;
    int V, E;

    if (argc != 3) {
        puts("Usage: a.out <V> <E> < edgelist.txt");
        exit(1);
    }
    V = atoi(argv[1]), E = atoi(argv[2]);
    Graph G = GRAPHinit(V, E);
    for (i=0; i<E; ++i) {
        scanf("%d%d", &v, &w);
        GRAPHinsertE(G, EDGE(v, w));
    }

    if (V < 20)
        GRAPHshow(G);
    else printf("%d vertices, %d edges, ", V, E);
    printf("%d components\n", GRAPHcc(G));
    return 0;
}
