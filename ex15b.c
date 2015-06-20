#include <stdio.h>

int main(int argc, char *argv[]) {
  int i = 5;
  int *pointer_to_i = &i;

  printf("this is i:%d \n", i);
  printf("this is also i:%d \n", *pointer_to_i);
  printf("this is not i:%p \n", pointer_to_i);

}
