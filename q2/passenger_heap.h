#ifndef PASSENGER_HEAP_H
#define PASSENGER_HEAP_H

#include <stdio.h>
#include <string.h>

#define MAX_PASSENGERS 64
#define MAX_NAME_LEN   32

typedef struct {
    char name[MAX_NAME_LEN];
    int riskScore;
} Passenger;

typedef struct {
    Passenger items[MAX_PASSENGERS];
    int size;
} PassengerHeap;

static void swapPassengers(Passenger *a, Passenger *b) {
    Passenger tmp = *a;
    *a = *b;
    *b = tmp;
}

static int parent(int i) { return (i - 1) / 2; }
static int leftChild(int i)  { return 2 * i + 1; }
static int rightChild(int i) { return 2 * i + 2; }

static void siftUp(PassengerHeap *heap, int i) {
    while (i > 0 && heap->items[parent(i)].riskScore < heap->items[i].riskScore) {
        swapPassengers(&heap->items[i], &heap->items[parent(i)]);
        i = parent(i);
    }
}

static void siftDown(PassengerHeap *heap, int i) {
    int largest = i;
    int l = leftChild(i);
    int r = rightChild(i);

    if (l < heap->size && heap->items[l].riskScore > heap->items[largest].riskScore)
        largest = l;
    if (r < heap->size && heap->items[r].riskScore > heap->items[largest].riskScore)
        largest = r;

    if (largest != i) {
        swapPassengers(&heap->items[i], &heap->items[largest]);
        siftDown(heap, largest);
    }
}

static void heapInit(PassengerHeap *heap) {
    heap->size = 0;
}

static void heapAppendRaw(PassengerHeap *heap, const char *name, int risk) {
    Passenger p;
    strncpy(p.name, name, MAX_NAME_LEN - 1);
    p.name[MAX_NAME_LEN - 1] = '\0';
    p.riskScore = risk;
    heap->items[heap->size++] = p;
}

static void buildMaxHeap(PassengerHeap *heap) {
    for (int i = (heap->size / 2) - 1; i >= 0; i--) {
        siftDown(heap, i);
    }
}

static void heapInsert(PassengerHeap *heap, const char *name, int risk) {
    Passenger p;
    strncpy(p.name, name, MAX_NAME_LEN - 1);
    p.name[MAX_NAME_LEN - 1] = '\0';
    p.riskScore = risk;
    heap->items[heap->size++] = p;
    siftUp(heap, heap->size - 1);
}

static int extractMax(PassengerHeap *heap, Passenger *out) {
    if (heap->size == 0) return 0;
    *out = heap->items[0];
    heap->items[0] = heap->items[heap->size - 1];
    heap->size--;
    if (heap->size > 0) siftDown(heap, 0);
    return 1;
}

static int findIndexByRisk(PassengerHeap *heap, int risk) {
    for (int i = 0; i < heap->size; i++) {
        if (heap->items[i].riskScore == risk) return i;
    }
    return -1;
}

static int heapDeleteAt(PassengerHeap *heap, int i) {
    if (i < 0 || i >= heap->size) return 0;
    heap->items[i] = heap->items[heap->size - 1];
    heap->size--;
    if (i < heap->size) {
        siftDown(heap, i);
        siftUp(heap, i);
    }
    return 1;
}

static void printHeapArray(const PassengerHeap *heap) {
    printf("  [");
    for (int i = 0; i < heap->size; i++) {
        printf("(%s, %d)%s", heap->items[i].name, heap->items[i].riskScore,
               i + 1 < heap->size ? ", " : "");
    }
    printf("]\n");
}

static void printHeapTreeHelper(const PassengerHeap *heap, int i, int depth) {
    if (i >= heap->size) return;
    printHeapTreeHelper(heap, rightChild(i), depth + 1);
    for (int s = 0; s < depth; s++) printf("        ");
    printf("[%s:%d]\n", heap->items[i].name, heap->items[i].riskScore);
    printHeapTreeHelper(heap, leftChild(i), depth + 1);
}

static void printHeapTree(const PassengerHeap *heap) {
    printf("  Tree (rotated, root on the left):\n");
    printHeapTreeHelper(heap, 0, 1);
}

#endif
