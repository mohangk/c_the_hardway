#include <stdio.h>
/* provides assert */
#include <assert.h>
/* provides type conversion (atoi, atol, atof) memory management (malloc, free) , search (bsearch, qsort)   */
#include <stdlib.h>
/* srtdup */
#include <string.h>

struct Person {
  char *name;
  int age;
  int weight;
  int height;
};

struct Person *Person_create(char *name, int age, int height, int weight)
{
  struct Person *who = malloc(sizeof(struct Person));
  assert(who != NULL);

  who->name = strdup(name);
  who->age = age;
  who->height = height;
  who->weight = weight;

  return who;
}

void Person_destroy(struct Person *who) {
  assert(who != NULL);
  free(who->name);
  free(who);
}

void Person_print(struct Person *who){
  printf("Name: %s \n", who->name);
  printf("Age: %d \n", who->age);
  printf("Weight: %d \n", who->weight);
  printf("Height: %d \n", who->height);
}

int main(int argc, char *argv[]) {
  struct Person *john = Person_create("John", 56, 190, 100);
  struct Person *frank = Person_create("Frank", 25, 100, 89);


  printf("Frank is stored at %p \n", frank);
  printf("John is store at %p \n", john);

  Person_print(john);
  printf("Adding age by 20 \n");
  john->age += 20;
  Person_print(john);

  Person_destroy(john);
  Person_destroy(frank);
}
