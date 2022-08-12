#include "alloc/heapalloc.h"
#include "alloc/pagealloc.h"

#define POOL_SIZE 16 * 1024 * 1024

/** Initializes the heap allocator */
static void heap_init(struct heap_state *state)
{
  state->page = page_alloc();
  struct Node metadata[PAGE_SIZE];
  for (int i = 0; i < PAGE_SIZE; i++)
  {  
    metadata[i].page_element = (state->page)+i;
    metadata[i].used = false;
    metadata[i].head = false;
    metadata[i].allocated = -1;
    metadata[i].index = i;
  }

  state->metadata = metadata;
}

/** Finds corresponding metadata node to a given page element in a heap state struct */
static struct Node *find_element(struct heap_state *state, void *p)
{
  struct Node *element = NULL;
  for (int i = 0; i < PAGE_SIZE; i++)
  {
    if (state.metadata[i].page_element == p)
    {
      element = state.metadata + i;
      return element;
    }
  }

  return element;
}

/** Flips a chunk of data's "used" state to the opposite */
static void switch_state(struct Node *element, size_t size)
{
  // Set data to opposite state
  for (int i = 0; i < size; i++)
  {
    if ((element + i)->used)
      (element + i)->used = false;
    else
      (element + i)->used = true;
  }
}

/** Finds a chunk in a heap state's that satisfies the size requirement. Returns the head of the chunk */
static struct Node *find_space(struct heap_state *state, size_t size)
{
  int counter = 0;
  while (counter < PAGE_SIZE)
  {
    // Check if current element is head. If so, skip counter by allocated chunk size
    if ((state.metadata + counter)->head)
      counter += (state.metadata + counter)->allocated;

    // Check if chunk size is enough space
    bool fits = true;
    int jump_size = 0; // Amount of bytes to "jump" ahead
    for (int i = 0; i < size; i++)
    {

      if ((state.metadata + counter + i)->used)
      {
        fits = false;
        jump_size = i;
        break;
      }
    }

    if (fits)
      return (state.metadata + counter);
    counter += jump_size;
  }
  return NULL;
}

/** Frees a chunk of memory in global memory previous allocated by malloc */
static int heap_free(struct heap_state *state, void *p)
{
  struct Node *element = find_element(state, p);
  if (element == NULL)
    return 0;
  if (!element->head)
    return 0;
  else
  {
    element->head = false;
    switch_state(element, element->allocated);
    return 1;
  }
}

/** Allocates a chunk of memory of the given size in global memory */
static void *heap_malloc(struct heap_state *state, size_t size)
{
  state->size = size;
  struct Node *head = find_space(state, size);
  if (head == NULL)
    return NULL;
  head->allocated = size;
  head->head = true;
  switch_state(head, size);

  return head->page_element;
}

/** Resizes a chunk of memory in global memory previously allocated by malloc */
static void *heap_realloc(struct heap_state *state, void *p, size_t size)
{
  struct Node *old_head = find_element(state, p);
  if (old_head == NULL || !old_head->head)
    return NULL;                      // Check for invalid pointer
  int old_size = old_head->allocated; // Save allocated size
  heap_free(state, p);

  struct Node *head = find_space(state, size);
  if (head == NULL)
    return NULL;
  switch_state(head, size);
  head->allocated = size;
  head->head = true;
  for (int i = 0; i < old_size; i++)
  {
    state->page[i + head->index] = state->page[i + old_head->index];
  }

  return head->page_element;
}

void heap_done(struct heap_state *state) {
  page_free(state->page);
}