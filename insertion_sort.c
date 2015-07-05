#include <stdio.h>
#include <stdlib.h>

void print_numbers(int count, int *numbers);
void insertion_sort(int count, int *numbers);

int main(int argc, char *argv[])
{
  int count = argc - 1;
  int *numbers = malloc(sizeof(int) * count);
  int i;

  for(i = 1; i < argc; i++) {
    numbers[i-1] = atoi(argv[i]);
  }
  print_numbers(count, numbers);
  insertion_sort(count, numbers);
  print_numbers(count, numbers);

  return 0;
}


void insertion_sort(int count, int *numbers) 
{
  int i = 0;
  for(i = 0; i < count; i++) {
    int j = i;
    while((numbers[j] < numbers[j-1]) && j>0) {
      int temp = numbers[j];
      numbers[j] = numbers[j-1];
      numbers[j-1] = temp;
      j--;
    }
  }
}

void print_numbers(int count, int *numbers) {
  int i = 0;
  for(i = 0; i < count; i++) {
    printf(" %d ", numbers[i]);
  }
  printf("\n");
}

