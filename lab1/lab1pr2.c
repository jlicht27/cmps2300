#include <stdio.h>
#include <string.h>

int isHex(char* number) {

  char hex[23] = "01234567890abcdefABCDEF";
  char* checker;

  if (strlen(number) == 0) {
    return 1;
  }

  for (int i = 0; i < strlen(number); i++) {
    checker = strchr(hex, number[i]);
    if (checker == NULL) {
      return 0;
    }
  }
  return 1;
}

int main() {

  char input[20];
  int result;

  printf("Please enter a hex number: ");
  scanf("%s", input);
  result = isHex(input);

  while (result != 1) {
    printf("Please enter a valid hex number: ");
    scanf("%s", input);
    result = isHex(input);
  }
  printf("Thank you!\n");

  return 0;
}
