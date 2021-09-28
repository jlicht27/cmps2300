#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

const char *unsigned_to_binary(unsigned long msg, int size)
{
	char* b = (char *)malloc(size + 1);
	b[0] = '\0';

	int z;
	for (z = (1<<(size-1)); z > 0; z >>= 1)
	{
		strcat(b, ((msg & z) == z) ? "1" : "0");
	}

	return b;
}

unsigned long crc_remainder(unsigned long msg, unsigned long check, int mlen, int clen) {
	unsigned long newmsg = msg << (clen-1);
	unsigned long n;
	int i;
	for (i = mlen; i > 0; i--) {
		if ((newmsg & (1 << (i+clen-2))) != 0) {
			n = check << (i - 1);
			newmsg = newmsg ^ n;
		}
	}
	return newmsg & ((1 << clen) - 1);
}

int length_binary(unsigned long num) {
  int count = (num == 0) ? 1  : (log2(num) + 1);
  return count;
}

int length_decimal(unsigned long num) {
  int count = (num == 0) ? 1  : (log10(num) + 1);
  return count;
}

unsigned long toggle(unsigned long x, unsigned long n) {
  unsigned long result;
  result = 1 << n;
  result = x ^ result;
  return result;
}

int main() {
  // char* num = "10011010";
  //
  // char* ptr;
  // unsigned long result = strtoul(num, &ptr, 2);
  //
  // printf("result: %lu\n", result);
  // printf("length in decimal: %d\n", length_decimal(result));
  // printf("result in binary: %s\n", unsigned_to_binary(result, length_binary(result)));
  // printf("length of result in binary: %d\n", length_binary(result));
  //
  //
  // unsigned long x = 12345;


  printf("%lu\n", toggle(0011010101001, 3));
  printf("001101010001");




}
