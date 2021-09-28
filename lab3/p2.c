/*
Both the parent and child processes can access the file descripter returned by
open(). When both processes are writing to the same file, each process is not
interrupted when writing a specific word, but the two processes will alternate
writing to file.

Example:

Parent
Parent
Child
Parent
Child
Child
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void func2() {
  int openTester = open("test.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

  int forkNum = fork();

  if (forkNum == 0) { //writing 'Child' to file 300 times
    for(int i = 0; i < 300; i++) {
      write(openTester, "Child\n",strlen("Child\n"));
    }
  }

  if (forkNum > 0) {//writing 'Parent' to file 300 times
    for(int j = 0; j < 300; j++) {
      write(openTester, "Parent\n",strlen("Parent\n"));
    }
  }

  close(openTester);
}

int main() {
  func2();
  return 0;
}
