#include "lib/queue.h"
#include "stdlib/stdalloc.h"

/** Data structure for a node */
struct node {
    /** The data that a node points to */
    void *data;
    /** A pointer to the next node in the queue */
    struct node *next;
};

void queue_init(struct queue *q){
    q->front = NULL;
    q->back = NULL;
    q->size=0;
};

void queue_free(struct queue *q){
    while (q->front != NULL) {
        queue_dequeue(q);
    }
};

bool queue_empty(struct queue *q){
    return q->size == 0;
};

size_t queue_size(struct queue *q){
    return q->size;
};

void queue_enqueue(struct queue *q, void *elm){
    struct node *newnode = (struct node*)malloc(sizeof(struct node));

    newnode->data = elm;
    newnode->next = NULL;

    if (queue_empty(q)){
        q->front = newnode;
    } else {
        q->back->next = newnode;
    }
    q->back=newnode;
    q->size++;
};

void *queue_dequeue(struct queue *q){
    struct node *oldnode = q->front;

    if (oldnode == NULL) {
        return NULL;
    }

    if (q->front == q->back){
        q->front = NULL;
        q->back = NULL;
    } else {
        q->front = oldnode->next;
    }
    q->size--;
    void *elm = oldnode->data;
    free(oldnode);

    return (elm);
};

void *queue_peek(struct queue *q){
    return q->front;
};