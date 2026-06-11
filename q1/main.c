#include <stdio.h>
#include "job_heap.h"

int main(void) {
    int priorities[] = {42, 17, 93, 28, 65, 81, 54, 60, 99, 73, 88};
    int count = sizeof(priorities) / sizeof(priorities[0]);

    JobHeap heap;
    heapInit(&heap);

    for (int i = 0; i < count; i++) {
        Job job = { .id = 'A' + i, .priority = priorities[i] };
        heapAppendRaw(&heap, job);
    }

    printf("Step 1: Binary tree from input array (before heapify)\n");
    printHeapArray(&heap);
    printHeapTree(&heap);

    buildMaxHeap(&heap);
    printf("\nStep 2: After buildMaxHeap (Max-Heap property satisfied)\n");
    printHeapArray(&heap);
    printHeapTree(&heap);

    Job urgent = { .id = 'A' + count, .priority = 100 };
    heapInsert(&heap, urgent);
    printf("\nStep 3: After inserting urgent job (priority 100)\n");
    printHeapArray(&heap);
    printHeapTree(&heap);

    int targetIndex = findIndexByPriority(&heap, 100);
    if (targetIndex >= 0) {
        printf("\nStep 4: Removing urgent job (priority 100) at index %d\n", targetIndex);
        heapDeleteAt(&heap, targetIndex);
    }
    printf("After removing urgent job and re-heapifying:\n");
    printHeapArray(&heap);
    printHeapTree(&heap);

    return 0;
}
