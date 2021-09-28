/*
toggle() assumes that the right most digit is index number 0. This means the
digit at index 3 is really the 4th number from the right. The instructions
weren't really clear on whether the right-most number should be indexed as 0 or
1.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int prefix(unsigned int x, unsigned int n) {
  return x >> (32 - n);
}

unsigned int suffix(unsigned int x, unsigned int n) {
  unsigned int result;
  result = x << (32 - n);
  result = result >> (32-n);
  return result;
}

unsigned int toggle(unsigned int x, unsigned int n) {
  unsigned int result;
  result = 1 << n;
  result = x ^ result;
  return result;
}

void decToBinary(int num){

  for (int i = 31; i >= 0; i--) {
    int digit = num >> i;
    if (digit & 1) {
      printf("1");
    }
    else {
      printf("0");
    }
  }
  printf("\n");
}


int main() {
  unsigned int x = 3456789123, y = 3;

  //print introductory part
  printf("Original number in binary: ");
  decToBinary(x);

  //print prefix results
  printf("\nExtracting the first %u digit(s) from %u\n", y, x);
  unsigned int prefixR;
  prefixR = prefix(x, y);
  printf("Decimal: ");
  printf("%u\n",prefixR);
  printf("Binary: ");
  decToBinary(prefixR);
  printf("\n");

  //print suffix results
  printf("Extracting the last %u digit(s) from %u\n", y, x);
  unsigned int suffixR;
  suffixR = suffix(x, y);
  printf("Decimal: ");
  printf("%u\n",suffixR);
  printf("Binary: ");
  decToBinary(suffixR);
  printf("\n");

  //print toggle results
  printf("Toggling digit at index %u (from the right) of %u\n", y, x);
  unsigned int toggleR;
  toggleR = toggle(x, y);
  printf("Decimal: ");
  printf("%u\n",toggleR);
  printf("Binary: ");
  decToBinary(toggleR);

  return 0;
}
