#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

typedef struct metadata {
  size_t size;
  int is_available;
  struct metadata *next;
} metadata;

void *my_malloc(size_t alloc_size) {
  void *region = mmap(NULL, 4096, PROT_READ | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  if (region == MAP_FAILED) {
    perror("mmap failed");
    return NULL;
  }

  metadata *Node = (metadata *)region;
  Node->size = alloc_size;
  Node->is_available = 0;
  Node->next = NULL;

  return (void *)(Node + 1);
}

void my_free(void *ptr) {
  if (ptr == NULL) {
    return;
  }
  metadata *header = (metadata *)ptr - 1;
  header->is_available = 1;
}
/*
int main() {
  int *ptr = my_malloc(10 * sizeof(char));
  printf("%p\n", ptr);
  char abhi[] = "ABHISHEK D";
  for (int i = 0; i < 10; i++) {
    ptr[i] = abhi[i];
  }
  printf("\n");
  for (int i = 0; i < 10; i++) {
    printf("%c", ptr[i]);
  }
  printf("\n");
  my_free(ptr);
  for (int i = 0; i < 10; i++) {
    printf("%c", ptr[i]);
  }
}
*/
