#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "union_find.h"

static int compareEdgesByCost(const void *a, const void *b) {
    const Edge *ea = (const Edge *)a;
    const Edge *eb = (const Edge *)b;
    return ea->cost - eb->cost;
}

int main(void) {
    HubGraph g;
    graphInit(&g, 7, "ABCDEFG");

    graphAddEdge(&g, 0, 1, 6);   /* A-B */
    graphAddEdge(&g, 1, 2, 11);  /* B-C */
    graphAddEdge(&g, 1, 3, 5);   /* B-D */
    graphAddEdge(&g, 2, 3, 17);  /* C-D */
    graphAddEdge(&g, 2, 6, 25);  /* C-G */
    graphAddEdge(&g, 3, 4, 22);  /* D-E */
    graphAddEdge(&g, 4, 5, 10);  /* E-F */
    graphAddEdge(&g, 5, 6, 22);  /* F-G */

    printAdjacencyMatrix(&g);

    Edge edges[MAX_EDGES];
    int edgeCount = graphCollectEdges(&g, edges);

    qsort(edges, edgeCount, sizeof(Edge), compareEdgesByCost);

    printf("\nSorted edges (ascending cost):\n");
    for (int i = 0; i < edgeCount; i++) {
        printf("  %c-%c : %d\n", g.labels[edges[i].from], g.labels[edges[i].to], edges[i].cost);
    }

    UnionFind uf;
    ufInit(&uf, g.hubCount);

    Edge mst[MAX_EDGES];
    int mstSize = 0;
    int totalCost = 0;

    printf("\nKruskal's selection:\n");
    for (int i = 0; i < edgeCount && mstSize < g.hubCount - 1; i++) {
        char u = g.labels[edges[i].from];
        char v = g.labels[edges[i].to];
        if (ufUnion(&uf, edges[i].from, edges[i].to)) {
            mst[mstSize++] = edges[i];
            totalCost += edges[i].cost;
            printf("  accept  %c-%c (%d)\n", u, v, edges[i].cost);
        } else {
            printf("  skip    %c-%c (%d)   forms a cycle\n", u, v, edges[i].cost);
        }
    }

    printf("\nMinimum Spanning Tree:\n");
    for (int i = 0; i < mstSize; i++) {
        printf("  %c <-> %c   cost = %d\n",
               g.labels[mst[i].from], g.labels[mst[i].to], mst[i].cost);
    }
    printf("\nTotal installation cost: %d million USD\n", totalCost);

    return 0;
}
