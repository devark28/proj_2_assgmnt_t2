#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include <limits.h>
#include "graph.h"

#define BF_INF INT_MAX

typedef struct {
    int distance[MAX_BRANCHES];
    int predecessor[MAX_BRANCHES];
    int negativeCycle;
} BFResult;

static void bellmanFord(const BankGraph *g, int source, BFResult *result) {
    for (int i = 0; i < g->branchCount; i++) {
        result->distance[i] = BF_INF;
        result->predecessor[i] = -1;
    }
    result->distance[source] = 0;
    result->negativeCycle = 0;

    for (int pass = 0; pass < g->branchCount - 1; pass++) {
        for (int e = 0; e < g->edgeCount; e++) {
            int u = g->edges[e].from;
            int v = g->edges[e].to;
            int w = g->edges[e].weight;
            if (result->distance[u] != BF_INF &&
                result->distance[u] + w < result->distance[v]) {
                result->distance[v] = result->distance[u] + w;
                result->predecessor[v] = u;
            }
        }
    }

    for (int e = 0; e < g->edgeCount; e++) {
        int u = g->edges[e].from;
        int v = g->edges[e].to;
        int w = g->edges[e].weight;
        if (result->distance[u] != BF_INF &&
            result->distance[u] + w < result->distance[v]) {
            result->negativeCycle = 1;
            return;
        }
    }
}

static void printPath(const BankGraph *g, const BFResult *result, int target) {
    int stack[MAX_BRANCHES];
    int depth = 0;
    int current = target;
    while (current != -1) {
        stack[depth++] = current;
        current = result->predecessor[current];
    }
    for (int i = depth - 1; i >= 0; i--) {
        printf("%c%s", g->labels[stack[i]], i > 0 ? " -> " : "");
    }
}

#endif
