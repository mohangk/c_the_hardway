#include <stdio.h>

int main(int argc, char *argv[]) {
  int distance = 100;
  float power = 12.34f;
  double super_power = 12356789.56789;

  char initial = 'A';
  char first_name[] = "Mohan";
  char last_name[] = "Krishnan";

  printf("These %d, are %f, all %f the values", distance, power, super_power);
  printf("These are the text %s, info %s, and chr %c", first_name, initial, last_name);

  return 0;
}
