#include "MBB.c"

int main() {
  int *ptr1 = my_malloc(5 * sizeof(int));
  int *ptr2 = my_malloc(5 * sizeof(int));
  printf("%p  %p\n", ptr1, ptr2);
}
