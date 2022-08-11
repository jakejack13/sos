#include "lib/queue.h"
#include "stdlib/stdalloc.h"

void queue_init(struct queue *q){
    
};

void queue_free(struct queue *q){

};

bool queue_empty(struct queue *q){
    return q->size == 0;
};

size_t queue_size(struct queue *q){
    return q->size;
};

void queue_enqueue(struct queue *q, void *elm){

};

void *queue_dequeue(struct queue *q){

};

void *queue_peek(struct queue *q){

};