#include <stdio.h>
#include <time.h>

int main() {
  volatile unsigned i;
  volatile unsigned j;
  time_t begin;
  time_t total;
  printf("[testproc2] BEGIN\n");
  begin = time(NULL);
  for (i = 0; i < 8; i++) {
    for (j = 0; j < 2100000000; j++) {}
    printf("[testproc2] LOOP\n");
    printf("  i = %d\n", i);
  }
  printf("[testproc2] TIME\n");
  total = time(NULL) - begin;
  printf("  %ld seconds\n", total);
  printf("[testproc2] END\n");
  return total;
}
