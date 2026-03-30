#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
void *Smalloc(size_t size) {
  void *ptr = sbrk(0);
  void *request = sbrk(size);
  if (request == (void *)-1) {
    return NULL;
  } else {
    assert(ptr == request);
    return ptr;
  }
}
int main() {
  // int *p = Smalloc(4 * sizeof(int));
  // p[0] = 67;
  // printf("%d", p[0]);
}
