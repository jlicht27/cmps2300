#include <stdio.h>

// void swap(int x, int y) {
//   int temp;
//   temp = x;
//   x = y;
//   y = temp;
//   return;
// }

void swap(int *x, int *y) {
  int temp;
  temp = *x;
  *x = *y;
  *y = temp;
  return;
}

int main() {
  int a = 5;
  int b = 6;
  swap(&a,&b);
  printf("a: %d\nb: %d\n", a, b);
}
