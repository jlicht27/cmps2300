/*
There are many variants of the exec() system call because there can be many
ways to run a program. It depends on how you would like to pass
command line arguments in the new program.
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

void func3() {
  int forkNum = fork();

  if (forkNum == 0) { //Child runs new program
    printf("I am the child\n");
    char* myargs[2];
    myargs[0] = strdup("/bin/ls");
    myargs[1] = NULL;

    execvp(myargs[0], myargs);

  }
  else if (forkNum > 0) { //Parent also runs new program
    printf("I am the parent\n");
    char* myargs[3];
    myargs[0] = strdup("/bin/ls");
    myargs[1] = NULL;

    execvp(myargs[0], myargs);
  }
}
int main() {
  func3();
  return 0;
}
