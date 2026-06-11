#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

#define MAX_BRANCHES 16
#define MAX_EDGES    128

typedef struct {
    int from;
    int to;
    int weight;
} Edge;

typedef struct {
    int  branchCount;
    int  edgeCount;
    Edge edges[MAX_EDGES];
    char labels[MAX_BRANCHES];
} BankGraph;

static void graphInit(BankGraph *g, int branchCount, const char *labels) {
    g->branchCount = branchCount;
    g->edgeCount = 0;
    for (int i = 0; i < branchCount; i++) g->labels[i] = labels[i];
}

static void graphAddDirected(BankGraph *g, int from, int to, int weight) {
    g->edges[g->edgeCount].from   = from;
    g->edges[g->edgeCount].to     = to;
    g->edges[g->edgeCount].weight = weight;
    g->edgeCount++;
}

static void graphAddUndirected(BankGraph *g, int u, int v, int weight) {
    graphAddDirected(g, u, v, weight);
    graphAddDirected(g, v, u, weight);
}

#endif
