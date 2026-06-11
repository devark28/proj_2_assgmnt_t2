#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

#define MAX_HUBS  16
#define MAX_EDGES 64

typedef struct {
    int from;
    int to;
    int cost;
} Edge;

typedef struct {
    int hubCount;
    int matrix[MAX_HUBS][MAX_HUBS];
    char labels[MAX_HUBS];
} HubGraph;

static void graphInit(HubGraph *g, int hubCount, const char *labels) {
    g->hubCount = hubCount;
    for (int i = 0; i < hubCount; i++) {
        g->labels[i] = labels[i];
        for (int j = 0; j < hubCount; j++) g->matrix[i][j] = 0;
    }
}

static void graphAddEdge(HubGraph *g, int u, int v, int cost) {
    g->matrix[u][v] = cost;
    g->matrix[v][u] = cost;
}

static int graphCollectEdges(const HubGraph *g, Edge *edges) {
    int count = 0;
    for (int i = 0; i < g->hubCount; i++) {
        for (int j = i + 1; j < g->hubCount; j++) {
            if (g->matrix[i][j] != 0) {
                edges[count].from = i;
                edges[count].to   = j;
                edges[count].cost = g->matrix[i][j];
                count++;
            }
        }
    }
    return count;
}

static void printAdjacencyMatrix(const HubGraph *g) {
    printf("Adjacency Matrix (0 = no direct link):\n     ");
    for (int i = 0; i < g->hubCount; i++) printf("%4c", g->labels[i]);
    printf("\n");
    for (int i = 0; i < g->hubCount; i++) {
        printf("  %c  ", g->labels[i]);
        for (int j = 0; j < g->hubCount; j++) printf("%4d", g->matrix[i][j]);
        printf("\n");
    }
}

#endif
