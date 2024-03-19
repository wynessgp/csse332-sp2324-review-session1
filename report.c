#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("You do not know how to call report.bin\n");
    exit(1000); // this is not a relevant exit code.
  }	

  printf("Scout %d is leaving the camp!\n", atoi(argv[1]));
  sleep(3); // simulate the scout doing something

  // do some random number generation to determine an exit code
  srand(time(NULL)); 
  int r = rand() % 4; // generate a random int: [0, 4)
  switch (r) {
    case 0:
      // TODO: Use this print: printf("The scout found an enemy patrol!\n");
      exit(5); // you'll need this exit code

    case 1:
      // TODO: Use this print: printf("The scout found a stash of supplies!\n");
      exit(10); // this one too

    case 2: 
      // TODO: Use this print: printf("The scout came back empty handed... why'd we draft him?\n);
      exit(15); // you know what to do

    case 3:
      // TODO: Use this print: printf("The scout never returned to camp...\n");
      int* my_bogus_ptr = 0;
      *my_bogus_ptr = 5; // scary!

    default: // should never happen
      break;
  }

}
