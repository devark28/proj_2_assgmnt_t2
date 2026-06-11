#ifndef JOB_HEAP_H
#define JOB_HEAP_H

#include <stdio.h>

#define MAX_JOBS 64

typedef struct {
    char id;
    int priority;
} Job;

typedef struct {
    Job items[MAX_JOBS];
    int size;
} JobHeap;

static void swapJobs(Job *a, Job *b) {
    Job tmp = *a;
    *a = *b;
    *b = tmp;
}

static int parent(int i) { return (i - 1) / 2; }
static int leftChild(int i)  { return 2 * i + 1; }
static int rightChild(int i) { return 2 * i + 2; }

static void siftUp(JobHeap *heap, int i) {
    while (i > 0 && heap->items[parent(i)].priority < heap->items[i].priority) {
        swapJobs(&heap->items[i], &heap->items[parent(i)]);
        i = parent(i);
    }
}

static void siftDown(JobHeap *heap, int i) {
    int largest = i;
    int l = leftChild(i);
    int r = rightChild(i);

    if (l < heap->size && heap->items[l].priority > heap->items[largest].priority)
        largest = l;
    if (r < heap->size && heap->items[r].priority > heap->items[largest].priority)
        largest = r;

    if (largest != i) {
        swapJobs(&heap->items[i], &heap->items[largest]);
        siftDown(heap, largest);
    }
}

static void heapInit(JobHeap *heap) {
    heap->size = 0;
}

static void heapAppendRaw(JobHeap *heap, Job job) {
    heap->items[heap->size++] = job;
}

static void buildMaxHeap(JobHeap *heap) {
    for (int i = (heap->size / 2) - 1; i >= 0; i--) {
        siftDown(heap, i);
    }
}

static void heapInsert(JobHeap *heap, Job job) {
    heap->items[heap->size] = job;
    heap->size++;
    siftUp(heap, heap->size - 1);
}

static int findIndexByPriority(JobHeap *heap, int priority) {
    for (int i = 0; i < heap->size; i++) {
        if (heap->items[i].priority == priority) return i;
    }
    return -1;
}

static int heapDeleteAt(JobHeap *heap, int i) {
    if (i < 0 || i >= heap->size) return 0;
    heap->items[i] = heap->items[heap->size - 1];
    heap->size--;
    if (i < heap->size) {
        siftDown(heap, i);
        siftUp(heap, i);
    }
    return 1;
}

static void printHeapArray(const JobHeap *heap) {
    printf("  Array:  [");
    for (int i = 0; i < heap->size; i++) {
        printf("%c=%d%s", heap->items[i].id, heap->items[i].priority,
               i + 1 < heap->size ? ", " : "");
    }
    printf("]\n");
}

static void printHeapTreeHelper(const JobHeap *heap, int i, int depth) {
    if (i >= heap->size) return;
    printHeapTreeHelper(heap, rightChild(i), depth + 1);
    for (int s = 0; s < depth; s++) printf("        ");
    printf("[%c:%d]\n", heap->items[i].id, heap->items[i].priority);
    printHeapTreeHelper(heap, leftChild(i), depth + 1);
}

static void printHeapTree(const JobHeap *heap) {
    printf("  Tree (rotated, root on the left):\n");
    printHeapTreeHelper(heap, 0, 1);
}

#endif
