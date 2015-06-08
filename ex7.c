#include <stdio.h>

int main(int argc, char *argv[]) {
  int bugs = 100;
  double bug_rate = 1.2;

  printf("You have %d bugs at an imaginary rate of %f. \n", bugs, bug_rate);
  long universe_of_defects = 1024L * 1024L * 1024L * 1L;

  printf("Universe of defects is %ld \n", universe_of_defects);

  double expected_bugs = bug_rate * bugs;
  printf("You are expected to have %f bugs. \n", expected_bugs);

  double part_of_universe = expected_bugs/universe_of_defects;

  printf("That is only a portiong %e portion of the universe \n", part_of_universe);

  char nul_byte = '\0';
  int care_percentage = bugs * nul_byte;
  printf("Which means you should care %d%%. \n", care_percentage);

  return 0;
}
