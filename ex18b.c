#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void die(const char *message)
{
  if(errno) {
    perror(message);
  } else {
    printf("ERROR: %s\n", message);
  }

  exit(1);
}

typedef int (*compare_cb)(int a, int b);
typedef void (*sort_cb)(int *numbers, int count, compare_cb cmp);

void insertion_sort(int *numbers, int count, compare_cb cmp) 
{
  int i = 0;
  for(i = 0; i < count; i++) {
    int j = i;
    while(!cmp(numbers[j],numbers[j-1]) && j>0) {
      int temp = numbers[j];
      numbers[j] = numbers[j-1];
      numbers[j-1] = temp;
      j--;
    }
  }
}

void bubble_sort(int *numbers, int count, compare_cb cmp)
{
  int temp = 0;
  int i = 0;
  int j = 0;

  for(i = 0; i < count; i++) {
    for(j = 0; j < count -1; j++){
      if(cmp(numbers[j], numbers[j+1]) > 0){
        temp = numbers[j+1];
        numbers[j+1] = numbers[j];
        numbers[j] = temp;
      }
    }
  }
}

int sorted_order(int a, int b) 
{
  return a > b;
}

int reverse_order(int a, int b)
{
  return b > a;
}

int strange_order(int a, int b)
{
  if(a == 0 || b == 0) {
    return 0;
  } else {
    return a % b;
  }
}

void test_sorting(int *numbers, int count, sort_cb sorter, compare_cb cmp)
{
  int i = 0;
  sorter(numbers, count, cmp);

  if(!numbers) die("Failed to sort as requester");

  for(i=0; i < count; i++){
    printf("%d ", numbers[i]);
  }
  printf("\n");
}

int main(int argc, char *argv[])
{
  if(argc < 2) die("USAGE: ex18 1 5 7 8");

  int count = argc - 1;
  int i = 0;
  char **inputs = argv + 1;

  int *numbers = malloc(count * sizeof(int));
  if(!numbers) die("Memory error.");

  for(i = 0; i < count; i++){
    numbers[i] = atoi(inputs[i]);
  }

  printf("bubble Sorted  order >");
  test_sorting(numbers, count, bubble_sort, sorted_order);
  printf("bubble Reverse order >");
  test_sorting(numbers, count, bubble_sort, reverse_order);
  printf("bubble Weird   order >");
  test_sorting(numbers, count, bubble_sort, strange_order);

  printf("insertion Sorted  order >");
  test_sorting(numbers, count, insertion_sort, sorted_order);
  printf("insertion Reverse order >");
  test_sorting(numbers, count, insertion_sort, reverse_order);
  printf("insertion Weird   order >");
  test_sorting(numbers, count, insertion_sort, strange_order);

  free(numbers);

  return 0;
}
