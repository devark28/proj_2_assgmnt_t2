#include <stdio.h>
#include "passenger_heap.h"

int main(void) {
    const char *names[]   = {"Alice", "Brian", "Chen", "Fatima", "Noah", "Sofia"};
    int         risks[]   = {62,      85,      47,     93,       71,     58};
    int count = sizeof(risks) / sizeof(risks[0]);

    PassengerHeap heap;
    heapInit(&heap);

    for (int i = 0; i < count; i++) {
        heapAppendRaw(&heap, names[i], risks[i]);
    }

    printf("Step 1: Initial passenger list (raw, before heapify)\n");
    printHeapArray(&heap);
    printHeapTree(&heap);

    buildMaxHeap(&heap);
    printf("\nStep 2: After buildMaxHeap\n");
    printHeapArray(&heap);
    printHeapTree(&heap);

    printf("\nStep 3: Priority queue (screening order by extractMax):\n");
    PassengerHeap snapshot = heap;
    int order = 1;
    Passenger next;
    while (extractMax(&snapshot, &next)) {
        printf("  %d. %s (risk %d)\n", order++, next.name, next.riskScore);
    }

    heapInsert(&heap, "Urgent", 98);
    printf("\nStep 4: After inserting passenger with risk 98\n");
    printHeapArray(&heap);
    printHeapTree(&heap);

    int idx = findIndexByRisk(&heap, 98);
    if (idx >= 0) {
        printf("\nStep 5: Removing passenger with risk 98 at index %d\n", idx);
        heapDeleteAt(&heap, idx);
    }
    printf("After removal and re-heapifying:\n");
    printHeapArray(&heap);
    printHeapTree(&heap);

    return 0;
}
