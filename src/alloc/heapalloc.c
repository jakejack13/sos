#include "alloc/heapalloc.h"
#include "alloc/pagealloc.h"

#define POOL_SIZE 16 * 1024 * 1024

/** The pool of metadata nodes that maps to the pool array */
static struct Node metadata[POOL_SIZE];

/** The pool of memory that can be accessed by the global allocator */
static char pool[POOL_SIZE];

/** Initializes the global allocator */
static void heap_init(struct heap_state *state)
{
  for (int i = 0; i < POOL_SIZE; i++)
  {
    metadata[i].pool_element = &pool[i];
    metadata[i].used = false;
    metadata[i].head = false;
    metadata[i].allocated = -1;
    metadata[i].index = i;
  }
}

/** Finds corresponding metadata node to a given pool element */
static struct Node *find_element(void *p)
{
  struct Node *element = NULL;
  for (int i = 0; i < POOL_SIZE; i++)
  {
    if (metadata[i].pool_element == p)
    {
      element = metadata + i;
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

/** Finds a chunk in the pool that satisfies the size requirement. Returns the head of the chunk */
static struct Node *find_space(size_t size)
{
  int counter = 0;
  while (counter < POOL_SIZE)
  {
    // Check if current element is head. If so, skip counter by allocated chunk size
    if ((metadata + counter)->head)
      counter += (metadata + counter)->allocated;

    // Check if chunk size is enough space
    bool fits = true;
    int jump_size = 0; // Amount of bytes to "jump" ahead
    for (int i = 0; i < size; i++)
    {

      if ((metadata + counter + i)->used)
      {
        fits = false;
        jump_size = i;
        break;
      }
    }

    if (fits)
      return (metadata + counter);
    counter += jump_size;
  }
  return NULL;
}

/** Frees a chunk of memory in global memory previous allocated by malloc */
static int global_free(void *p)
{
  struct Node *element = find_element(p);
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
static void *global_malloc(size_t size)
{
  struct Node *head = find_space(size);
  if (head == NULL)
    return NULL;
  head->allocated = size;
  head->head = true;
  switch_state(head, size);

  return head->pool_element;
}

/** Resizes a chunk of memory in global memory previously allocated by malloc */
static void *global_realloc(void *p, size_t size)
{
  struct Node *old_head = find_element(p);
  if (old_head == NULL || !old_head->head)
    return NULL;                      // Check for invalid pointer
  int old_size = old_head->allocated; // Save allocated size
  global_free(p);

  struct Node *head = find_space(size);
  if (head == NULL)
    return NULL;
  switch_state(head, size);
  head->allocated = size;
  head->head = true;
  for (int i = 0; i < old_size; i++)
  {
    pool[i + head->index] = pool[i + old_head->index];
  }

  return head->pool_element;
}
