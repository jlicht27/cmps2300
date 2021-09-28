#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
  int rc = fork();

  if(rc == 0) {
    printf("Darmok at Tanagra.\n");
    rc = fork();
    if(rc == 0) {
      printf("Jalad ");
    } else {
      return 0; // current process exits
    }
  } else {
    wait(NULL);
    printf("Darmok and Jalad ");
  }
  printf("at Tanagra.\n");
  return 0;
}
