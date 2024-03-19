#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define NUM_LEADERS 3 // you are free to change these, if you wish.
#define NUM_SOLDIERS 3
#define NUM_WEAPONS_PER_SOLDIER 2

#define BUF_SIZE 16  // use this to avoid reading/writing too many bytes!

int main(int argc, char** argv) {
  if (argc != 1) {
    printf("You should not be calling ./armory.bin with args!\n");
    exit(999);
  }

  // TODO: Code this to the requirements!

}
