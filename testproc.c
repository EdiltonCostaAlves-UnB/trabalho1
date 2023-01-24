#include <limits.h>
#include <stdio.h>
#include <time.h>

int main() {
  for (unsigned int j = 0; j < 10; j++) {
    for (unsigned int i = 0; i < INT_MAX; i++) {}
  }
  return 0;
}
