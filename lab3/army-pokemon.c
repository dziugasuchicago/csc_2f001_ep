#include <stdio.h>
#include <stdlib.h>

#include "army.h"

struct army {
  struct monster** monsters;
  int top;
  int capacity;
};

struct army* create_army() {
  struct army* a = malloc(sizeof(struct army));
  a->monsters = NULL;
  a->top = 0;
  a->capacity = 0;
  return a;
}

void add_monster_to_army(struct army* a, struct monster* m) {
  if (a->top == a->capacity) {
    a->capacity = a->capacity == 0 ? 1 : a->capacity * 2;
    a->monsters = realloc(a->monsters, a->capacity * sizeof(struct monster*));
  }
  a->monsters[a->top] = m;
  a->top++;
}

void display_army(struct army* a) {
  for (int i = 0; i < a->top; i++)
    display_monster(a->monsters[i]);
}

void delete_army(struct army* a) {
  free(a->monsters);
  free(a);
}
