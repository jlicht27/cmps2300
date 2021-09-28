/*
If the child process tries to use printf() after using close(STDOUT_FILENO), it
will not print to the terminal.
*/

#include <stdio.h>
#include <unistd.h>

void func6() {

  int forkNum = fork();

  if (forkNum == 0) { //Child cannot print after 'close(STDOUT_FILENO)'
    close(STDOUT_FILENO);
    printf("I am the child\n");
  }
  else if (forkNum > 0) {
    printf("I am the parent\n");
  }
}

int main() {
  func6();
  return 0;
}
