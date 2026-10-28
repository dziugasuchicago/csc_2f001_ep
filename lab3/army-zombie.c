#include <stdio.h>
#include <stdlib.h>

#include "army.h"

struct node {
  struct monster* monster;
  struct node* next;
};

struct army {
  struct node* head;
  int stars;
};

struct army* create_army() {
  struct army* a = malloc(sizeof(struct army));
  a->head = NULL;
  a->stars = 0;
  return a;
}

void add_monster_to_army(struct army* a, struct monster* m) {
  struct node* n = malloc(sizeof(struct node));
  n->monster = m;
  n->next = NULL;
  if (a->head == NULL) {
    a->head = n;
  } else {
    struct node* last = a->head;
    while (last->next != NULL)
      last = last->next;
    last->next = n;
  }
}

void display_army(struct army* a) {
  printf("This is a %d stars army\n", a->stars);
  for (struct node* n = a->head; n != NULL; n = n->next)
    display_monster(n->monster);
}

void delete_army(struct army* a) {
  struct node* n = a->head;
  while (n != NULL) {
    struct node* next = n->next;
    free(n);
    n = next;
  }
  free(a);
}
