#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_CAPACITY 64

typedef struct {
    int items[QUEUE_CAPACITY];
    int head;
    int tail;
} IntQueue;

static void queueInit(IntQueue *q) {
    q->head = 0;
    q->tail = 0;
}

static void queuePush(IntQueue *q, int value) {
    q->items[q->tail++] = value;
}

static int queuePop(IntQueue *q) {
    return q->items[q->head++];
}

#endif
