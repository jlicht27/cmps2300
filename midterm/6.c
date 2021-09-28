#include <stdio.h>
#include <unistd.h>

int main() {
  int val = 0;
  int rc = fork();

  if(rc == 0) {
    // nothing
  } else {
    val = 400;
  }
  printf("%d - ", val);
  return 0;
}
