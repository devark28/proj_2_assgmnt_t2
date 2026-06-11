#include <stdio.h>
#include <ctype.h>
#include "graph.h"
#include "queue.h"

static void bfsDirectNeighbors(const CommGraph *g, int start, int *neighbors, int *outCount) {
    int visited[MAX_NODES] = {0};
    IntQueue q;
    queueInit(&q);

    queuePush(&q, start);
    visited[start] = 1;
    *outCount = 0;

    int current = queuePop(&q);
    for (int v = 0; v < g->nodeCount; v++) {
        if (g->matrix[current][v] != 0 && !visited[v]) {
            visited[v] = 1;
            neighbors[(*outCount)++] = v;
            queuePush(&q, v);
        }
    }
}

int main(void) {
    CommGraph g;
    graphInit(&g, 7, "ABCDEFG");

    graphAddEdge(&g, 0, 1, 6);   /* A-B */
    graphAddEdge(&g, 1, 2, 11);  /* B-C */
    graphAddEdge(&g, 1, 3, 5);   /* B-D */
    graphAddEdge(&g, 2, 3, 17);  /* C-D */
    graphAddEdge(&g, 2, 6, 25);  /* C-G */
    graphAddEdge(&g, 3, 4, 22);  /* D-E */
    graphAddEdge(&g, 4, 5, 10);  /* E-F */
    graphAddEdge(&g, 5, 6, 22);  /* F-G */

    printf("Available workstations: ");
    for (int i = 0; i < g.nodeCount; i++) printf("%c ", g.labels[i]);
    printf("\nEnter the suspected compromised workstation: ");

    char input;
    if (scanf(" %c", &input) != 1) {
        printf("No input received.\n");
        return 1;
    }
    input = toupper((unsigned char)input);

    int startIndex = graphFindLabel(&g, input);
    if (startIndex < 0) {
        printf("Workstation '%c' is not in the network.\n", input);
        return 1;
    }

    int neighbors[MAX_NODES];
    int neighborCount = 0;
    bfsDirectNeighbors(&g, startIndex, neighbors, &neighborCount);

    printf("\nBFS from workstation %c\n", input);
    printf("Directly connected workstations (one-hop neighbors):\n");
    if (neighborCount == 0) {
        printf("  (none)\n");
        return 0;
    }

    int highestNeighbor = neighbors[0];
    int highestWeight   = g.matrix[startIndex][neighbors[0]];

    for (int i = 0; i < neighborCount; i++) {
        int n = neighbors[i];
        int w = g.matrix[startIndex][n];
        printf("  %c --[%d min]--> %c\n", input, w, g.labels[n]);
        if (w > highestWeight) {
            highestWeight = w;
            highestNeighbor = n;
        }
    }

    printf("\nHighest-risk peer: %c (data transfer time = %d minutes)\n",
           g.labels[highestNeighbor], highestWeight);

    return 0;
}
