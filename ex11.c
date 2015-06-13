#include <stdio.h>

int main(int argc, char *argv[]) {

  char *states[argc];
  int i = argc;

  while(i > 0) {
    states[i-1] = argv[i-1];
    i--;
  }

  i = argc;

  while(i > 0) {
    printf("States: %s \n", states[i-1]);
    i--;
  }

  return 0;
}
