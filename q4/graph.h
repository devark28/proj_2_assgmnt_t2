#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

#define MAX_NODES 16

typedef struct {
    int  nodeCount;
    int  matrix[MAX_NODES][MAX_NODES];
    char labels[MAX_NODES];
} CommGraph;

static void graphInit(CommGraph *g, int nodeCount, const char *labels) {
    g->nodeCount = nodeCount;
    for (int i = 0; i < nodeCount; i++) {
        g->labels[i] = labels[i];
        for (int j = 0; j < nodeCount; j++) g->matrix[i][j] = 0;
    }
}

static void graphAddEdge(CommGraph *g, int u, int v, int weight) {
    g->matrix[u][v] = weight;
    g->matrix[v][u] = weight;
}

static int graphFindLabel(const CommGraph *g, char label) {
    for (int i = 0; i < g->nodeCount; i++) {
        if (g->labels[i] == label) return i;
    }
    return -1;
}

#endif
