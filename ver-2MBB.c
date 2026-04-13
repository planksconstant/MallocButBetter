#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

typedef struct metadata {
  size_t size;
  int is_available;
  struct metadata *next;
} metadata;

metadata *heap_head = NULL;

void *my_alloc(size_t alloc_size) {
  metadata *current = heap_head;
  metadata *last = NULL;
  while (current != NULL) {
    if (current->is_available && current->size >= alloc_size) {
      // u just found the perfect chunk of memory that the user needs
      current->is_available = 0;
      return (void *)(current + 1);
    }
    last = current;
    current = current->next;
  }
  size_t page_size = 4096;
  if (alloc_size + sizeof(metadata) > page_size) {
    page_size = alloc_size + sizeof(metadata);
  }
  void *region = mmap(NULL, 4096, PROT_READ | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  if (region == MAP_FAILED) {
    perror("mmap failed");
    return NULL;
  }
  metadata *newNode = (metadata *)region;
  newNode->size = page_size - sizeof(metadata);
  newNode->is_available = 0;
  newNode->next = NULL;

  if (heap_head == NULL) {
    heap_head = newNode;
  } else {
    last->next = newNode;
  }
  return (void *)(newNode + 1);
}

void my_free(void *ptr) {
  if (ptr == NULL) {
    return;
  }
  metadata *header = (metadata *)ptr - 1;
  header->is_available = 1;
}
