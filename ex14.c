#include <stdio.h>
#include <ctype.h>
#include <string.h>


int can_print_it(char ch);
void print_letters(char arg[]);

void print_letters(char *arg) {
  int l = strlen(arg);
  int i = 0;

  for(i = 0; i < l; i++){
    char ch = arg[i];

    if(can_print_it(ch)) {
      printf("'%c' == %d", ch, ch);
    }

  }

  printf("\n");
}

int can_print_it(char ch) {
  return isalpha(ch) || isblank(ch);
}

int main(int argc, char *argv[]) {
  int i = 0;
  for(i = 0; i < argc ; i++) {
    print_letters(argv[i]);
  }
  return 0;
}
