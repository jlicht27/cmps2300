/*
The wait() system call returns the process ID (pid) of the parent process. If
you put wait() in the child process, the parent executes first and wait()
returns -1.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void func4() {

  int y;
  int x = 100;
  int forkNum = fork();

  if (forkNum == 0) {
    printf("I am the child and x is %d\n", x);
    printf("My pid is %d\n", getpid());
  }
  else if (forkNum > 0) { //Parent function waits for child to complete
    y = wait(NULL);
    printf("I am the parent and x is %d\n", x);
    printf("My pid is %d\n", getpid());
    printf("wait() returns %d\n", y);
  }
}

int main() {
  func4();
  return 0;
}
