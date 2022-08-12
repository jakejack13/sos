/** Implementation of a generic FIFO queue */
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "stdlib/stdtypes.h"

/** Data structure for a node */
struct node {
    void *data;
    struct node *next;
};

/** Data structure for a generic FIFO queue */
struct queue {
    struct node *front;
    struct node *back;
    size_t size;
};

/** Initializes a new queue */
void queue_init(struct queue *q);

/** Frees the queue from memory */
void queue_free(struct queue *q);

/** Returns true if queue is empty, false otherwise */
bool queue_empty(struct queue *q);

/** Returns the size of the queue */
size_t queue_size(struct queue *q);

/** Enqueues the given element into the back of the queue */
void queue_enqueue(struct queue *q, void *elm);

/** Removes and returns the first element in the queue */
void *queue_dequeue(struct queue *q);

/** Returns the first element in the queue without removal */
void *queue_peek(struct queue *q);

#endif //_QUEUE_H_