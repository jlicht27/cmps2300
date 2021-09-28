/*
The waitpid() system call would be useful when there are multiple forks.
waitpid() only waits for the specific parent process you tell it to. That way
if you wanted to wait for a specific process you would be able to do that.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void func5() {

  int x = 100;
  int status;
  int forkNum = fork();

  if (forkNum == 0) {
    x += 1;
    printf("I am the child and x is %d\n", x);
  }
  else if (forkNum > 0) { //Parent waits for specific child process to complete
    waitpid(forkNum, &status, WUNTRACED | WCONTINUED);
    x += 5;
    printf("I am the parent and x is %d\n", x);
  }
}

int main() {
  func5();
  return 0;
}
