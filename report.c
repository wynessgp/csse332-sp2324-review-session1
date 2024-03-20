#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("You do not know how to call report.bin\n");
    exit(1000); // this is not a relevant exit code.
  }	

  int scout_pid = atoi(argv[1]);
  int* my_bogus_ptr = 0;

  printf("Scout %d is leaving the camp!\n", scout_pid);

  // do some random number generation to determine an exit code
  time_t t;
  srand((int)time(&t) % scout_pid);
  sleep((rand() % 3) + 2); // simulate the scout doing something

  int r = rand() % 4; // generate a random int: [0, 4)
  switch (r) {
    case 0:
      // TODO: Use this print: printf("Ambush! Someone followed the scout!\n");
      exit(5); // you'll need this exit code

    case 1:
      // TODO: Use this print: printf("We're rich! The scout found treasure!\n");
      exit(10); // this one too

    case 2: 
      // TODO: Use this print: printf("Useless! The scout came back empty handed...\n");
      exit(15); // you know what to do

    case 3:
      // TODO: Use this print: printf("Oh tragic day! The scout never returned!\n");
      *my_bogus_ptr = 5; // scary!

    default: // should never happen
      break;
  }

}
