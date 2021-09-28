/*
The value of x is the same in the parent and child when fork is called. However,
when specifically a parent or child edits the value of x, it doesn't affect the
value of x in the other process.

Food for thought: The scheduling is pretty abnormal when running all of these
fucntions at once. For starters, functions 4,5, and 6 never get called because
function 3 calls exec() in the parent and child functions which stops the other
functions from ever being called. It also seems like the terminal isn't waiting
for all processes to be done before giving the next prompt. The prompt will
appear in the middle of the output. In addition, the scheduler also seems to
confuse all the fork() commands because p3.c seems to run and execute /bin/ls
more than just once.
*/

#include <stdio.h>
#include <unistd.h>

void func1() {
  int x = 100;
  int forkNum = fork();

  if (forkNum == 0) { //child
    x += 1;
    printf("I am the child and x is %d\n", x);
  }
  else if (forkNum > 0) { //parent
    x += 5;
    printf("I am the parent and x is %d\n", x);
  }
}

int main() {
  func1();
  return 0;
}
