#ifndef UNION_FIND_H
#define UNION_FIND_H

typedef struct {
    int parent[64];
    int rank[64];
} UnionFind;

static void ufInit(UnionFind *uf, int n) {
    for (int i = 0; i < n; i++) {
        uf->parent[i] = i;
        uf->rank[i] = 0;
    }
}

static int ufFind(UnionFind *uf, int x) {
    if (uf->parent[x] != x) {
        uf->parent[x] = ufFind(uf, uf->parent[x]);
    }
    return uf->parent[x];
}

static int ufUnion(UnionFind *uf, int a, int b) {
    int rootA = ufFind(uf, a);
    int rootB = ufFind(uf, b);
    if (rootA == rootB) return 0;

    if (uf->rank[rootA] < uf->rank[rootB]) {
        uf->parent[rootA] = rootB;
    } else if (uf->rank[rootA] > uf->rank[rootB]) {
        uf->parent[rootB] = rootA;
    } else {
        uf->parent[rootB] = rootA;
        uf->rank[rootA]++;
    }
    return 1;
}

#endif
