#include <stdio.h>
#include "graph.h"
#include "bellman_ford.h"

int main(void) {
    BankGraph g;
    graphInit(&g, 10, "ABCDEFGHIJ");

    graphAddUndirected(&g, 0, 1,  4);   /* A-B */
    graphAddUndirected(&g, 0, 3, 16);   /* A-D */
    graphAddUndirected(&g, 1, 2,  6);   /* B-C */
    graphAddUndirected(&g, 1, 3,  6);   /* B-D */
    graphAddUndirected(&g, 1, 9,  7);   /* B-J */
    graphAddUndirected(&g, 2, 6,  9);   /* C-G */
    graphAddUndirected(&g, 3, 4,  7);   /* D-E */
    graphAddUndirected(&g, 4, 5, 10);   /* E-F */
    graphAddUndirected(&g, 4, 8,  2);   /* E-I */
    graphAddUndirected(&g, 5, 8, 10);   /* F-I */
    graphAddUndirected(&g, 5, 9,  3);   /* F-J */
    graphAddUndirected(&g, 6, 7, 13);   /* G-H */

    int source = 0;
    printf("Source branch: %c\n\n", g.labels[source]);

    printf("Edge list (directed pairs from the undirected channels):\n");
    for (int i = 0; i < g.edgeCount; i++) {
        printf("  %c -> %c   weight = %d\n",
               g.labels[g.edges[i].from], g.labels[g.edges[i].to], g.edges[i].weight);
    }

    BFResult result;
    bellmanFord(&g, source, &result);

    printf("\nNegative-weight cycle detected: %s\n",
           result.negativeCycle ? "YES" : "no");

    if (result.negativeCycle) {
        printf("Shortest paths are unreliable in the presence of a negative cycle.\n");
        return 0;
    }

    printf("\nShortest transaction routes from branch %c:\n", g.labels[source]);
    for (int v = 0; v < g.branchCount; v++) {
        if (v == source) continue;
        printf("  %c -> %c : ", g.labels[source], g.labels[v]);
        if (result.distance[v] == BF_INF) {
            printf("unreachable\n");
        } else {
            printf("cost = %-3d  path = ", result.distance[v]);
            printPath(&g, &result, v);
            printf("\n");
        }
    }

    return 0;
}
