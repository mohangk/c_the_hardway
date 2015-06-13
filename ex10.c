#include <stdio.h>

int main(int argc, char *argv[]) {

  int i = 0;

  for(i = 0; i < argc; i++) {
    printf("argv %d:  %s \n", i, argv[i]);
  }

  char *states[] = {NULL, "California", "Texas", "Oregon"};
  int num_states = 4;

  for(i = 0; i < num_states; i++) {
    printf("%s \n", states[i]);
  }

  return 0;
}
