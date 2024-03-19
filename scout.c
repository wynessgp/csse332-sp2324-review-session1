#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("You do not know how to call ./scout.bin\n");
  }

  int n = atoi(argv[1]);
  printf("n is %d\n", n); // you can remove this line
  // it's just here to stop the C compiler from complaining.


  // TODO: Take it from here!
  

}
