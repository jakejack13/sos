#include "lib/list.h" // struct list
#include "stdlib/stdalloc.h" // malloc, free
#include "stdlib/stdtypes.h" // bool

/* *Structure of a node */
struct node {
    /* *The data that a node points to */
    void *data;
    /* *A pointer to the next node in the list */
    struct node *next;
};

void list_init(struct list *l) {
    l->head = NULL;
}

void list_free(struct list *l) {
    struct node *n = l->head;
    while (n) {
        struct node *next = n->next;
        free(n);
        n = next;
    }
}

void list_add(struct list *l, void *elm) {
    struct node *n = malloc(sizeof(struct node));
    n->data = elm;
    n->next = l->head;
    l->head = n;
}

void list_remove(struct list *l, void *elm) {
    struct node *n = l->head;
    struct node *prev = NULL;
    while (n) {
        if (n->data == elm) {
            if (prev) {
                prev->next = n->next;
            } else {
                l->head = n->next;
            }
            free(n);
            return;
        }
        prev = n;
        n = n->next;
    }
}

void list_clear(struct list *l) {
    struct node *n = l->head;
    while (n) {
        struct node *next = n->next;
        free(n);
        n = next;
    }
    l->head = NULL;
}

bool list_contains(struct list *l, void *elm) {
    struct node *n = l->head;
    while (n) {
        if (n->data == elm) {
            return true;
        }
        n = n->next;
    }
    return false;
}

size_t list_size(struct list *l) {
    size_t size = 0;
    struct node *n = l->head;
    while (n) {
        size++;
        n = n->next;
    }
    return size;
}

void list_to_array(struct list *l, void **buffer, size_t size) {
    struct node *n = l->head;
    size_t i = 0;
    while (n && i < size) {
        buffer[i++] = n->data;
        n = n->next;
    }
}
